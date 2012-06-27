#ifndef APPLICATION_H
#define APPLICATION_H

#include "globals.h"

/*
Application

Abstract class specifying the functioning of an SDL application

Init() - function for initialising any code for the application

IsRunning() - Boolean function to return true if application is running

Run() - Application loop, contains code to be run every application step

Shutdown() - Function for cleaning upon closing the application

*/

class Application
{
  public:
    Application() {};
    ~Application() {};

    virtual bool Init() = 0;
    virtual void Run() = 0;
    virtual void Shutdown() = 0;

    virtual bool IsRunning() = 0;

  protected:
    int _screen_width;
    int _screen_height;
    int _bits_per_pixel;
    bool _full_screen;
    std::string _window_name;
    SDL_Surface* _sdl_surface;
    Uint32 _sdl_flags;

};

#endif // APPLICATION_H
