#include "jumpstartcontroller.h"
#include <SDL/SDL_opengl.h>


JumpStartController JS;

JumpStartController::JumpStartController() {
  //Setup camera at start
  camera_.position = Point(0,0);
  camera_.rotation = 0.0f;
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
  world_->End();
  world_ = next_world_;
  next_world_ = NULL;
  world_->Begin();
  camera_ = world_->GetCamera();
}