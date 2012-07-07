#ifndef IMAGE_H
#define IMAGE_H

#include "globals.h"
#include "graphic.h"

#include <string>
#include <map>

class Image : public Graphic {
public:
protected:
private:
};

#endif


/*
 
 _alpha	property
 protected var _alpha:Number = 1
 alpha	property	 
 alpha:Number  [read-write]
 Change the opacity of the Image, a value from 0 to 1.
 
 Implementation 
 public function get alpha():Number 
 public function set alpha(value:Number):void 
 angle	property	 
 public var angle:Number = 0
 Rotation of the image, in degrees.
 
 blend	property	 
 public var blend:String
 Optional blend mode to use when drawing this image. Use constants from the flash.display.BlendMode class.
 
 _class	property	 
 protected var _class:String
 clipRect	property	 
 clipRect:Rectangle  [read-only]
 Clipping rectangle for the image.
 
 Implementation 
 public function get clipRect():Rectangle 
 _color	property	 
 protected var _color:uint = 0x00FFFFFF
 color	property	 
 color:uint  [read-write]
 The tinted color of the Image. Use 0xFFFFFF to draw the Image normally with the default blending mode.
 
 Implementation 
 public function get color():uint 
 public function set color(value:uint):void 
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
 _flip	property	 
 protected var _flip:BitmapData
 _flipped	property	 
 protected var _flipped:Boolean
 flipped	property	 
 flipped:Boolean  [read-write]
 If you want to draw the Image horizontally flipped. This is faster than setting scaleX to -1 if your image isn't transformed.
 
 Implementation 
 public function get flipped():Boolean 
 public function set flipped(value:Boolean):void 
 _flips	property	 
 protected static var _flips:Object
 height	property	 
 height:uint  [read-only]
 Height of the image.
 
 Implementation 
 public function get height():uint 
 locked	property	 
 locked:Boolean  [read-only]
 True if the image is locked.
 
 Implementation 
 public function get locked():Boolean 
 _matrix	property	 
 protected var _matrix:Matrix
 originX	property	 
 public var originX:Number = 0
 X origin of the image, determines transformation point.
 
 originY	property	 
 public var originY:Number = 0
 Y origin of the image, determines transformation point.
 
 scale	property	 
 public var scale:Number = 1
 Scale of the image, affects both x and y scale.
 
 scaledHeight	property	 
 scaledHeight:uint  [read-only]
 The scaled height of the image.
 
 Implementation 
 public function get scaledHeight():uint 
 scaledWidth	property	 
 scaledWidth:uint  [read-only]
 The scaled width of the image.
 
 Implementation 
 public function get scaledWidth():uint 
 scaleX	property	 
 public var scaleX:Number = 1
 X scale of the image.
 
 scaleY	property	 
 public var scaleY:Number = 1
 Y scale of the image.
 
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
 Method detail
 centerOO	()	method
 public function centerOO():void
 Centers the Image's originX/Y to its center.
 
 centerOrigin	()	method	 
 public function centerOrigin():void
 Centers the Image's originX/Y to its center.
 
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