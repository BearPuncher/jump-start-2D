#include "SDL/SDL_opengl.h"
#include "entity.h"
#include "globals.h"
#include "world.h"
#include "graphic.h"

using namespace draw;

Entity::Entity() : hitbox_(Point(0,0), 0, 0) {
  position_.x = 0;
  position_.y = 0;

  graphic_ = NULL;

  layer_ = 0;

  visible_ = true;

  world_ = NULL;

  collision_type_ = "";

  mask_ = NULL;
}

Entity::Entity(Point position, Graphic* graphic, geometry::Shape* mask) : hitbox_(Point(0,0), 0, 0) {
  position_ = position;

  graphic_ = graphic;

  layer_ = 0;

  visible_ = true;

  world_ = NULL;

  collision_type_ = "";

  mask_ = mask;
}

Entity::~Entity() {
  delete graphic_;
}

void Entity::Added() {}

void Entity::Removed() {}

void Entity::Update() {
  if (graphic_ != NULL) {
     graphic_->Update();
  }
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

void Entity::DebugRender() {

  int px = position_.x - hitbox_.p.x;
  int py = position_.y - hitbox_.p.y;


  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
    glVertex2f(px, py);
    glVertex2f(px + hitbox_.w, py);
    glVertex2f(px + hitbox_.w, py + hitbox_.h);
    glVertex2f(px, py + hitbox_.h);
  glEnd();
}

void Entity::SetHitbox(int width, int height, int origin_x, int origin_y) {
  hitbox_.w = width;
  hitbox_.h = height;
  hitbox_.p.x = origin_x;
  hitbox_.p.y = origin_y;
}

void Entity::SetHitbox(geometry::Rect hitbox) {
  hitbox_ = hitbox;
}

void Entity::SetHitboxToImage() {
  if (graphic_ == NULL) return;

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
