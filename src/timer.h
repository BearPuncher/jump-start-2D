#ifndef JS_TIMER_H
#define JS_TIMER_H

#include "SDL/SDL.h"

/*This piece of code was originally from Lazy Foo' Productions (http://lazyfoo.net/)*/

//SDL Timer class
class Timer {
public:
  Timer();
  void Start();
  void Stop();
  void Pause();
  void Unpause();

  int GetTicks();
  bool IsStarted();
  bool IsPaused(); 
  
private:
  Uint32 start_ticks_;
  Uint32 paused_ticks_;
  bool started_;
  bool paused_;
};

#endif