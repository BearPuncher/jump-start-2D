#ifndef SPRITEMAP_H
#define SPRITEMAP_H

#include "globals.h"
#include "graphic.h"

#include <string>


class Spritemap : public Graphic
{
public:
  Spritemap();
  virtual ~Spritemap();
  
  
  void Render(Point p);
  void Update(double dt);
  
protected:
private:
  int frame_width_;
  int frame_height_;
  
  
  //Struct definition for animation
  struct Animation
	{
    //Amount of frames in the animation
    int frame_count;
    //Animation Speed
    float frame_rate;
    //Pointer to an array of frames in the animation;
    int* frames;
    //Does animation loop
    bool loop;
    //Name of the animation
    std::string name;
    
    //play the
    void play(bool reset)
    {
      if (reset) frame_count = 0;
      
    };
    
    Animation(std::string _name, int* _frames, float _frame_rate = 0, bool _loop = true) :
    name(_name), //Name of animation
    frames(NULL), //Frame
    frame_rate(_frame_rate),
    loop(_loop)
    {
        size_t size_of_array = (sizeof _frames)/(sizeof _frames[0]);
        frames = new int[size_of_array];
        for(int i = size_of_array; i < size_of_array; i++)
      {
        
      }
      
    };
	};
  
};


/*
 
 Spritemap(source:*, frameWidth:uint = 0, frameHeight:uint = 0, callback:Function = null)
 Constructor.
 Spritemap
 
 add(name:String, frames:Array, frameRate:Number = 0, loop:Boolean = true):Anim
 Add an Animation.
 Spritemap
 
 getFrame(column:uint = 0, row:uint = 0):uint
 Gets the frame index based on the column and row of the source image.
 Spritemap
 
 play(name:String = "", reset:Boolean = false, frame:int = 0):Anim
 Plays an animation.
 Spritemap
 
 randFrame():void
 Assigns the Spritemap to a random frame.
 Spritemap
 
 setAnimFrame(name:String, index:int):void
 Sets the frame to the frame index of an animation.
 Spritemap
 
 setFrame(column:uint = 0, row:uint = 0):void
 Sets the current display frame based on the column and row of the source image.
 Spritemap
 
 updateBuffer(clearBefore:Boolean = false):void
 Updates the spritemap's buffer.
 */

#endif // SPRITEMAP_H
