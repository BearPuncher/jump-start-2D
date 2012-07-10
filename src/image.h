#ifndef IMAGE_H
#define IMAGE_H

#include "globals.h"
#include "graphic.h"

#include <string>
#include <map>

using namespace geometry;

class Image : public Graphic {
public:
  Image();
  virtual ~Image();
  
  virtual void Render(Point p);
  virtual void Update(double dt);
  
  inline void SetAlpha(float alpha) {
    alpha_ = alpha;
  };
  
  inline float GetAlpha() {
    return alpha_;
  };
  
  inline void SetScale(double scale) {
    scale_ = scale;
  };
  
  inline void SetClippingRectangle(Point p, int w, int h) {
    clip_rect_.p = p;
    clip_rect_.w = w;
    clip_rect_.h = h;
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
  
  inline void CenterOrigin() {
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
  struct {
    Point p;
    int w;
    int h;
  } clip_rect_;
  
  Uint32 colour_; //0xFFFFFF for no tint
  bool flipped_;
  
  int origin_x_;
  int origin_y_;
  
private:
};

#endif


/*
 
 
 blend	property	 
 public var blend:String
 Optional blend mode to use when drawing this image. Use constants from the flash.display.BlendMode class.
 
 _class	property	 
 protected var _class:String
 

 _colorTransform	property	 
 protected var _colorTransform:ColorTransform
 _drawMask	property	 
 protected var _drawMask:BitmapData
 drawMask	property	 
 drawMask:BitmapData  [read-write]
 Set the transparency mask of the Image.
 
 Implementation 
 public function get drawMask():BitmapData 
 public function set drawMask(value:BitmapData):void 
 
 
 _flips	property	 
 protected static var _flips:Object
 
 locked	property	 
 locked:Boolean  [read-only]
 True if the image is locked.
 
 Implementation 
 public function get locked():Boolean 
 _matrix	property	 
 protected var _matrix:Matrix

 smooth	property	 
 public var smooth:Boolean
 If the image should be drawn transformed with pixel smoothing. This will affect drawing performance, but look less pixelly.
 
 source	property	 
 source:BitmapData  [read-only]
 Implementation 
 protected function get source():BitmapData 
 _tint	property	 
 protected var _tint:ColorTransform
 _tintFactor	property	 
 protected var _tintFactor:Number = 1.0
 tinting	property	 
 tinting:Number  [read-write]
 The amount the image will be tinted, suggested values from 0 to 1. 0 Means no change, 1 is full color tint.
 
 Implementation 
 public function get tinting():Number 
 public function set tinting(value:Number):void 
 _tintMode	property	 
 protected var _tintMode:Number = 0.0
 tintMode	property	 
 tintMode:Number  [read-write]
 The tint mode - multiply or colorize
 
 Implementation 
 public function get tintMode():Number 
 public function set tintMode(value:Number):void 
 width	property	 
 width:uint  [read-only]
 Width of the image.
 
 Implementation 
 public function get width():uint 
 Constructor detail
 Image	()	constructor
 public function Image(source:*, clipRect:Rectangle = null)
 Constructor.
 
 Parameters
 source:* — Source image.
 
 clipRect:Rectangle (default = null) — Optional rectangle defining area of the source image to draw.
 
 clear	()	method	 
 public function clear():void
 Clears the image buffer.
 
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
 
 Parameters
 width:uint — Width of the rectangle.
 
 height:uint — Height of the rectangle.
 
 color:uint (default = 0xFFFFFF) — Color of the rectangle.
 
 alpha:Number (default = 1)
 Returns
 Image — A new Image object.
 lock	()	method	 
 public function lock():void
 Lock the image, preventing updateBuffer() from being run until unlock() is called, for performance.
 
 unlock	()	method	 
 public function unlock():void
 Unlock the image. Any pending updates will be applied immediately.
 
 updateBuffer	()	method	 
 public function updateBuffer(clearBefore:Boolean = false):void
 Updates the image buffer.
 
 Parameters
 clearBefore:Boolean (default = false)
 updateColorTransform	()	method	 
 protected function updateColorTransform():void
 Updates the color transform
*/