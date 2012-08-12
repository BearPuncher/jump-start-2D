#include <assert.h>
#include <algorithm>
#include <iostream>         

#include "world.h"
#include "entity.h"
#include "graphic.h"
#include "image.h"
#include "SDL/SDL_opengl.h"

//TODO replace loops with foreaches
//priority queue on add removes

World::World() {
  camera_.position = Point(0,0);
  camera_.rotation = 0;
  
  count_ = 0;
  visible_ = true;
}

World::~World() {
  
}

void World::Begin() {}

void World::End() {}

void World::UpdateLists() {
  
  Entity* entity;
  
  while (!to_remove_.empty()) {
    entity = to_remove_.front();
    to_remove_.pop_front();
    
    if (entity->GetWorld() == NULL) {
      //remove from add if exits in add
      std::remove(to_add_.begin(), to_add_.end(), entity);
      continue;
    }
    
    if (entity->GetWorld() != this) continue;
    
    entity->Removed();
    entity->SetWorld(NULL);
    
    RemoveUpdate(entity);
    RemoveRender(entity);
    //if (e._type) removeType(e);
    //if (e._name) unregisterName(e);
    //if (e.autoClear && e._tween) e.clearTweens();
  }
  
  //Add Queue
  while (!to_add_.empty()) {
    entity = to_add_.front();
    to_add_.pop_front();
    
    if (entity->GetWorld() != NULL) continue;
    
    AddUpdate(entity);
    AddRender(entity);
    
    if (entity->GetCollisionType() != "") AddType(entity);
    //if (e._name) registerName(e);
    
    entity->SetWorld(this);
    entity->Added();
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
  if (!visible_) return;
  glRotatef(camera_.rotation, 0.0f, 0.0, 1.0f);
  glTranslatef(camera_.position.x, camera_.position.y, 0);
  
  glPushMatrix();
  
  if (!render_map_.empty()) {
    //Map of layers to entities, render code needs testing
    //Want c++11
    std::map< int, EntityList* >::iterator it;
    for (it = render_map_.begin(); it != render_map_.end(); it++ ) {
      EntityList* elist = (*it).second;
      if (elist == NULL) continue;
      
      EntityList::iterator it_list;
      for (it_list = elist->begin(); it_list != elist->end(); it_list++ ) {
        Entity* e = (*it_list);
        if (e->IsVisible()) {
          e->Render();
        }
      }
    }
  }
  

glPopMatrix();
}

void World::Add(Entity* entity) {
  to_add_.push_back(entity);
}

void World::Remove(Entity* entity) {
  to_remove_.push_back(entity);
}

void World::RemoveAll() {
  //TODO
}

void World::AddType(Entity* entity) {
  //TODO
  
}

/* Render  and update lists */
void World::AddUpdate(Entity* entity) {
  if (entity == NULL) return;
  update_list_.push_back(entity);
  count_++;
  assert(!update_list_.empty());
  //if (!_classCount[e._class]) _classCount[e._class] = 0;
  //_classCount[e._class] ++;
}

void World::RemoveUpdate(Entity* entity) {
  if (entity == NULL) return;
  update_list_.remove(entity);
  count_--;
}

void World::AddRender(Entity* entity) {
  if (entity == NULL) return;
  int layer = entity->GetLayer();
  if (render_map_[layer] == NULL) render_map_[layer] = new EntityList;
  render_map_[layer]->push_back(entity);
  assert(!render_map_[layer]->empty());
}

void World::RemoveRender(Entity* entity) {
  if (entity == NULL) return;
  int layer = entity->GetLayer();
  render_map_[layer]->remove(entity);
  if (render_map_[layer]->empty()) {
    delete render_map_[layer];
    render_map_[layer] = NULL;
  }
}