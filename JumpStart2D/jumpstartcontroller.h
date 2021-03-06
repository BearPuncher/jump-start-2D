#ifndef JS_H
#define JS_H


#include "geometry.h"
#include "draw.h"

//JS is a public external class that tracks some global application variables

class World;

class JumpStartController {
public:
  JumpStartController();

  //Camera functions
  inline draw::Camera GetCamera() {
    return camera_;
  };

  void SetCameraOrigin();

  void SetCameraPosition(geometry::Point position);

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

  void SetBounds(geometry::Rect* bounds) {
    bounds_ = bounds;
  };

  geometry::Rect* GetBounds() {
    return bounds_;
  };

  inline double GetElapsedTime() {
    return elapsed_;
  };

  inline void SetElapsedTime(double elapsed) {
    elapsed_ = elapsed;
  };

  inline double Timedt() {
    return (double)expected_frame_rate_ * elapsed_;
  };

  inline void SetFrameRate(int frame_rate) {
    expected_frame_rate_ = frame_rate;
  };

private:
  int screen_width_;
  int screen_height_;

  World* world_;
  World* next_world_;

  draw::Camera camera_;
  geometry::Rect* bounds_;

  int expected_frame_rate_;
  double elapsed_;
};


extern JumpStartController JS;


#endif
