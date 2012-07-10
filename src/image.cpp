#include "image.h"

Image::Image():Graphic() {
  alpha_ = 1; // value 0 to 1
  angle_ = 0;
  
  scale_ = 1;
  
  //clip_rect_;

  colour_ = 0xffffff;
  flipped_ = false;
  
  origin_x_ = 0;
  origin_y_ = 0;
}

Image::~Image() {
  
}

void Image::Render(Point p) {
  //If not visible, dont render
  if (!visible_) {
    return;
  }
  
  double x = p.x - origin_x_ + offset_x_;
  double y = p.y - origin_y_ + offset_y_;
  
  double w = image_surface_->w * scale_x_ * scale_;
  double h = image_surface_->h * scale_y_ * scale_;
  
  GLuint texture;  // This is a handle to our texture object
  GLenum texture_format;
  GLint  number_of_pixels;
  
  // get the number of channels in the SDL surface
  number_of_pixels = image_surface_->format->BytesPerPixel;
  if (number_of_pixels == 4) {// contains an alpha channel
    if (image_surface_->format->Rmask == 0x000000ff) {
      texture_format = GL_RGBA;
    } else {
      texture_format = GL_BGRA;
    }
  } else if (number_of_pixels == 3) {  // no alpha channel
    if (image_surface_->format->Rmask == 0x000000ff) {
      texture_format = GL_RGB;
    } else {
      texture_format = GL_BGR;
    }
  } else {
    fprintf(stderr, "error: Bytes Per Pixel not a valid number - %d.", number_of_pixels);
    exit(-1);
  }
  glPushMatrix();
  
  glTranslatef(-JS.GetCameraPoint().x * (1.0f - scroll_x_),
               -JS.GetCameraPoint().y * (1.0f - scroll_y_), 0);
  
  glGenTextures( 1, &texture );
  
  // Bind the texture object
  glBindTexture( GL_TEXTURE_2D, texture );
  
  // Set the texture's stretching properties
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  
  // Edit the texture object's image data using the information SDL_Surface gives us
  glTexImage2D( GL_TEXTURE_2D, 0, number_of_pixels, image_surface_->w,
               image_surface_->h, 0, texture_format,
               GL_UNSIGNED_INT_8_8_8_8, image_surface_->pixels);
  //GL_UNSIGNED_BYTE, image_surface_->pixels );
  
  if (number_of_pixels == 4) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
  
  //No tint
  glColor3f(HEX3_TO_FLOAT(colour_));
  
  //Needs to be called before mapping a texture
  glEnable(GL_TEXTURE_2D);
  // Bind the texture to which subsequent calls refer to
  glBindTexture( GL_TEXTURE_2D, texture );
  
  glBegin( GL_QUADS );
  
  //Draw flipped
  if (!flipped_) {
    //Bottom-left vertex (corner)
    glTexCoord2i( 0, 0 ); glVertex3f( x, y, 0.0f );
    //Bottom-right vertex (corner)
    glTexCoord2i( 1, 0 ); glVertex3f( x+w, y, 0.f );
    //Top-right vertex (corner)
    glTexCoord2i( 1, 1 ); glVertex3f( x+w, y+h, 0.f );
    //Top-left vertex (corner)
    glTexCoord2i( 0, 1 ); glVertex3f( x, y+h, 0.f );
  } else {
    //Bottom-left vertex (corner)
    glTexCoord2i( 1, 0 ); glVertex3f( x, y, 0.0f );
    //Bottom-right vertex (corner)
    glTexCoord2i( 0, 0 ); glVertex3f( x+w, y, 0.f );
    //Top-right vertex (corner)
    glTexCoord2i( 0, 1 ); glVertex3f( x+w, y+h, 0.f );
    //Top-left vertex (corner)
    glTexCoord2i( 1, 1 ); glVertex3f( x, y+h, 0.f );    
  }
  
  glEnd();
  
  glPopMatrix();
  
  if (number_of_pixels == 4) {
    glDisable(GL_BLEND);
  }
}

void Image::Update(double dt) {
  
}
