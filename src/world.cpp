#include "world.h"
#include <SDL/SDL_opengl.h>

World::World() {
  camera_.position = Point(0,0);
  camera_.rotation = 0;
}

World::~World() {
  
}

void World::Begin() {
  
}

void World::End() {
  
}

void World::Update() {

}

void World::Render() {
  glRotatef(camera_.rotation, 0.0f, 0.0, 1.0f);
  glTranslatef(camera_.position.x, camera_.position.y, 0);
  
  glPushMatrix();
  
  glPopName();
  
}

void World::Add() {
  
}

void World::Remove() {
  
}

void World::RemoveAll() {
  
}