#ifndef GAME_TEST_H
#define GAME_TEST_H

#include "globals.h"
#include "game.h"


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

class GameTest : public Game {
public:

  GameTest();
  GameTest(int screen_width, int screen_height, 
       std::string window_name = "", bool full_screen = false);

  
protected:
  
  
};

#endif // GAME_TEST_H
