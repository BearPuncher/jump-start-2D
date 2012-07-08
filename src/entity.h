#ifndef ENTITY_H
#define ENTITY_H

#include "spritemap.h"

class Entity {
  public:
    Entity() {};
    virtual ~Entity() {};

    virtual void Update(float dt) {};//= 0;
    virtual void Render() {};//= 0;

  protected:
    Image sprite_;
  private:
};

#endif // ENTITY_H
