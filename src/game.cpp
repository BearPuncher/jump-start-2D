#include "game.h"
#include "entity.h"
#include "graphic.h"

using namespace std;
using namespace geometry;

//Default Constructor
Game::Game() {
  screen_width_ = 640;
  screen_height_ = 480;
  bits_per_pixel_ = 32;
  
  window_name_ = "";
  
  sdl_surface_ = NULL;
  sdl_flags_ = 0;
  
  full_screen_ = false;
}

Game::Game(int screen_width, int screen_height, 
                         std::string window_name, bool full_screen) {
  screen_width_ = screen_width;
  screen_height_ = screen_height;
  
  bits_per_pixel_ = 32;
  
  window_name_ = window_name;
  
  sdl_surface_ = NULL;
  sdl_flags_ = 0;
  
  full_screen_ = full_screen;
}

Game::~Game() {
  delete sdl_surface_;
}

bool Game::Init() {
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
  
  sdl_surface_ = SDL_SetVideoMode(screen_width_, screen_height_,
                                  bits_per_pixel_, sdl_flags_);
  
  if ( sdl_surface_ == NULL ) {
    fprintf(stderr, "Couldn't set %dx %dx%d video mode: %s\n",
            screen_width_, screen_height_, bits_per_pixel_,
            SDL_GetError());
    return false;
  }
  
  fprintf(stderr, "Set %dx%d at %d bits-per-pixel mode\n",
          screen_width_, screen_height_,
          sdl_surface_->format->BitsPerPixel);
  
  fprintf(stderr, "SDL initialized.\n");
  
  //Set Open gl stuff
  //Colour to clear screen
  glClearColor(0, 0, 0, 0);
  
  //Colour to reset pixel depth
  glClearDepth(1.0f);
  
  //Set viewport
  glViewport(0, 0, screen_width_, screen_height_);
  
  //multiply the current matrix with an orthographic matrix
  //Near value 1, far value -1
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, screen_width_, screen_height_, 0, 1, -1);
  glMatrixMode(GL_MODELVIEW);
  
  glEnable(GL_TEXTURE_2D);
  
  glLoadIdentity();
  
  return true;
};

void Game::SetWindowName(std::string name) {
  window_name_ = name;
  SDL_WM_SetCaption(window_name_.c_str(), NULL);
};

//Simple Resize function
void Game::ResizeWindow(int width, int height) {
  screen_width_ = width;
  screen_height_ = height;
  
  sdl_surface_ = SDL_SetVideoMode(screen_width_, screen_height_,
                                  bits_per_pixel_, sdl_flags_);
  
  glViewport(0, 0, screen_width_, screen_height_);
  
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, screen_width_, screen_height_, 0, 1, -1);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
};

//Easily toggle between full screen
void Game::ToggleFullscreen() {
  full_screen_ = !full_screen_;
  
  SDL_WM_ToggleFullScreen(sdl_surface_);
  
  if (!full_screen_) {
    SDL_ShowCursor(SDL_ENABLE);
  } else {
    SDL_ShowCursor(SDL_DISABLE);
  }
};


