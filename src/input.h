#ifndef INPUT_H
#define INPUT_H

#include "globals.h"
using namespace geometry;

class Input
{
public:
  Input();
  ~Input();
  
  // Call this before any other methods
  void ReadInput();
  
  
  inline bool* GetInput()
  {
    return key_held_;
  };
  
  inline bool KeyPressed(SDLKey key)
  {
    return key_held_[key];
  };
  
  inline bool WindowClosed()
  {
    return window_closed_;
  };
  
  inline Point GetMousePosition()
  {
    return Point(mouse_x_, mouse_y_);
  };
  
private:
  SDL_Event event_;
  //bool m_key_down[323];
  bool key_held_[323];
  //bool m_key_up[323];
  bool window_closed_;
  
  int mouse_x_;
  int mouse_y_;
  
  
};

extern Input input;

#endif
