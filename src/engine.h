#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "spritemap.h"
/*
 Engine
 
 Abstract class specifying the functioning of an SDL Game
 
 Init() - function for initialising any code for the Game
 
 IsRunning() - Boolean function to return true if Game is running
 
 Run() - Game loop, contains code to be run every Game step
 
 Shutdown() - Function for cleaning upon closing the Game
 
 */

class Engine {
public:
  enum GameStatusCode {
    GAME_RUNNING = 0,
    GAME_OVER
  };
  
  Engine();
  Engine(int screen_width, int screen_height,
              std::string window_name = "",
              bool full_screen = false,
              int frame_rate = 60,
              bool fixed_frame_rate = false);
  virtual ~Engine();
  
  virtual bool Init();
  
  void Run();
  virtual void Render();
  virtual void Update();
  
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

  int bits_per_pixel_;
  bool full_screen_;
  std::string window_name_;
  SDL_Surface* sdl_surface_;
  Uint32 sdl_flags_;
  
  int frame_rate_;
  bool fixed_frame_rate_;
  bool paused_;
  bool debug_;
  
  GameStatusCode game_status_;
  
  Spritemap* img;
  
  void CheckWorld();
};

#endif // GAME_H