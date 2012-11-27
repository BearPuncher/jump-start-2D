#ifndef JS_SPRITEMAP_H
#define JS_SPRITEMAP_H

#include "image.h"

#include <string>
#include <map>

class Spritemap : public Image {
public:
  Spritemap();
  virtual ~Spritemap();
  Spritemap(const char * filename, int frame_width = 0, int frame_height = 0);
  
  void Update();
  
  void Add(const char* name, int* frames, int frame_count, float frame_rate = 0, bool loop = true);
  void Play(const char* name, bool reset = false, int frame = 0);
  
  
  void GetColumns();
  void GetRows();
  
  void SetFrame(int column, int row);
  int GetFrame(int column, int row) {
    return (row % rows_) * columns_ + (column % columns_);
  }
  
  inline virtual void CenterOrigin() {
    origin_x_ = frame_width_/2;
    origin_y_ = frame_height_/2;
  };
  
protected:
  //Struct definition for animation
  struct Animation {
    std::string name;
    //Pointer to an array of frames in the animation;
    int* frames;
    //Amount of frames in the animation
    int frame_count;
    //Animation Speed
    float frame_rate;
    //Does animation loop
    bool loop;

    
    //play the
    void play(bool reset)
    {
      if (reset) frame_count = 0;
      
    };
    
    Animation(std::string _name, int* _frames, int _frame_count, float _frame_rate = 0, bool _loop = true) :
    name(_name),
    frames(NULL),
    frame_count(_frame_count),
    frame_rate(_frame_rate),
    loop(_loop) {
      frames = new int[_frame_count];
      for(int i = 0; i < _frame_count; i++) {
        frames[i] = _frames[i];
      }
    };
	};
  
  int frame_width_;
  int frame_height_;
  
  //callback
  
  //Map of all animations from a string to a list
  std::map< std::string, Animation* > animation_map_;
  Animation* current_animation_;
  
  int columns_;
  int rows_;
  bool complete_;
  int frame_;
  int frame_count_;
  int index_;
  float rate_;
  double timer_;
  
  virtual void DrawTexture(Point p);
  
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
 
 
 */

#endif // SPRITEMAP_H
