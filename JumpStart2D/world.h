#ifndef JS_WORLD_H
#define JS_WORLD_H

#include <map>
#include <list>
#include <deque>

#include "globals.h"
#include "geometry.h"
#include "draw.h"

class Entity;

class World {
public:
  World();
  ~World();
  
  virtual void Begin();
  virtual void End();
  virtual void Update();
  virtual void Render();
  
  //Adds and Removes
  void UpdateLists();
  
  void Add(Entity* entity);
  void Remove(Entity* entity);
  void RemoveAll();
  
  /* Lesser used memebers */
  void AddUpdate(Entity* entity);
  void RemoveUpdate(Entity* entity);
  void AddRender(Entity* entity);
  void RemoveRender(Entity* entity);
  
  //Get Current world camera
  inline draw::Camera GetCamera() {
    return camera_;
  };
  
  //Get Position of mouse with offset.
  inline Point GetMouse() {
    Point mouse_position = input.GetMousePosition();
    return (Point(camera_.position.x + mouse_position.x, 
                  camera_.position.y + mouse_position.y));
  };
  
  //inline int GetLayer(int layer, Container c );
  
  inline int LayerCount(int layer) {
    if (render_map_[layer] == NULL) return 0;
    return render_map_[layer]->size();
  };
  
  inline Entity* LayerFirst(int layer) {
    if (render_map_[layer] == NULL) return NULL;
    return render_map_[layer]->front();
  };
  
  inline Entity* LayerLast(int layer) {
    if (render_map_[layer] == NULL) return NULL;
    return render_map_[layer]->back();
  };
  
  inline int NearestLayer() {
    if (render_map_.empty()) return 0;
    return (*render_map_.end()).first;
  };
  
  inline int FarthestLayer() {
    if (render_map_.empty()) return 0;
    return (*render_map_.begin()).first;
  };
  
  inline int GetCount() {
    return count_;
  };
  
  inline bool IsVisible() {
    return visible_;
  };
  
  bool BringForward(Entity* entity);
  bool SendBackward(Entity* entity);
  
  bool BringToFront(Entity* entity);
  bool SendToBack(Entity* entity);
  
protected:
  
  typedef std::list< Entity* > EntityList;
  
  void AddType(Entity* entity);
  
  draw::Camera camera_;
  
  std::deque< Entity* > to_add_;
  std::deque< Entity* > to_remove_;
  
  std::list< Entity* > update_list_;
  //A map of layers to lists of enities
  std::map< int, EntityList*> render_map_;
  
  int count_;
  bool visible_;
  
private:
  int layer_count_;
};

//Map or priority queue

#endif

/*
 farthest	property	 
 farthest:Entity  [read-only]
 The Entity that will be rendered first by the World.
 public function get farthest():Entity 
 
 first	property	 
 first:Entity  [read-only]
 The first Entity in the World.
 public function get first():Entity 
 
 layerFarthest	property	 
 layerFarthest:int  [read-only]
 The layer that will be rendered first by the World.
 public function get layerFarthest():int
 
 layerNearest	property	 
 layerNearest:int  [read-only]
 The layer that will be rendered last by the World.
 public function get layerNearest():int 
 public function get nearest():Entity  
 
 
 uniqueTypes	property	 
 uniqueTypes:uint  [read-only]
 How many different types have been added to the World.
 public function get uniqueTypes():uint 
 
 addGraphic	()	method	 
 public function addGraphic(graphic:Graphic, layer:int = 0, x:int = 0, y:int = 0):Entity
 Adds an Entity to the World with the Graphic object.
 
 Parameters
 graphic:Graphic — Graphic to assign the Entity.
 layer:int (default = 0) — X position of the Entity.
 x:int (default = 0) — Y position of the Entity.
 y:int (default = 0) — Layer of the Entity.
 Returns
 Entity — The Entity that was added.
 
 addList	()	method	 
 public function addList(... list):void
 Adds multiple Entities to the world.
 Parameters
 ... list — Several Entities (as arguments) or an Array/Vector of Entities.
 
 addMask	()	method	 
 public function addMask(mask:Mask, type:String, x:int = 0, y:int = 0):Entity
 Adds an Entity to the World with the Mask object.
 
 Parameters
 mask:Mask — Mask to assign the Entity.
 type:String — Collision type of the Entity.
 x:int (default = 0) — X position of the Entity.
 y:int (default = 0) — Y position of the Entity.
 Returns
 Entity — The Entity that was added.
 
 bringToFront	()	method	 
 public function bringToFront(e:Entity):Boolean
 Brings the Entity to the front of its contained layer.
 Parameters
 e:Entity — The Entity to shift.
 Returns
 Boolean — If the Entity changed position.
 
 classCount	()	method	 
 public function classCount(c:Class):uint
 Returns the amount of Entities of the Class are in the World.
 Parameters
 c:Class — The Class type to count.
 Returns
 uint — How many Entities of Class exist in the World.
 
 classFirst	()	method	 
 public function classFirst(c:Class):Entity
 The first Entity of the Class.
 Parameters
 c:Class — The Class type to check.
 Returns
 Entity — The Entity.
 
 clearRecycled	()	method	 
 public static function clearRecycled(classType:Class):void
 Clears stored reycled Entities of the Class type.
 Parameters
 classType:Class — The Class type to clear.
 
 clearRecycledAll	()	method	 
 public static function clearRecycledAll():void
 Clears stored recycled Entities of all Class types.
 
 collideLine	()	method	 
 public function collideLine(type:String, fromX:int, fromY:int, toX:int, toY:int, precision:uint = 1, p:Point = null):Entity
 Returns the first Entity found that collides with the line.
 Parameters
 type:String — The Entity type to check for.
 fromX:int — Start x of the line.
 fromY:int — Start y of the line.
 toX:int — End x of the line.
 toY:int — End y of the line.
 precision:uint (default = 1)
 p:Point (default = null)
 Returns
 Entity
 
 collidePoint	()	method	 
 public function collidePoint(type:String, pX:Number, pY:Number):Entity
 Returns the first Entity found that collides with the position.
 Parameters
 type:String — The Entity type to check for.
 pX:Number — X position.
 pY:Number — Y position.
 Returns
 Entity — The collided Entity, or null if none collide.
 
 collidePointInto	()	method	 
 public function collidePointInto(type:String, pX:Number, pY:Number, into:Object):void
 Populates an array with all Entities that collide with the position. This function does not empty the array, that responsibility is left to the user.
 Parameters
 type:String — The Entity type to check for.
 pX:Number — X position.
 pY:Number — Y position.
 into:Object — The Array or Vector to populate with collided Entities.
 
 collideRect	()	method	 
 public function collideRect(type:String, rX:Number, rY:Number, rWidth:Number, rHeight:Number):Entity
 Returns the first Entity that collides with the rectangular area.
 Parameters
 type:String — The Entity type to check for.
 rX:Number — X position of the rectangle.
 rY:Number — Y position of the rectangle.
 rWidth:Number — Width of the rectangle.
 rHeight:Number — Height of the rectangle.
 Returns
 Entity — The first Entity to collide, or null if none collide.
 
 collideRectInto	()	method	 
 public function collideRectInto(type:String, rX:Number, rY:Number, rWidth:Number, rHeight:Number, into:Object):void
 Populates an array with all Entities that collide with the rectangle. This function does not empty the array, that responsibility is left to the user.
 Parameters
 type:String — The Entity type to check for.
 rX:Number — X position of the rectangle.
 rY:Number — Y position of the rectangle.
 rWidth:Number — Width of the rectangle.
 rHeight:Number — Height of the rectangle.
 into:Object — The Array or Vector to populate with collided Entities.
 
 create	()	method	 
 public function create(classType:Class, addToWorld:Boolean = true):Entity
 Returns a new Entity, or a stored recycled Entity if one exists.
 Parameters
 classType:Class — The Class of the Entity you want to add.
 addToWorld:Boolean (default = true) — Add it to the World immediately.
 Returns
 Entity — The new Entity object.

 focusGained	()	method	 
 public function focusGained():void
 Override this; called when game gains focus.
 
 focusLost	()	method	 
 public function focusLost():void
 Override this; called when game loses focus.
 
 getAll	()	method	 
 public function getAll(into:Object):void
 Pushes all Entities in the World into the array.
 Parameters
 into:Object — The Array or Vector to populate.
 
 getClass	()	method	 
 public function getClass(c:Class, into:Object):void
 Pushes all Entities in the World of the Class into the Array or Vector.
 Parameters
 c:Class — The Class type to check.
 into:Object — The Array or Vector to populate.
 
 getInstance	()	method	 
 public function getInstance(name:String):*
 Returns the Entity with the instance name, or null if none exists.
 Parameters
 name:String — Instance name of the Entity.
 Returns
 * — An Entity in this world.
 
 getLayer	()	method	 
 public function getLayer(layer:int, into:Object):void
 Pushes all Entities in the World on the layer into the Array or Vector.
 Parameters
 layer:int — The layer to check.
 into:Object — The Array or Vector to populate.
 
 getType	()	method	 
 public function getType(type:String, into:Object):void
 Pushes all Entities in the World of the type into the Array or Vector.
 Parameters
 type:String — The type to check.
 into:Object — The Array or Vector to populate.
 
 isAtBack	()	method	 
 public function isAtBack(e:Entity):Boolean
 If the Entity as at the back of its layer.
 Parameters
 e:Entity — The Entity to check.
 Returns
 Boolean — True or false.
 
 isAtFront	()	method	 
 public function isAtFront(e:Entity):Boolean
 If the Entity as at the front of its layer.
 Parameters
 e:Entity — The Entity to check.
 Returns
 Boolean — True or false.
  
 nearestToEntity	()	method	 
 public function nearestToEntity(type:String, e:Entity, useHitboxes:Boolean = false):Entity
 Finds the Entity nearest to another.
 Parameters
 type:String — The Entity type to check for.
 e:Entity — The Entity to find the nearest to.
 useHitboxes:Boolean (default = false) — If the Entities' hitboxes should be used to determine the distance. If false, their x/y coordinates are used.
 Returns
 Entity — The nearest Entity to e.
 
 nearestToPoint	()	method	 
 public function nearestToPoint(type:String, x:Number, y:Number, useHitboxes:Boolean = false):Entity
 Finds the Entity nearest to the position.
 Parameters
 type:String — The Entity type to check for.
 x:Number — X position.
 y:Number — Y position.
 useHitboxes:Boolean (default = false) — If the Entities' hitboxes should be used to determine the distance. If false, their x/y coordinates are used.
 Returns
 Entity — The nearest Entity to the position.
 
 nearestToRect	()	method	 
 public function nearestToRect(type:String, x:Number, y:Number, width:Number, height:Number, ignore:Entity = null):Entity
 Finds the Entity nearest to the rectangle.
 Parameters
 type:String — The Entity type to check for.
 x:Number — X position of the rectangle.
 y:Number — Y position of the rectangle.
 width:Number — Width of the rectangle.
 height:Number — Height of the rectangle.
 ignore:Entity (default = null) — Ignore this entity.
 Returns
 Entity — The nearest Entity to the rectangle.
 
 recycle	()	method	 
 public function recycle(e:Entity):Entity
 Removes the Entity from the World at the end of the frame and recycles it. The recycled Entity can then be fetched again by calling the create() function.
 Parameters
 e:Entity — The Entity to recycle.
 Returns
 Entity — The recycled Entity.
 
 removeAll	()	method	 
 public function removeAll():void
 Removes all Entities from the World at the end of the frame.
 
 removeList	()	method	 
 public function removeList(... list):void
 Removes multiple Entities from the world.
 Parameters
 ... list — Several Entities (as arguments) or an Array/Vector of Entities.

 
 sendToBack	()	method	 
 public function sendToBack(e:Entity):Boolean
 Sends the Entity to the back of its contained layer.
 Parameters
 e:Entity — The Entity to shift.
 Returns
 Boolean — If the Entity changed position.
 
 typeCount	()	method	 
 public function typeCount(type:String):uint
 Returns the amount of Entities of the type are in the World.
 Parameters
 type:String — The type (or Class type) to count.
 Returns
 uint — How many Entities of type exist in the World.
 
 typeFirst	()	method	 
 public function typeFirst(type:String):Entity
 The first Entity of the type.
 
 Parameters
 type:String — The type to check.
 Returns
 Entity — The Entity.
  
*/