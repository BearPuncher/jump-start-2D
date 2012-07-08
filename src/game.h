#ifndef GAME_H
#define GAME_H

#include "globals.h"

/*
 Game
 
 Abstract class specifying the functioning of an SDL Game
 
 Init() - function for initialising any code for the Game
 
 IsRunning() - Boolean function to return true if Game is running
 
 Run() - Game loop, contains code to be run every Game step
 
 Shutdown() - Function for cleaning upon closing the Game
 
 */

class Game {
public:
  enum GameStatusCode {
    GAME_RUNNING = 0,
    GAME_OVER
  };
  
  
  Game();
  Game(int screen_width, int screen_height,
              std::string window_name = "", bool full_screen = false);
  virtual ~Game();
  
  virtual bool Init();
  
  virtual void Run();
  virtual void Shutdown() {
      fprintf(stderr, "Quiting SDL.\n");
      SDL_Quit();
  };
  
  //Set window name to string "name"
  void SetWindowName(std::string name);
  //
  void ResizeWindow(int width, int height);
  //Easily toggle between full screen
  void ToggleFullscreen();
  
  virtual inline bool IsRunning() {
    return (game_status_ == GAME_RUNNING);
  };
  
protected:
  int screen_width_;
  int screen_height_;
  int bits_per_pixel_;
  bool full_screen_;
  std::string window_name_;
  SDL_Surface* sdl_surface_;
  Uint32 sdl_flags_;
  
  GameStatusCode game_status_;
  
};

#endif // GAME_H
