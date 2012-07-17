#include "globals.h"
#include "entity.h"

Entity::Entity() {
  position_.x = 0;
  position_.y = 0;
  
  graphic_ = NULL;
}

Entity::Entity(Point p, Graphic* graphic) {
  position_ = p;
  
  graphic_ = graphic;
}

Entity::~Entity() {
  delete graphic_;
};

void Entity::Added() {
  
}

void Entity::Update() {
  position_ = input.GetMousePosition();
}

void Entity::Render() {
  if (graphic_ != NULL && graphic_->IsVisible()) {
    Point point;
    
    if (graphic_->IsRelative()) {
      point = position_;
    } else {
      point.x = point.y = 0;
    }
    
    graphic_->Render(point);
  }
}