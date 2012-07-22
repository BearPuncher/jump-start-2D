#ifndef JS_H
#define JS_H

#include "globals.h"
#include "world.h"
using namespace geometry;
using namespace draw;
//JS is a public external class that tracks some global application variables

class JumpStartController {
public:
  JumpStartController();
  
  //Camera functions
  inline Camera GetCamera() {
    return camera_;
  };
  
  void SetCameraOrigin();
  
  void SetCameraPosition(Point position);
  
  void SetCameraRotation(float degrees);
  
  void RenderCamera();
  
  inline void SetDimensions(int width, int height) {
    screen_width_ = width;
    screen_height_ = height;
  };
  
  inline int GetScreenWidth() {
    return screen_width_;
  };
  
  inline int GetScreenHeight() {
    return screen_height_;
  };
  
  inline World* GetWorld() {
    return world_;
  };
  
  inline void SetWorld(World* world) {
    if (world_ == world) return;
    next_world_ = world;
  };
  
  //Update to new world if next_world_ is set
  void CheckWorld();
  
protected:

  int screen_width_;
  int screen_height_;

  World* world_;
  World* next_world_;
  
  Camera camera_;
private:
};


extern JumpStartController JS;


#endif
