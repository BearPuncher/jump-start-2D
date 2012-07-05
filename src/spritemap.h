#ifndef SPRITEMAP_H
#define SPRITEMAP_H

#include "globals.h"
#include "graphic.h"

#include <string>
#include <map>

class Spritemap : public Graphic {
public:
  Spritemap();
  virtual ~Spritemap();
  
  
  void Render(Point p);
  void Update(double dt);
  
  void add(std::string name, int* frames, float frame_rate = 0, bool loop = true)
  {
    //animation_map_[name] = Animation(name, frames, frame_rate, loop);
  };
  
  
protected:
  //Struct definition for animation
  struct Animation {
    //Name of the animation
    std::string name;
    //Pointer to an array of frames in the animation;
    int* frames;
    //Animation Speed
    float frame_rate;
    //Does animation loop
    bool loop;
    //Amount of frames in the animation
    int frame_count;
    
    //play the
    void play(bool reset)
    {
      if (reset) frame_count = 0;
      
    };
    
    Animation(std::string _name, int* _frames, float _frame_rate = 0, bool _loop = true) :
    name(_name), //Name of animation
    frames(NULL), //Frame
    frame_rate(_frame_rate),
    loop(_loop) {
      size_t size_of_array = (sizeof _frames)/(sizeof _frames[0]);
      frames = new int[size_of_array];
      for(int i = size_of_array; i < size_of_array; i++)
      {
        frames[i] = _frames[i];
      }
      
      frame_count = 0;
      
    };
	};
  
  int frame_width_;
  int frame_height_;
  
  //Map of all animations from a string to a list
  //std::map<std::string,Animation> animation_map_;
  std::string current_animation_;
  
  
  private:
};


/*
 
 Spritemap(source:*, frameWidth:uint = 0, frameHeight:uint = 0, callback:Function = null)
 Constructor.
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
