#include "image.h"

Image::Image():Graphic() {
  alpha_ = 1; // value 0 to 1
  angle_ = 0;
  
  scale_ = 1;
  
  blend_mode_ = NORMAL;
  
  clip_rect_ = NULL;
  
  colour_ = 0xffffff;
  flipped_ = false;
  
  origin_x_ = 0;
  origin_y_ = 0;
}

Image::~Image() {
  
}

Image::Image(const char* filename, Rectangle* clip_rect):Graphic() {
  LoadImage(filename);
  
  alpha_ = 1; // value 0 to 1
  angle_ = 0;
  
  scale_ = 1;
  
  blend_mode_ = NORMAL;
  
  clip_rect_ = clip_rect;
  
  colour_ = 0xffffff;
  flipped_ = false;
  
  origin_x_ = 0;
  origin_y_ = 0;
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
  glLoadIdentity();
  
  //Set rotate point for the quad
  glTranslatef(p.x, p.y, 0);
  glRotatef(angle_, 0.0f, 0.0, 1.0f);
  glTranslatef(-p.x, -p.y, 0);
  
  //glPushMatrix();
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
    ApplyBlendFunction();
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
  
  //If clip_rect is not yet defined, values will be x = 0 y = 0 w = 0 h =0
  //This will cause the whole screen to be displayed - fingers crossed
  if (clip_rect_ != NULL) {
    glEnable(GL_SCISSOR_TEST);
    glScissor(clip_rect_->p.x, clip_rect_->p.y, clip_rect_->w, clip_rect_->h);
  }
  
  //No tint
  glColor4f(HEX3_TO_FLOAT(colour_), alpha_);
  
  //Needs to be called before mapping a texture
  glEnable(GL_TEXTURE_2D);
  // Bind the texture to which subsequent calls refer to
  glBindTexture( GL_TEXTURE_2D, texture );
  
  glBegin( GL_QUADS );
  
  //Draw flipped
  if (!flipped_) {
    //Bottom-left vertex (corner)
    glTexCoord2f( 0, 0 ); glVertex3f( x, y, 0.0f );
    //Bottom-right vertex (corner)
    glTexCoord2f( 1, 0 ); glVertex3f( x+w, y, 0.f );
    //Top-right vertex (corner)
    glTexCoord2f( 1, 1 ); glVertex3f( x+w, y+h, 0.f );
    //Top-left vertex (corner)
    glTexCoord2f( 0, 1 ); glVertex3f( x, y+h, 0.f );
  } else {
    //Bottom-left vertex (corner)
    glTexCoord2f( 1, 0 ); glVertex3f( x, y, 0.0f );
    //Bottom-right vertex (corner)
    glTexCoord2f( 0, 0 ); glVertex3f( x+w, y, 0.f );
    //Top-right vertex (corner)
    glTexCoord2f( 0, 1 ); glVertex3f( x+w, y+h, 0.f );
    //Top-left vertex (corner)
    glTexCoord2f( 1, 1 ); glVertex3f( x, y+h, 0.f );    
  }
  
  glEnd();
  
  if (clip_rect_ != NULL) {
    glDisable(GL_SCISSOR_TEST);
  }
  glPopMatrix();
  glPopMatrix();
  
  if (number_of_pixels == 4) {
    glDisable(GL_BLEND);
  }
}

void Image::Update(double dt) {
  
}


void Image::ApplyBlendFunction() {
  switch (blend_mode_) {
    case ADD:
      glBlendFunc(GL_ONE, GL_ONE);
      break;
    case ALPHA:
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
      break;
    case DARKEN:
      //glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
      break;
    case DIFFERENCE:
      glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
      break;
    case ERASE:
      break;
    case HARDLIGHT:
      break;
    case INVERT:
      glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
      //glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
      break;
    case LAYER:
      break;
    case LIGHTEN:
      glBlendFunc(GL_DST_COLOR, GL_ONE);
      break;
    case MULTIPLY: //NOPE
      glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
      break;
    case NORMAL:
      glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
      break;
    case OVERLAY:
      break;
    case SCREEN:
      break;
    case SHADER:
      break;
    case SUBTRACT:
      glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
      break;
    default:
      glBlendFunc(GL_ZERO, GL_ZERO);
      break;
  }
}

