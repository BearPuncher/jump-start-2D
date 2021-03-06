#include <SDL/SDL_opengl.h>
#include "jumpstartcontroller.h"
#include "world.h"

JumpStartController JS;

JumpStartController::JumpStartController() {
  //Setup camera at start
  camera_.position = Point(0,0);
  camera_.rotation = 0.0f;
  
  world_ = NULL;
  next_world_ = NULL;
  bounds_ = NULL;
  
  //Default to 60
  expected_frame_rate_ = 60;
  elapsed_ = 0;
}

void JumpStartController::SetCameraOrigin() {
  camera_.position = Point(0,0);
  camera_.rotation = 0;
}

void JumpStartController::SetCameraPosition(Point position) {
  camera_.position = position;
}

void JumpStartController::SetCameraRotation(float degrees) {
  camera_.rotation = degrees;
}

void JumpStartController::RenderCamera() {
  glRotatef(camera_.rotation, 0.0f, 0.0, 1.0f);
  glTranslatef(camera_.position.x, camera_.position.y, 0);
}

void JumpStartController::CheckWorld() {
  if (next_world_ == NULL) return;
  if (world_ != NULL) {
    world_->End();
  }
  world_ = next_world_;
  next_world_ = NULL;
  world_->Begin();
  camera_ = world_->GetCamera();
}