#include "game_test.h"
#include "entity.h"
#include "graphic.h"

using namespace std;
using namespace geometry;

GameTest::GameTest() : Game() {
  game_status_ = GameTest::GAME_RUNNING;
}

GameTest::GameTest(int screen_width, int screen_height, 
           std::string window_name, bool full_screen) :
Game(screen_width, screen_height, window_name, full_screen) {
  game_status_ = GameTest::GAME_RUNNING;
}


void GameTest::Run() {
  glClearColor(1,1,1,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glPushMatrix();
  //Camera position
  Point p = JS.GetCameraPoint();
  p.x -= 1;
  p.y -= 1;
  JS.SetCameraPosition(p);
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
  myGraphic.SetScroll(0.5f, 0.5f);
  
  myGraphic.Render(Point(600,100));
  
  Graphic myGraphic1;
  myGraphic1.LoadImage("./assets/heart.png");
  myGraphic1.SetOffset(-80, -70);
  myGraphic1.SetScroll(1.0f, 1.0f);
  
  myGraphic1.Render(Point(600,300));
  glPopMatrix();
  
  glPopMatrix();
  
  SDL_GL_SwapBuffers();

  if (input.KeyPressed(SDLK_ESCAPE) || input.WindowClosed()) {
    game_status_ = GameTest::GAME_OVER;
  }
}


bool GameTest::IsRunning() {
  return (game_status_ == GameTest::GAME_RUNNING);
}


