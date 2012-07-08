#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

//#include <Box2D/Box2D.h>

#include "geometry.h"
#include "input.h"
#include "jumpstartcontroller.h"

#define HEX3_TO_FLOAT(x) (float)(((x&0xff0000)>>16)/255.0f),(float)(((x&0x00ff00)>>8)/255.0f),(float)((x&0x0000ff)/255.0f)

#define HEX3_R_VAL(x) (float)(((x&0xff0000)>>16)/255.0f)
#define HEX3_G_VAL(x) (float)(((x&0x00ff00)>>8)/255.0f)
#define HEX3_B_VAL(x) (float)((x&0x0000ff)/255.0f)


#endif // GLOBALS_H
