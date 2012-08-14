#include "entity.h"
#include "globals.h"
#include "world.h"
#include "graphic.h"

using namespace draw;

Entity::Entity() {
  position_.x = 0;
  position_.y = 0;
  
  layer_ = 0;
  
  visible_ = true;
  
  graphic_ = NULL;
  world_ = NULL;
  
  collision_type_ = "";
}

Entity::Entity(Point position, Graphic* graphic) {
  position_ = position;
  graphic_ = graphic;
  
  layer_ = 0;
  
  visible_ = true;
  
  world_ = NULL;
  
  collision_type_ = "";
}

Entity::~Entity() {
  delete graphic_;
}

void Entity::Added() {}

void Entity::Removed() {}

void Entity::Update() {}

void Entity::Render() {
  if (graphic_ != NULL && graphic_->IsVisible()) {
    Point point;
    
    if (graphic_->IsRelative()) {
      point = position_;
    } else {
      point.x = point.y = 0;
    }
    
    Camera camera = JS.GetWorld() != NULL ? JS.GetWorld()->GetCamera() : JS.GetCamera();
    
    graphic_->Render(point, camera);
  }
}

void Entity::SetLayer(int layer) {
  if (layer_ == layer) return;
  if (world_ == NULL) {
    layer_ = layer;
    return;
  }
  
  world_->RemoveRender(this);
  layer_ = layer;
  world_->AddRender(this);
}

bool Entity::OnCamera() {
  //TODO
  return false;
}
