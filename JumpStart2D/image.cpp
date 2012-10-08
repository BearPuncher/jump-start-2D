#include "image.h"

Image Image::CreateRect(int width, int height, Uint32 colour, float alpha) {

  SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, RMASK, GMASK, BMASK, AMASK );
  SDL_Rect rect = {0, 0, width, height};
  SDL_FillRect(surface, &rect, colour);

  Image image(surface);
  image.SetAlpha(alpha);
  return image;
}

Image Image::CreateCircle(int radius, Uint32 colour, float alpha) {
  SDL_Surface* surface = SDL_CreateRGBSurface(0, radius * 2, radius * 2, 32, RMASK, GMASK, BMASK, AMASK );

  static const int BPP = 4;

  double r = (double)radius;

  for (double dy = 1; dy <= r; dy += 1.0) {
    double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
    int x = radius - dx;
    // Grab a pointer to the left-most pixel for each half of the circle
    Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(radius + r - dy)) * surface->pitch + x * BPP;
    Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(radius - r + dy)) * surface->pitch + x * BPP;

    for (; x <= radius + dx; x++) {
      *(Uint32 *)target_pixel_a = colour;
      *(Uint32 *)target_pixel_b = colour;
      target_pixel_a += BPP;
      target_pixel_b += BPP;
    }
  }

  Image image(surface);
  image.SetAlpha(alpha);
  return image;
}

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

Image::Image(const char* filename, SDL_Rect* clip_rect):Graphic() {
  LoadSurface(filename);

  alpha_ = 1; // value 0 to 1
  angle_ = 0;

  scale_ = 1;

  blend_mode_ = NORMAL;

  clip_rect_ = clip_rect;

  colour_ = 0xffffff;
  flipped_ = false;

  origin_x_ = 0;
  origin_y_ = 0;

  bound_texture_ = CreateOpenGLTexture(image_surface_);
}

Image::Image(SDL_Surface* image_surface, SDL_Rect* clip_rect):Graphic() {
  LoadSurface(image_surface);
  
  alpha_ = 1; // value 0 to 1
  angle_ = 0;

  scale_ = 1;

  blend_mode_ = NORMAL;

  clip_rect_ = clip_rect;

  colour_ = 0xffffff;
  flipped_ = false;

  origin_x_ = 0;
  origin_y_ = 0;

  visible_ = true;

  bound_texture_ = CreateOpenGLTexture(image_surface_);
}

void Image::Render(Point point, Camera camera) {

  //If not visible, dont render
  if (!visible_) {
    return;
  }

  glPushMatrix();

  //Set rotate point for the quad
  glTranslatef(point.x, point.y, 0);
  glRotatef(angle_, 0.0f, 0.0, 1.0f);
  glTranslatef(-point.x, -point.y, 0);

  glTranslatef(-camera.position.x * (1.0f - scroll_x_),
               -camera.position.y * (1.0f - scroll_y_), 0);

  //if (number_of_pixels == 4) {
    glEnable(GL_BLEND);
    ApplyBlendFunction();
  //}

  //If clip_rect is not yet defined, values will be x = 0 y = 0 w = 0 h =0
  //This will cause the whole screen to be displayed - fingers crossed
  if (clip_rect_ != NULL) {
    glEnable(GL_SCISSOR_TEST);
    glScissor(clip_rect_->x, clip_rect_->y, clip_rect_->w, clip_rect_->h);
  }

  //No tint
  glColor4f(HEX3_TO_FLOAT(colour_), alpha_);

  //Needs to be called before mapping a texture
  glEnable(GL_TEXTURE_2D);
  // Bind the texture to which subsequent calls refer to
  glBindTexture( GL_TEXTURE_2D, bound_texture_ );

  DrawTexture(point);

  if (clip_rect_ != NULL) {
    glDisable(GL_SCISSOR_TEST);
  }
  glPopMatrix();

  //if (number_of_pixels == 4) {
    glDisable(GL_BLEND);
  //}
}

void Image::DrawTexture(Point p) {
  double x = p.x - origin_x_ + offset_x_;
  double y = p.y - origin_y_ + offset_y_;

  double w = image_surface_->w * scale_x_ * scale_;
  double h = image_surface_->h * scale_y_ * scale_;

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
    //Top-left vertex (corner)
    glTexCoord2f( 1, 0 ); glVertex3f( x, y, 0.0f );
    //Bottom-left vertex (corner)
    glTexCoord2f( 0, 0 ); glVertex3f( x+w, y, 0.f );
    //Bottom-right vertex (corner)
    glTexCoord2f( 0, 1 ); glVertex3f( x+w, y+h, 0.f );
    //Top-right vertex (corner)
    glTexCoord2f( 1, 1 ); glVertex3f( x, y+h, 0.f );
  }
  glEnd();
}

void Image::Update() {

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
    case DIFF:
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
      //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

GLuint Image::CreateOpenGLTexture(SDL_Surface* image_surface) {

  GLuint texture;  // This is a handle to our texture object
  GLenum texture_format;
  GLint  number_of_pixels;

  // get the number of channels in the SDL surface
  number_of_pixels = image_surface->format->BytesPerPixel;
  if (number_of_pixels == 4) {// contains an alpha channel
    if (image_surface->format->Rmask == 0x000000ff) {
      texture_format = GL_RGBA;
    } else {
      texture_format = GL_BGRA;
    }
  } else if (number_of_pixels == 3) {  // no alpha channel
    if (image_surface->format->Rmask == 0x000000ff) {
      texture_format = GL_RGB;
    } else {
      texture_format = GL_BGR;
    }
  } else {
    fprintf(stderr, "error: Bytes Per Pixel not a valid number - %d.", number_of_pixels);
    exit(-1);
  }

  glGenTextures( 1, &texture );

  // Bind the texture object
  glBindTexture( GL_TEXTURE_2D, texture );

  // Set the texture's stretching properties
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  // Edit the texture object's image data using the information SDL_Surface gives us
  glTexImage2D( GL_TEXTURE_2D, 0, number_of_pixels, image_surface->w,
               image_surface->h, 0, texture_format,
               TEXTURE_TYPE, image_surface->pixels);
  //GL_UNSIGNED_BYTE, image_surface_->pixels );
  return texture;
}

