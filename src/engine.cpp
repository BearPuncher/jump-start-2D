#include "engine.h"
#include "entity.h"
#include "graphic.h"

using namespace std;
using namespace geometry;

//Default Constructor
Engine::Engine() {
  JS.SetDimensions(640, 480);
  bits_per_pixel_ = 32;
  
  window_name_ = "";
  
  sdl_surface_ = NULL;
  sdl_flags_ = 0;
  
  full_screen_ = false;
  
  img = NULL;
  
  game_status_ = GAME_RUNNING;
  
  JS.SetWorld(new World());
}

Engine::Engine(int screen_width, int screen_height,
               std::string window_name,
               bool full_screen,
               int frame_rate,
               bool fixed_frame_rate) {
  JS.SetDimensions(screen_width, screen_height);
  
  bits_per_pixel_ = 32;
  
  window_name_ = window_name;
  
  frame_rate_ = frame_rate;
  fixed_frame_rate_ = fixed_frame_rate;
  
  sdl_surface_ = NULL;
  sdl_flags_ = 0;
  
  full_screen_ = full_screen;
  
  img = NULL;
  
  game_status_ = GAME_RUNNING;
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
  
  return true;
};


void Engine::Run() {
  glClearColor(1,1,1,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  glPushMatrix();
  //Camera position
  JS.RenderCamera();
  
  //Render code
  glPushMatrix();
  
  /* Some code goes here */
  
  //Test
  Entity entity(Point(10,10), new Image("./assets/heart.png"));
  entity.Update();
  entity.Render();
  
  glPopMatrix();
  
  glPopMatrix();
  
  SDL_GL_SwapBuffers();
  
  if (input.KeyPressed(SDLK_ESCAPE) || input.WindowClosed()) {
    game_status_ = GAME_OVER;
  }
}

void Engine::SetWindowName(std::string name) {
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


