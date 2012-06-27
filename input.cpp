#include "input.h"

Input input;

Input::Input()
{
   m_windowClosed = false;

   // Make sure all the keys are set to false.
   for (int i = 0; i < 323; i++)
   {
      m_key_held[i] = false;
   }
}

Input::~Input()
{
}

void Input::ReadInput()
{
   if (SDL_PollEvent(&m_event))
   {
      if (m_event.type == SDL_QUIT)
      {
         m_windowClosed = true;
      }

      if (m_event.type == SDL_KEYDOWN)
      {
         m_key_held[m_event.key.keysym.sym] = true;
      }

      if (m_event.type == SDL_KEYUP)
      {
         m_key_held[m_event.key.keysym.sym] = false;
      }
   }
}

bool* Input::GetInput()
{
   return m_key_held;
}

bool Input::KeyPressed(SDLKey key)
{
  return m_key_held[key];
}

bool Input::WindowClosed()
{
   return m_windowClosed;
}
