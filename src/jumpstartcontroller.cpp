#include "jumpstartcontroller.h"

JumpStartController JS;

JumpStartController::JumpStartController() {
  //Setup camera at start
  camera.position = Point(0,0);
  camera.rotation = 0.0f;
}

//Camera functions
Point JumpStartController::GetCameraPoint() {
  return camera.position;
}

void JumpStartController::SetCameraOrigin() {
  camera.position = Point(0,0);
  camera.rotation = 0;
}

void JumpStartController::SetCameraPosition(Point p) {
  camera.position = p;
}

void JumpStartController::SetCameraRotation(float degrees) {
  camera.rotation = degrees;
}

void JumpStartController::RenderCamera() {
  glRotatef(camera.rotation, 0.0f, 0.0, 1.0f);
  glTranslatef(camera.position.x, camera.position.y, 0);
}