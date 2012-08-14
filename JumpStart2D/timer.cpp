#include "timer.h"

Timer::Timer() {
  start_ticks_ = 0;
  paused_ticks_ = 0;
  started_ = false;
  paused_ = false;
}

void Timer::Start() {
  started_ = true;
  paused_ = false;
  start_ticks_ = SDL_GetTicks();
}

void Timer::Stop() {
  started_ = false;
  paused_ = false;
}

void Timer::Pause() {
  if((started_ == true) && (paused_ == false)) {
    paused_ = true;
    paused_ticks_ = SDL_GetTicks() - start_ticks_;
  }
}

void Timer::Unpause() {
  if(paused_ == true) {
    paused_ = false;
    start_ticks_ = SDL_GetTicks() - paused_ticks_;
    paused_ticks_ = 0;
  }
}

int Timer::GetTicks() {
  if( started_ == true ) {
    if( paused_ == true ) {
      return paused_ticks_;
    } else {
      return SDL_GetTicks() - start_ticks_;
    }
  }
  return 0;
}

bool Timer::IsStarted() {
  return started_;
}

bool Timer::IsPaused() {
  return paused_;
}