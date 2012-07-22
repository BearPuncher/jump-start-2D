#include "globals.h"
#include "world.h"
#include "entity.h"

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
  
  //Test
  Entity entity(Point(100,50), new Image("./assets/heart.png"));
  entity.Update();
  entity.Render();
  
  glPopName();
  
}

void World::Add() {
  
}

void World::Remove() {
  
}

void World::RemoveAll() {
  
}