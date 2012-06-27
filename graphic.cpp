#include "graphic.h"
#include "globals.h"

Graphic::Graphic()
{
    _active = false;
    _relative = true;
    _scroll_x = 1;
    _scroll_y = 1;
    _visible = true;
    _offset_x = 0;
    _offset_y = 0;
    _scale_x = 1;
    _scale_y = 1;
}

Graphic::~Graphic()
{
    SDL_FreeSurface(_image_surface);
}

void Graphic::Render(Point p)
{
    //If not visible, dont render
    if (!_visible) return;

    double x = p.x + _offset_x;
    double y = p.y + _offset_y;

    double w = _image_surface->w * _scale_x;
    double h = _image_surface->h * _scale_y;

    GLuint texture;  // This is a handle to our texture object
    GLenum texture_format;
    GLint  nOfColors;

    // get the number of channels in the SDL surface
    nOfColors = _image_surface->format->BytesPerPixel;
    if (nOfColors == 4) // contains an alpha channel
    {
        if (_image_surface->format->Rmask == 0x000000ff)
        {
            texture_format = GL_RGBA;
        }
        else
        {
            texture_format = GL_BGRA;
        }

    }
    else if (nOfColors == 3)   // no alpha channel
    {
        if (_image_surface->format->Rmask == 0x000000ff)
        {
            texture_format = GL_RGB;
        }
        else
        {
            texture_format = GL_BGR;
        }
    }
    glGenTextures( 1, &texture );

    // Bind the texture object
    glBindTexture( GL_TEXTURE_2D, texture );

    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // Edit the texture object's image data using the information SDL_Surface gives us
    glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, _image_surface->w,
                  _image_surface->h, 0, texture_format,
                  GL_UNSIGNED_BYTE, _image_surface->pixels );

    if (nOfColors == 4)
    {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

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

    if (nOfColors == 4)
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

    _image_surface = surface_return;
}
