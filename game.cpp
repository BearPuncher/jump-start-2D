#include "game.h"
#include "entity.h"
#include "graphic.h"

using namespace std;
using namespace geometry;

Game::Game()
{
  _screen_width = 640;
  _screen_height = 480;
  _bits_per_pixel = 32;

  _window_name = "";

  _sdl_surface = NULL;
  _sdl_flags = 0;

  _full_screen = false;

  _game_status = Game::GAME_RUNNING;

}

Game::~Game()
{
  delete _sdl_surface;
}

bool Game::Init()
{
  fprintf(stderr, "SDL initializing.\n");

  _sdl_flags = SDL_OPENGL | SDL_ANYFORMAT;

  if (_full_screen) _sdl_flags |= SDL_FULLSCREEN;

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
    _sdl_flags |= SDL_HWSURFACE;
  } else {
    _sdl_flags |= SDL_SWSURFACE;
  }

  _bits_per_pixel = info->vfmt->BitsPerPixel;

  SDL_WM_SetCaption(_window_name.c_str(), NULL);

  _sdl_surface = SDL_SetVideoMode(_screen_width, _screen_height,
                                 _bits_per_pixel, _sdl_flags);

  if ( _sdl_surface == NULL ) {
    fprintf(stderr, "Couldn't set %dx %dx%d video mode: %s\n",
            _screen_width, _screen_height, _bits_per_pixel,
            SDL_GetError());
    return false;
  }

  fprintf(stderr, "Set %dx%d at %d bits-per-pixel mode\n",
          _screen_width, _screen_height,
          _sdl_surface->format->BitsPerPixel);

  fprintf(stderr, "SDL initialized.\n");

  //Set Open gl stuff
  //Colour to clear screen
  glClearColor(0, 0, 0, 0);

  //Colour to reset pixel depth
  glClearDepth(1.0f);

  //Set viewport
  glViewport(0, 0, _screen_width, _screen_height);

  //multiply the current matrix with an orthographic matrix
  //Near value 1, far value -1
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, _screen_width, _screen_height, 0, 1, -1);
  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_TEXTURE_2D);

  glLoadIdentity();

  return true;
}

void Game::Run()
{
  glClearColor(1,1,1,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  /*
  glBegin(GL_QUADS);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
    glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
    glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
    glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
  glEnd();
  */

  /*
  Graphic myGraphic;
  myGraphic.LoadImage("./assets/heart.png");
  myGraphic.Render(Point(80,50));
  */

  SDL_GL_SwapBuffers();

  if ( input.KeyPressed(SDLK_ESCAPE) || input.WindowClosed() )
    _game_status = Game::GAME_OVER;
}

void Game::Shutdown()
{
  fprintf(stderr, "Quiting SDL.\n");
  SDL_Quit();
}

bool Game::IsRunning()
{
  return (_game_status == Game::GAME_RUNNING);
}

//Set window name to string "name"
void Game::SetWindowName(string name)
{
  _window_name = name;
  SDL_WM_SetCaption(_window_name.c_str(), NULL);
}

//
void Game::ResizeWindow(int width, int height)
{
  _screen_width = width;
  _screen_height = height;

	_sdl_surface = SDL_SetVideoMode(_screen_width, _screen_height,
                                 _bits_per_pixel, _sdl_flags);

  glViewport(0, 0, _screen_width, _screen_height);


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, _screen_width, _screen_height, 0, 1, -1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

//Easily toggle between full screen
void Game::ToggleFullscreen()
{
	_full_screen = !_full_screen;

	SDL_WM_ToggleFullScreen(_sdl_surface);

	if (!_full_screen)
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
}
