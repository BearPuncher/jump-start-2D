#include "graphic.h"
#include "globals.h"
#include <iostream>

Graphic::Graphic() {
  active_ = false;
  relative_ = true;
  visible_ = true;
  offset_x_ = 0;
  offset_y_ = 0;
  scale_x_ = 1;
  scale_y_ = 1;
  scroll_x_ = 1;
  scroll_y_ = 1;
}

Graphic::~Graphic() {
  SDL_FreeSurface(image_surface_);
}


void Graphic::LoadSurface( const char * filename) {
  SDL_Surface* surface_temp = NULL;

  if((surface_temp = IMG_Load(filename)) == NULL) {
	const char *message = IMG_GetError();
	if(!message) {
      message = "Unable to determine SDL_Image error";
    }
    
	fprintf(stderr, "Image Error: %s\n", message);
    exit(-1);
  }

  // Check that the image's width is a power of 2
  if ( (surface_temp->w & (surface_temp->w - 1)) != 0 ) {
    fprintf(stderr, "warning: %s width is not a power of 2\n", filename);
  }

  // Also check if the height is a power of 2
  if ( (surface_temp->h & (surface_temp->h - 1)) != 0 ) {
    fprintf(stderr, "warning: %s height is not a power of 2\n", filename);
  }
  
  image_surface_ = surface_temp;
}

void Graphic::LoadSurface(SDL_Surface* image_surface) {
  image_surface_ = image_surface;
}
