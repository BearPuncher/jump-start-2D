#include "graphic.h"
#include "globals.h"

Graphic::Graphic()
{
    active_ = false;
    relative_ = true;
    scroll_x_ = 1;
    scroll_y_ = 1;
    visible_ = true;
    offset_x_ = 0;
    offset_y_ = 0;
    scale_x_ = 1;
    scale_y_ = 1;
}

Graphic::~Graphic()
{
    SDL_FreeSurface(image_surface_);
}

void Graphic::Render(Point p)
{
    //If not visible, dont render
    if (!visible_) return;

    double x = p.x + offset_x_;
    double y = p.y + offset_y_;

    double w = image_surface_->w * scale_x_;
    double h = image_surface_->h * scale_y_;

    GLuint texture;  // This is a handle to our texture object
    GLenum texture_format;
    GLint  number_of_pixels;

    // get the number of channels in the SDL surface
    number_of_pixels = image_surface_->format->BytesPerPixel;
    if (number_of_pixels == 4) // contains an alpha channel
    {
        if (image_surface_->format->Rmask == 0x000000ff)
        {
            texture_format = GL_RGBA;
        }
        else
        {
            texture_format = GL_BGRA;
        }

    }
    else if (number_of_pixels == 3)   // no alpha channel
    {
        if (image_surface_->format->Rmask == 0x000000ff)
        {
            texture_format = GL_RGB;
        }
        else
        {
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
    glTexImage2D( GL_TEXTURE_2D, 0, number_of_pixels, image_surface_->w,
                  image_surface_->h, 0, texture_format,
                  GL_UNSIGNED_INT_8_8_8_8, image_surface_->pixels);
                 //GL_UNSIGNED_BYTE, image_surface_->pixels );

    if (number_of_pixels == 4)
    {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    //Needs to be called before mapping a texture
    glEnable(GL_TEXTURE_2D);
    // Bind the texture to which subsequent calls refer to
    glBindTexture( GL_TEXTURE_2D, texture );

    glBegin( GL_QUADS );
      //Bottom-left vertex (corner)
      glTexCoord2i( 0, 0 ); glVertex3f( x, y, 0.0f );

      //Bottom-right vertex (corner)
      glTexCoord2i( 1, 0 ); glVertex3f( x+w, y, 0.f );

      //Top-right vertex (corner)
      glTexCoord2i( 1, 1 ); glVertex3f( x+w, y+h, 0.f );

      //Top-left vertex (corner)
      glTexCoord2i( 0, 1 ); glVertex3f( x, y+h, 0.f );
    glEnd();

    if (number_of_pixels == 4)
    {
      glDisable(GL_BLEND);
    }
}

void Graphic::Update(double dt) {

}

void Graphic::LoadImage( const char * filename)
{
    SDL_Surface* surface_temp = NULL;
    SDL_Surface* surface_return = NULL;

    if((surface_temp = IMG_Load(filename)) == NULL)
    {
        fprintf(stderr, "Image %s not found.\n", filename);
        exit(-1);
    }

    // Check that the image's width is a power of 2
    if ( (surface_temp->w & (surface_temp->w - 1)) != 0 )
    {
        fprintf(stderr, "warning: %s width is not a power of 2\n", filename);
    }

    // Also check if the height is a power of 2
    if ( (surface_temp->h & (surface_temp->h - 1)) != 0 )
    {
        fprintf(stderr, "warning: %s height is not a power of 2\n", filename);
    }

    surface_return = SDL_DisplayFormatAlpha(surface_temp);
    SDL_FreeSurface(surface_temp);

    image_surface_ = surface_return;
}
