#include "world.h"
#include "entity.h"
#include "graphic.h"
#include "image.h"
#include <SDL/SDL_opengl.h>

World::World() {
  camera_.position = Point(0,0);
  camera_.rotation = 0;
  
  count_ = 0;
}

World::~World() {
  
}

void World::Begin() {
  Add(new Entity(Point(10,10), new Image("./assets/heart.png")));
  UpdateLists();
}

void World::End() {
  
}


void World::UpdateLists() {
  //Remove
  
  //Add Queue
  while (!to_add_.empty()) {
    Entity* e = to_add_.front();
    to_add_.pop();
    AddUpdate(e);
    AddRender(e);
    
    //addtype
    //addname
    
    e->Added();
  }
}

void World::Update() {
  if (!update_list_.empty()) {
    std::list<Entity*>::iterator it;
    
    for (it = update_list_.begin(); it != update_list_.end(); it++ ) {
      Entity* e = (*it);
      e->Update();
      Graphic* g = e->GetGraphic();
      if (g != NULL && g->IsActive()) {
        g->Update();
      }
    }
  }
}

void World::Render() {
  glRotatef(camera_.rotation, 0.0f, 0.0, 1.0f);
  glTranslatef(camera_.position.x, camera_.position.y, 0);
  
  glPushMatrix();
  if (!render_list_.empty()) {
    std::list<Entity*>::iterator it;
    
    for (it = render_list_.begin(); it != render_list_.end(); it++ ) {
      Entity* e = (*it);
      if (e->IsVisible()) {
        e->Render();
      }
    }
  }
  
  glPopMatrix();
  
}

void World::Add(Entity* entity) {
  to_add_.push(entity);
}

void World::Remove(Entity* entity) {
  to_remove_.push(entity);
}

void World::RemoveAll() {
  
}

void World::AddUpdate(Entity* entity) {
  update_list_.push_back(entity);
  count_++;
  
  //if (!_classCount[e._class]) _classCount[e._class] = 0;
  //_classCount[e._class] ++;
}

void World::RemoveUpdate(Entity* entity) {
  update_list_.remove(entity);
  count_--;
}

void World::AddRender(Entity* entity) {
  render_list_.push_back(entity);
}

void World::RemoveRender(Entity* entity) {
  render_list_.remove(entity);
}