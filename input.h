#ifndef INPUT_H
#define INPUT_H

#include "globals.h"

class Input
{
  // Methods
  public:
    Input();
    ~Input();

    // Call this before any other methods
    void ReadInput();

    bool* GetInput();

    bool KeyPressed(SDLKey key);

    // Check this each frame
    bool WindowClosed();

  // Data
  private:
    SDL_Event m_event;
    //bool m_key_down[323];
    bool m_key_held[323];
    //bool m_key_up[323];
    bool m_windowClosed;

};

extern Input input;

#endif
