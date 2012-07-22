#ifndef IMAGE_H
#define IMAGE_H

#include "globals.h"
#include "graphic.h"

#include <SDL/SDL_opengl.h>

#include <string>
#include <map>

using namespace geometry;
using namespace draw;

class Image : public Graphic {
public:
  
  //Blend Modes
  enum BlendMode {
    ADD,
    ALPHA,
    DARKEN,
    DIFFERENCE,
    ERASE,
    HARDLIGHT,
    INVERT,
    LAYER,
    LIGHTEN,
    MULTIPLY,
    NORMAL,
    OVERLAY,
    SCREEN,
    SHADER,
    SUBTRACT
  };

  static Image CreateRectangle(int width, int height, Uint32 colour = 0xFFFFFF, float alpha = 1);
  static Image CreateCircle(int radius, Uint32 colour = 0xFFFFFF, float alpha = 1); 
  
  Image();
  virtual ~Image();
  Image(const char* filename, SDL_Rect* clip_rect = NULL);
  Image(SDL_Surface* image_surface_, SDL_Rect* clip_rect = NULL);
  
  virtual void Render(Point point, Camera camera);
  virtual void Update();
  
  inline void SetAlpha(float alpha) {
    alpha_ = alpha;
  };
  
  inline float GetAlpha() {
    return alpha_;
  };
  
  inline void SetAngle(double angle) {
    angle_ = angle;
  }
  
  inline void SetScale(double scale) {
    scale_ = scale;
  };
  
  inline void SetBlendMode(BlendMode blend_mode) {
    blend_mode_ = blend_mode;
  };
  
  inline void SetClippingRectangle(Point p, int w, int h) {
    clip_rect_ = new SDL_Rect;
    clip_rect_->x = p.x;
    clip_rect_->y = p.x;
    clip_rect_->w = w;
    clip_rect_->h = h;
    //SDL_SetClipRect(image_surface_, clip_rect_);
  };
  
  inline void SetColour(Uint32 colour) {
    colour_ = colour;
  };

  inline Uint32 GetColour() {
    return colour_;
  };
  
  inline void SetFlipped(bool flipped) {
    flipped_ = flipped;
  };
  
  inline bool GetFlipped() {
    return flipped_;
  };
  
  inline void SetOriginX(int origin_x) {
    origin_x_ = origin_x;
  };
  
  inline void SetOriginY(int origin_y) {
    origin_y_ = origin_y;
  };
  
  inline virtual void CenterOrigin() {
    origin_x_ = image_surface_->w/2;
    origin_y_ = image_surface_->h/2;
  };
  
  inline int GetWidth() {
    return image_surface_->w;
  };
  
  inline int GetHeight() {
    return image_surface_->h;
  };
  
  inline int GetScaledWidth() {
    return image_surface_->w * scale_x_ * scale_;
  };
  
  inline int GetScaledHeight() {
    return image_surface_->h * scale_y_ * scale_;
  };
  
protected:
  double alpha_; // value 0 to 1
  double angle_; //0
  
  double scale_; //Affects X&Y
  
  //blend mode
  BlendMode blend_mode_;
  
  Uint32 colour_; //0xFFFFFF for no tint
  bool flipped_;
  
  int origin_x_;
  int origin_y_;
  
  SDL_Rect* clip_rect_;
  
  void ApplyBlendFunction();
  static GLuint CreateOpenGLTexture(SDL_Surface* image_surface);
  virtual void DrawTexture(Point p);
private:
};

#endif



/*
 smooth	property	 
 public var smooth:Boolean
 If the image should be drawn transformed with pixel smoothing. This will affect drawing performance, but look less pixelly.
 
 
 Implementation 
 public function get width():uint 
 Constructor detail
 Image	()	constructor
 public function Image(source:*, clipRect:Rectangle = null)
 Constructor.
 
 clipRect:Rectangle (default = null) — Optional rectangle defining area of the source image to draw.

 
 createCircle	()	method	 
 public static function createCircle(radius:uint, color:uint = 0xFFFFFF, alpha:Number = 1):Image
 Creates a new circle Image.
 
 Parameters
 radius:uint — Radius of the circle.
 
 color:uint (default = 0xFFFFFF) — Color of the circle.
 
 alpha:Number (default = 1) — Alpha of the circle.
 Returns
 Image — A new Image object.
 createRect	()	method	 
 public static function createRect(width:uint, height:uint, color:uint = 0xFFFFFF, alpha:Number = 1):Image
 Creates a new rectangle Image.
 */