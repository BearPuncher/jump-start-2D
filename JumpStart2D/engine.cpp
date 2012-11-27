#include <iostream>

#include "SDL/SDL_opengl.h"

#include "globals.h"
#include "engine.h"
#include "world.h"
#include "entity.h"
#include "image.h"

//Default Constructor
Engine::Engine() : timer() {
  JS.SetDimensions(640, 480);
  JS.SetBounds(new Rect(Point(0,0), 640, 480));
  bits_per_pixel_ = 32;

  window_name_ = "";

  frame_rate_ = 60;
  fixed_frame_rate_ = false;

  paused_ = false;
  debug_ = false;

  sdl_surface_ = NULL;
  sdl_flags_ = 0;

  full_screen_ = false;

  old_time_ = current_time_ = accumulator_ = fps_ = fps_count_ = 0;

  game_status_ = GAME_RUNNING;
  focus_state_ = input.HasFocus();
}

Engine::Engine(int screen_width, int screen_height,
               std::string window_name,
               bool full_screen,
               int frame_rate,
               bool fixed_frame_rate) : timer()  {
  JS.SetDimensions(screen_width, screen_height);
  JS.SetBounds(new Rect(Point(0,0), 640, 480));

  bits_per_pixel_ = 32;

  window_name_ = window_name;

  frame_rate_ = frame_rate;
  fixed_frame_rate_ = fixed_frame_rate;

  paused_ = false;
  debug_ = false;

  sdl_surface_ = NULL;
  sdl_flags_ = 0;

  full_screen_ = full_screen;

   old_time_ = current_time_ = accumulator_ = fps_ = fps_count_ = 0;

  game_status_ = GAME_RUNNING;
  focus_state_ = input.HasFocus();
}

Engine::~Engine() {
  delete sdl_surface_;
}

bool Engine::Init() {
  fprintf(stderr, "SDL initializing.\n");

  sdl_flags_ = SDL_OPENGL | SDL_ANYFORMAT;

  if (full_screen_) sdl_flags_ |= SDL_FULLSCREEN;

  atexit(SDL_Quit);

  if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  const SDL_VideoInfo* info = SDL_GetVideoInfo( );

  if( !info ) {
    /* This should probably never happen. */
    fprintf(stderr, "Video query failed: %s\n", SDL_GetError( ) );
    SDL_Quit();
    return false;
  }
  
  if (info->hw_available) {
    sdl_flags_ |= SDL_HWSURFACE;
  } else {
    sdl_flags_ |= SDL_SWSURFACE;
  }
  
  //Standard SDL GL attributes
  
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  
  SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);
  
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

  bits_per_pixel_ = info->vfmt->BitsPerPixel;

  SDL_WM_SetCaption(window_name_.c_str(), NULL);

  int width = JS.GetScreenWidth();
  int height = JS.GetScreenHeight();

  sdl_surface_ = SDL_SetVideoMode(width, height,
                                  bits_per_pixel_, sdl_flags_);

  if ( sdl_surface_ == NULL ) {
    fprintf(stderr, "Couldn't set %dx %dx%d video mode: %s\n",
            width, height, bits_per_pixel_,
            SDL_GetError());
    return false;
  }

  fprintf(stderr, "Set %dx%d at %d bits-per-pixel mode\n",
          width, height,
          sdl_surface_->format->BitsPerPixel);

  fprintf(stderr, "SDL initialized.\n");

  //Set Open gl stuff
  //Colour to clear screen
  glClearColor(0, 0, 0, 0);

  //Colour to reset pixel depth
  glClearDepth(1.0f);

  //Set viewport
  glViewport(0, 0, width, height);

  //multiply the current matrix with an orthographic matrix
  //Near value 1, far value -1
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, 1, -1);
  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_TEXTURE_2D);

  glLoadIdentity();

  //Globals setup
  JS.SetFrameRate(frame_rate_);
  JS.SetWorld(new World());
  JS.CheckWorld();
  timer.Start();

  return true;
};

void Engine::Run() {

  bool run_loop = UpdateTimer();

  if (run_loop) {
    UpdateFPS();

    Update();
    Render();

    if (input.KeyPressed(SDLK_ESCAPE) || input.WindowClosed()) {
      game_status_ = GAME_OVER;
    }
  }
}

void Engine::Update() {
  World* current_world = JS.GetWorld();
  CheckFocusState();
  if (current_world != NULL) {
    current_world->Update();
  }
  current_world->UpdateLists();
  JS.CheckWorld();
}

void Engine::Render() {
  glClearColor(1,1,1,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glLoadIdentity();

  World* current_world = JS.GetWorld();

  glPushMatrix();

  if (current_world != NULL) {
    if (current_world->IsVisible()) {
      current_world->Render();
      if (debug_) current_world->DebugRender();
    }
  } else {
    //Render static camera if no world exists
    JS.RenderCamera();
  }

  glPopMatrix();

  glPopMatrix();

  SDL_GL_SwapBuffers();
}

void Engine::SetWindowName(const char* name) {
  window_name_ = name;
  SDL_WM_SetCaption(window_name_.c_str(), NULL);
};

//Simple Resize function
void Engine::ResizeWindow(int width, int height) {
  JS.SetDimensions(width, height);

  sdl_surface_ = SDL_SetVideoMode(width, height,
                                  bits_per_pixel_, sdl_flags_);

  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, 1, -1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
};

//Easily toggle between full screen
void Engine::ToggleFullscreen() {
  full_screen_ = !full_screen_;

  SDL_WM_ToggleFullScreen(sdl_surface_);

  if (!full_screen_) {
    SDL_ShowCursor(SDL_ENABLE);
  } else {
    SDL_ShowCursor(SDL_DISABLE);
  }
};


bool Engine::UpdateTimer() {
  bool time_step = true;

  //Variable or fixed time step
  if (fixed_frame_rate_) {
    old_time_ = current_time_;
    current_time_ = (double)timer.GetTicks();
    accumulator_ += (double)(current_time_ - old_time_) / 1000.0f;
    double frame_rate_cap = 1000.0f / (double)frame_rate_ / 1000.0f;
    if (accumulator_ >= frame_rate_cap) {
      accumulator_ -= frame_rate_cap;
      JS.SetElapsedTime(frame_rate_cap);
    } else {
      time_step = false;
    }
  } else {
    old_time_ = current_time_;
    current_time_ = (double)timer.GetTicks();
    int elapsed_ticks = current_time_ - old_time_;
    JS.SetElapsedTime((double)(elapsed_ticks) / 1000.0f);
  }

  return time_step;
}

void Engine::UpdateFPS() {
  fps_count_ += JS.GetElapsedTime();
  fps_++;
  //If greater than or equal to 1 second
  if (fps_count_ >= 1) {
    fprintf(stderr, "%d\r", fps_);
    fps_ = 0;
    fps_count_ -= 1;
  }
}

void Engine::CheckFocusState() {
  if (focus_state_ != input.HasFocus()) {
    focus_state_ = input.HasFocus();
    World* world = JS.GetWorld();
    if (focus_state_) {
      world->FocusGained();
    } else {
      world->FocusLost();
    }
  }
}


