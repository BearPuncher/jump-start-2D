#include "entity.h"
#include "globals.h"
#include "world.h"
#include "graphic.h"

Entity::Entity() {
  position_.x = 0;
  position_.y = 0;
  
  graphic_ = NULL;
}

Entity::Entity(Point position, Graphic* graphic) {
  position_ = position;
  graphic_ = graphic;
}

Entity::~Entity() {
  delete graphic_;
};

void Entity::Added() {
  
}

void Entity::Update() {

}

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
  layer_ = layer;
};
