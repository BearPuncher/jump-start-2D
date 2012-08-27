#include "input.h"

Input input;

Input::Input() {
  window_closed_ = false;
  window_maximised_ = true;
  window_focused_ = true;
  
  // Make sure all the keys are set to false.
  for (int i = 0; i < 323; i++) {
    key_held_[i] = false;
  }
}

Input::~Input() {
}

void Input::ReadInput() {
  if (SDL_PollEvent(&event_)) {
    if (event_.type == SDL_QUIT) {
      window_closed_ = true;
    }
    
    if (event_.type == SDL_KEYDOWN) {
      key_held_[event_.key.keysym.sym] = true;
    }
    
    if (event_.type == SDL_KEYUP) {
      key_held_[event_.key.keysym.sym] = false;
    }
    
    if (event_.type == SDL_MOUSEMOTION) {
      mouse_x_ = event_.motion.x;
      mouse_y_ = event_.motion.y;
    }
    
    if (event_.type == SDL_KEYUP) {
      key_held_[event_.key.keysym.sym] = false;
    }
    
    if (event_.type == SDL_ACTIVEEVENT) {
      if(event_.active.state & SDL_APPACTIVE) {
        if(event_.active.gain){
          window_maximised_ = true;
        } else {
          window_maximised_ = false;
        }
      } else if (event_.active.state & SDL_APPMOUSEFOCUS) {
        if(event_.active.gain){
          window_focused_ = true;
        } else {
          window_focused_ = false;
        }
      }
    }
  }
}

