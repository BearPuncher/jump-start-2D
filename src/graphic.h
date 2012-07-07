#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL/SDL_image.h>
#include "globals.h"

using namespace geometry;

class Graphic {
public:
  Graphic();
  virtual ~Graphic();
  
  virtual void Render(Point p);
  virtual void Update(double dt);
  
  //Setters
  inline void SetOffset(double offset_x, double offset_y) {
    offset_x_ = offset_x;
    offset_y_ = offset_y;
  };
  
  inline void SetScale(double scale_x, double scale_y) {
    scale_x_ = scale_x;
    scale_y_ = scale_y;
  };
  
  inline void SetScroll(double scroll_x, double scroll_y) {
    scroll_x_ = scroll_x;
    scroll_x_ = scroll_y;
  };
  
  inline void Hide() {
    visible_ = false;
  };
  
  inline void Show() {
    visible_ = true;
  };
  
  void LoadImage( const char * filename);
  
protected:
  bool active_;
  bool relative_;
  double scroll_x_;
  double scroll_y_;
  bool visible_;
  double offset_x_;
  double offset_y_;
  
  double scale_x_;
  double scale_y_;
  
  SDL_Surface* image_surface_; 	// This surface will tell us the details of the image
private:
};

#endif // GRAPHIC_H
