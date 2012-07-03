#ifndef INPUT_H
#define INPUT_H

#include "globals.h"

class Input
{
  public:
    Input();
    ~Input();

    // Call this before any other methods
    void ReadInput();

    bool* GetInput();

    bool KeyPressed(SDLKey key);

    // Check this each frame
    bool WindowClosed();

  private:
    SDL_Event event_;
    //bool m_key_down[323];
    bool key_held_[323];
    //bool m_key_up[323];
    bool window_closed_;

};

extern Input input;

#endif
