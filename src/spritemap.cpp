#include "graphic.h"
#include "globals.h"

#include "spritemap.h"

Spritemap::Spritemap():Graphic(){

}

Spritemap::~Spritemap() {
  
}

void Spritemap::Render(Point p) {
  Graphic::Render(p);
}

void Spritemap::Update(double dt) {
  Graphic::Update(dt);
}

void Spritemap::add(std::string name, int* frames, float frame_rate, bool loop) {
  animation_map_[name] =  new Animation(name, frames, frame_rate, loop);
};
