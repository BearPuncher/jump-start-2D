#ifndef JS_ENTITY_H
#define JS_ENTITY_H

#include <string>
#include "geometry.h"

class World;
class Graphic;

class Entity {
public:
  /**
   * Constructor.
   */
  Entity();
  
  /**
   * Constructor.
   * @param	position  Starting position of the entity
   * @param	graphic   Pointer to a graphic
   * @param	mask      The image mask, hides certain parts of image
   */
  Entity(geometry::Point position, Graphic* graphic = NULL, geometry::Shape* mask = NULL);
  
  /**
   * Deconstructor.
   */
  virtual ~Entity();

  //Overridable functions
  /**
   * Called upon the entity being added to a world
   */
  virtual void Added();
  
  /**
   * Called upon the entity being removed to a world
   */
  virtual void Removed();
  
  /**
   * Called every update cycle
   */
  virtual void Update();
  
  /**
   * Called every render step
   */
  virtual void Render();

  /**
   * Draws hitbox of the entity
   */
  void DebugRender();
  
  /**
   * Called upon the entity being added to a world
   * @return The pointer to the entity's graphic
   */
  inline Graphic* GetGraphic() {
    return graphic_;
  };

  /**
   * Sets the origin of the hitbox to center of the hitbox
   */
  inline void CenterOrigin() {
    hitbox_.p.x = hitbox_.w / 2;
    hitbox_.p.y = hitbox_.h / 2;
  };

  /**
   * Sets the entity's origin to given point
   * @param position  The point to be the new hitbox origin
   */
  inline void SetOrigin(geometry::Point position) {
    position_ = position;
  };

  /**
   * Returns the current point of origin
   */
  inline geometry::Point GetOrigin() {
    return position_;
  };

  /**
   * Sets the entity's hitbox to given dimensions
   * @param width   width of the hitbox
   * @param height  height of the hitbox
   * @param origin  origin of the hitbox
   */
  void SetHitbox(int width = 0, int height = 0, geometry::Point origin = geometry::origin);
  
  /**
   * Sets the entity's hitbox to given rectange
   * @param hitbox   given hitbox to clone
   */
  void SetHitbox(geometry::Rect hitbox);
  
  /**
   * Sets the entity's hitbox the dimensions current graphic
   */
  void SetHitboxToImage();


  void SetLayer(int layer);

  inline int GetLayer() {
    return layer_;
  };

  inline World* GetWorld() {
    return world_;
  }

  inline void SetWorld(World* world) {
    world_ = world;
  };

  inline bool IsVisible() {
    return visible_;
  };

  inline void SetCollisionType(const char* type) {
    collision_type_ = type;
  };

  inline std::string GetCollisionType() {
    return collision_type_;
  };

  bool OnCamera();

protected:
  geometry::Point position_;

  geometry::Rect hitbox_;

  geometry::Shape* mask_;

  Graphic* graphic_;
  int layer_;
  bool visible_;
  World* world_;
  std::string collision_type_;

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
 vis

 left : Number
 [read-only] The leftmost position of the Entity's hitbox.

 mask : Mask
 An optional Mask component, used for specialized collision.

 name : String
 The Entity's instance name.

 onCamera : Boolean
 [read-only] If the Entity collides with the camera Rect.

 right : Number
 [read-only] The rightmost position of the Entity's hitbox.

 top : Number
 [read-only] The topmost position of the Entity's hitbox.


 addGraphic(g:Graphic):Graphic
 Adds the graphic to the Entity via a Graphiclist.
 Entity

 centerOrigin():void
 Center's the Entity's origin (half width & height).
 Entity

 clampHorizontal(left:Number, right:Number, padding:Number = 0):void
 Clamps the Entity's hitbox on the x-axis.
 Entity

 clampVertical(top:Number, bottom:Number, padding:Number = 0):void
 Clamps the Entity's hitbox on the y axis.
 Entity

 collide(type:String, x:Number, y:Number):Entity
 Checks for a collision against an Entity type.
 Entity

 collideInto(type:String, x:Number, y:Number, array:Object):void
 Populates an array with all collided Entities of a type.
 Entity

 collidePoint(x:Number, y:Number, pX:Number, pY:Number):Boolean
 Checks if this Entity overlaps the specified position.
 Entity

 collideRect(x:Number, y:Number, rX:Number, rY:Number, rWidth:Number, rHeight:Number):Boolean
 Checks if this Entity overlaps the specified Rect.
 Entity

 collideTypes(types:Object, x:Number, y:Number):Entity
 Checks for collision against multiple Entity types.
 Entity

 collideTypesInto(types:Object, x:Number, y:Number, array:Object):void
 Populates an array with all collided Entities of multiple types.
 Entity

 collideWith(e:Entity, x:Number, y:Number):Entity
 Checks if this Entity collides with a specific Entity.
 Entity

 distanceFrom(e:Entity, useHitboxes:Boolean = false):Number
 Calculates the distance from another Entity.
 Entity

 distanceToPoint(px:Number, py:Number, useHitbox:Boolean = false):Number
 Calculates the distance from this Entity to the point.
 Entity

 distanceToRect(rx:Number, ry:Number, rwidth:Number, rheight:Number):Number
 Calculates the distance from this Entity to the Rect.
 Entity

 getClass():Class
 Entity

 moveBy(x:Number, y:Number, solidType:Object = null, sweep:Boolean = false):void
 Moves the Entity by the amount, retaining integer values for its x and y.
 Entity

 moveCollideX(e:Entity):Boolean
 When you collide with an Entity on the x-axis with moveTo() or moveBy().
 Entity

 moveCollideY(e:Entity):Boolean
 When you collide with an Entity on the y-axis with moveTo() or moveBy().
 Entity

 moveTo(x:Number, y:Number, solidType:Object = null, sweep:Boolean = false):void
 Moves the Entity to the position, retaining integer values for its x and y.
 Entity

 moveTowards(x:Number, y:Number, amount:Number, solidType:Object = null, sweep:Boolean = false):void
 Moves towards the target position, retaining integer values for its x and y.
 Entity

 setHitbox(width:int = 0, height:int = 0, originX:int = 0, originY:int = 0):void
 Sets the Entity's hitbox properties.
 Entity

 setHitboxTo(o:Object):void
 Sets the Entity's hitbox to match that of the provided object.
 Entity

 toString():String
 Gets the class name as a string.
 Entity

*/
