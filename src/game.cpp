#include "game.h"
#include "entity.h"
#include "graphic.h"

using namespace std;
using namespace geometry;

Game::Game() : Application() {
  game_status_ = Game::GAME_RUNNING;
}

Game::Game(int screen_width, int screen_height, 
           std::string window_name, bool full_screen) :
Application(screen_width, screen_height, window_name, full_screen) {
  game_status_ = Game::GAME_RUNNING;
}


void Game::Run() {
  glClearColor(1,1,1,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glPushMatrix();
  //Camera position
  //JS.SetCameraPosition(Point(80,80));
  //JS.SetCameraRotation(30.0f);
  JS.RenderCamera();
  
  /*
  glBegin(GL_QUADS);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
    glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
    glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
    glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
  glEnd();
  */

  
  //Render code
  glPushMatrix();
  
  Graphic myGraphic;
  myGraphic.LoadImage("./assets/heart.png");
  myGraphic.SetOffset(-80, -70);
  myGraphic.Render(Point(0,0));
  glPopMatrix();
  
  glPopMatrix();
  
  SDL_GL_SwapBuffers();

  if (input.KeyPressed(SDLK_ESCAPE) || input.WindowClosed()) {
    game_status_ = Game::GAME_OVER;
  }
}


bool Game::IsRunning() {
  return (game_status_ == Game::GAME_RUNNING);
}


