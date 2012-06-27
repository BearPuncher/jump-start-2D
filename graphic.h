#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL/SDL_image.h>
#include "globals.h"

using namespace geometry;

class Graphic
{
  public:
    Graphic();
    virtual ~Graphic();

    virtual void Render(Point p);
    virtual void Update(double dt);

    //Setters
    inline void SetOffset(double offset_x, double offset_y)
    {
      _offset_x = offset_x; _offset_y = offset_y;
    };
    inline void SetScale(double scale_x, double scale_y)
    {
      _scale_x = scale_x; _scale_y = scale_y;
    }
    inline void Hide()
    {
      _visible = false;
    };
    inline void Show()
    {
      _visible = true;
    };

    void LoadImage( const char * filename);

  protected:
    bool _active;
    bool _relative;
    double _scroll_x;
    double _scroll_y;
    bool _visible;
    double _offset_x;
    double _offset_y;

    double _scale_x;
    double _scale_y;

    SDL_Surface* _image_surface; 	// This surface will tell us the details of the image
  private:
};

#endif // GRAPHIC_H
