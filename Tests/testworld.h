#ifndef JS_TESTWORLD_H
#define JS_TESTWORLD_H

#include "world.h"
#include "entity.h"
#include "image.h"


class TestWorld : public World {
public:
  TestWorld() : World() {}
  ~TestWorld() {
    World::~World();
  }
  
  void Begin() {
    World::Begin();
    
    e1 = new Entity(Point(0,0), new Image("./assets/heart.png"));
    Add(e1);
  };
  
  void End() {
    World::End();
  };
  
  void Update() {
    World::Update();
  };
  
  void Render() {
    World::Render();
  };
private:
  Entity* e1;
};

#endif