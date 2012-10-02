#ifndef JS_TESTWORLD_H
#define JS_TESTWORLD_H

#include "Box2D/Box2D.h"

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
    Image* i1 = new Image("./assets/heart.png");
    i1->CenterOrigin();
    e1 = new Entity(Point(0,0), i1);
    e1->SetLayer(0);
    e1->SetHitbox(160, 140);
    e1->CenterOrigin();
    
    Add(e1);
    
    e2 = new Entity(Point(140,140), new Image("./assets/heart.png"));
    e2->SetLayer(1);
    e2->SetHitbox(160, 140);
    Add(e2);
    
    e3 = new Entity(Point(260,260), new Image("./assets/heart.png"));
    e3->SetLayer(2);
    //e2->SetHitbox(60, 60);
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
    //std::cerr << GetLayerCount() << std::endl;
    /*world->Step(JS.GetElapsedTime(), 2, 6);
    
    // Now print the position and angle of the body.
    b2Vec2 position = body->GetPosition();
    float32 angle = body->GetAngle();
    
    
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);*/
    
    if (input.KeyPressed(SDLK_SPACE)) {
      RemoveAll();
    }
  };
  
  void Render() {
    World::Render();
  };
  
  void FocusGained() {
    World::FocusGained();
    std::cerr << "Focused gained" << std::endl;
  };
  
  void FocusLost() {
    World::FocusLost();
    std::cerr << "Focused lost" << std::endl;
  };
  
private:
  Entity* e1;
  Entity* e2;
  Entity* e3;
  b2World* world;
  b2Body* body;
};

#endif