#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "application.h"


/*
Game

Game is an implementation of Application
 Game game;

Init() - function for initialising any code for the game
  if (!game.Init()) exit(); //Application failed to initialise

IsRunning() - Boolean function to return true if game is running
Run() - Game loop, contains code to be run every game step
  while (game.IsRunning()) {
    game.Run(); //Does something
  }

Shutdown() - Function for cleaning upon closing the game
  game.Shutdown();
  exit();

*/

class Game : public Application
{
  public:
    enum GameStatusCode {
      GAME_RUNNING = 0,
      GAME_OVER
    };

    Game();
    ~Game();
    bool Init();
    void Run();
    void Shutdown();

    bool IsRunning();

    void SetWindowName(std::string name);
    void ResizeWindow(int width, int height);
    void ToggleFullscreen();

  protected:
    GameStatusCode _game_status;

};

#endif // GAME_H
