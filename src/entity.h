#ifndef ENTITY_H
#define ENTITY_H

#include "geometry.h"
using namespace geometry;

class World;
class Graphic;

class Entity {
public:
  Entity();
  Entity(Point position, Graphic* graphic = NULL); /*, mask:Mask = null*/
  virtual ~Entity();

  //Overridable functions
  virtual void Added();
  virtual void Update();
  virtual void Render();
  
  inline void SetOrigin(Point position) {
    position_ = position;
  };
  
  inline int GetLayer() {
    return layer_;
  };
  
  void SetLayer(int layer);

  inline void SetWorld(World* world) {
    world_ = world;
  };
  
protected:
  Graphic* graphic_;
  Point position_;
  int layer_;
  
  World* world_;
private:
};

#endif // ENTITY_H


/*
 bottom : Number
 [read-only] The bottommost position of the Entity's hitbox.
 
 centerX : Number
 [read-only] The center x position of the Entity's hitbox.
 
 centerY : Number
 [read-only] The center y position of the Entity's hitbox.
 
 collidable : Boolean = true
 If the Entity should respond to collision checks.
 
 halfHeight : Number
 [read-only] Half the Entity's height.
 
 halfWidth : Number
 [read-only] Half the Entity's width.
 
 height : int
 Height of the Entity's hitbox.
 
 left : Number
 [read-only] The leftmost position of the Entity's hitbox.
 
 mask : Mask
 An optional Mask component, used for specialized collision.
 
 name : String
 The Entity's instance name.
 
 onCamera : Boolean
 [read-only] If the Entity collides with the camera rectangle.
 
 originX : int
 X origin of the Entity's hitbox.
 
 originY : int
 Y origin of the Entity's hitbox.
 
 renderTarget : BitmapData
 The BitmapData target to draw the Entity to.
 
 right : Number
 [read-only] The rightmost position of the Entity's hitbox.
 
 top : Number
 [read-only] The topmost position of the Entity's hitbox.
 
 type : String
 The collision type, used for collision checking.
 
 visible : Boolean = true
 If the Entity should render.
 
 width : int
 Width of the Entity's hitbox.

*/