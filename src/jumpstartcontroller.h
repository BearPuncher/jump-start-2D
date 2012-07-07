#ifndef JS_H
#define JS_H

#include "globals.h"
using namespace geometry;

//JS is a public external class that tracks some global application variables

class JumpStartController {
public:
  JumpStartController();
  
  //Camera functions
  Point GetCameraPoint();
  
  void SetCameraOrigin();
  
  void SetCameraPosition(Point p);
  
  void SetCameraRotation(float degrees);
  
  void RenderCamera();
  
protected:
  //Camera struct
  struct {
    Point position;
    float rotation;
  } camera;

private:
};


extern JumpStartController JS;


#endif
