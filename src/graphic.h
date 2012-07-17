#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL/SDL_image.h>
#include "globals.h"

using namespace geometry;

class Graphic {
public:
  Graphic();
  virtual ~Graphic();
  
  virtual void Render(Point p) {};
  virtual void Update() {};
  
  //Setters
  inline void SetRelative(bool relative) {
    relative_ = relative;
  };
  
  inline void SetScaleX(double scale_x) {
    scale_x_ = scale_x;
  };
  
  inline void SetScaleY(double scale_y) {
    scale_y_ = scale_y;
  };
  
  inline void SetScroll(double scroll_x, double scroll_y) {
    scroll_x_ = scroll_x;
    scroll_y_ = scroll_y;
  };
  
  inline void SetVisible(bool visible) {
    visible_ = visible;
  };
  
  inline void SetOffset(double offset_x, double offset_y) {
    offset_x_ = offset_x;
    offset_y_ = offset_y;
  };
  
  //Getters
  inline bool IsVisible() {
    return visible_;
  };
  
  inline bool IsRelative() {
    return relative_;
  };
  
  void LoadImage( const char * filename);
  void LoadImage(SDL_Surface* image_surface);
  
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
