#ifndef JS_GLOBALS_H
#define JS_GLOBALS_H

#include "input.h"
#include "jumpstartcontroller.h"

#define HEX3_TO_FLOAT(x) (float)(((x&0xff0000)>>16)/255.0f),(float)(((x&0x00ff00)>>8)/255.0f),(float)((x&0x0000ff)/255.0f)

#define HEX3_R_VAL(x) (float)(((x&0xff0000)>>16)/255.0f)
#define HEX3_G_VAL(x) (float)(((x&0x00ff00)>>8)/255.0f)
#define HEX3_B_VAL(x) (float)((x&0x0000ff)/255.0f)

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  #define RMASK 0xff000000
  #define GMASK 0x00ff0000
  #define BMASK 0x0000ff00
  #define AMASK 0x000000ff
  #define TEXTURE_TYPE GL_UNSIGNED_INT_8_8_8_8
#else
  #define RMASK 0x000000ff
  #define GMASK 0x0000ff00
  #define BMASK 0x00ff0000
  #define AMASK 0xff000000
  #define TEXTURE_TYPE GL_UNSIGNED_BYTE
#endif

#endif // GLOBALS_H
