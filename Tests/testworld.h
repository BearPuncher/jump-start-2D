#ifndef JS_TESTWORLD_H
#define JS_TESTWORLD_H

#include "Box2D/Box2D.h"

#include "world.h"
#include "testentity.h"
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
    
    e2 = new Entity(Point(100,40), new Image("./assets/heart.png"));
    Add(e2);
    
    e3 = new Entity(Point(40,100), new Image("./assets/heart.png"));
    Add(e3);
    
    /*
    b2Vec2 gravity(0.0f, -10.0f);
    bool doSleep = true;
    world = new b2World(gravity, doSleep);
    
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    body = world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    
    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    
    // Override the default friction.
    fixtureDef.friction = 0.3f;
    
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);*/
  };
  
  void End() {
    World::End();
  };
  
  void Update() {
    World::Update();
    
    /*world->Step(JS.GetElapsedTime(), 2, 6);
    
    // Now print the position and angle of the body.
    b2Vec2 position = body->GetPosition();
    float32 angle = body->GetAngle();
    
    
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);*/
    if (input.KeyPressed(SDLK_SPACE)) {
      std::cerr << (bool)BringToFront(e1) << std::endl; 
    }
  };
  
  void Render() {
    World::Render();
  };
private:
  Entity* e1;
  Entity* e2;
  Entity* e3;
  b2World* world;
  b2Body* body;
};

#endif