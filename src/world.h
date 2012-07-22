#ifndef WORLD_H
#define WORLD_H

#include "entity.h"
#include "geometry.h"
#include "draw.h"

using namespace geometry;
using namespace draw;

class World {
public:
  World();
  ~World();
  
  void Begin();
  void End();
  void Update();
  void Render();
  
  void Add();
  void Remove();
  void RemoveAll();
  
  inline Camera GetCamera() {
    return camera_;
  };
  
protected:
  Camera camera_;
};

#endif

/*Property detail
 camera	property
 public var camera:Point
 Point used to determine drawing offset in the render loop.
 
 count	property	 
 count:uint  [read-only]
 How many Entities are in the World.
 
 Implementation 
 public function get count():uint 
 farthest	property	 
 farthest:Entity  [read-only]
 The Entity that will be rendered first by the World.
 
 Implementation 
 public function get farthest():Entity 
 first	property	 
 first:Entity  [read-only]
 The first Entity in the World.
 
 Implementation 
 public function get first():Entity 
 layerFarthest	property	 
 layerFarthest:int  [read-only]
 The layer that will be rendered first by the World.
 
 Implementation 
 public function get layerFarthest():int 
 layerNearest	property	 
 layerNearest:int  [read-only]
 The layer that will be rendered last by the World.
 
 Implementation 
 public function get layerNearest():int 
 layers	property	 
 layers:uint  [read-only]
 How many Entity layers the World has.
 
 Implementation 
 public function get layers():uint 
 mouseX	property	 
 mouseX:int  [read-only]
 X position of the mouse in the World.
 
 Implementation 
 public function get mouseX():int 
 mouseY	property	 
 mouseY:int  [read-only]
 Y position of the mouse in the world.
 
 Implementation 
 public function get mouseY():int 
 nearest	property	 
 nearest:Entity  [read-only]
 The Entity that will be rendered last by the world.
 
 Implementation 
 public function get nearest():Entity 
 uniqueTypes	property	 
 uniqueTypes:uint  [read-only]
 How many different types have been added to the World.
 
 Implementation 
 public function get uniqueTypes():uint 
 visible	property	 
 public var visible:Boolean = true
 If the render() loop is performed.
 
 Constructor detail
 World	()	constructor
 public function World()
 Constructor.
 
 Method detail
 add	()	method
 public function add(e:Entity):Entity
 Adds the Entity to the World at the end of the frame.
 
 Parameters
 e:Entity — Entity object you want to add.
 Returns
 Entity — The added Entity object.
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
 begin	()	method	 
 public function begin():void
 Override this; called when World is switch to, and set to the currently active world.
 
 bringForward	()	method	 
 public function bringForward(e:Entity):Boolean
 Shifts the Entity one place towards the front of its contained layer.
 
 Parameters
 e:Entity — The Entity to shift.
 Returns
 Boolean — If the Entity changed position.
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
 end	()	method	 
 public function end():void
 Override this; called when World is changed, and the active world is no longer this.
 
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
 layerCount	()	method	 
 public function layerCount(layer:int):uint
 Returns the amount of Entities are on the layer in the World.
 
 Parameters
 layer:int — The layer to count Entities on.
 Returns
 uint — How many Entities are on the layer.
 layerFirst	()	method	 
 public function layerFirst(layer:int):Entity
 The first Entity on the Layer.
 
 Parameters
 layer:int — The layer to check.
 Returns
 Entity — The Entity.
 layerLast	()	method	 
 public function layerLast(layer:int):Entity
 The last Entity on the Layer.
 
 Parameters
 layer:int — The layer to check.
 Returns
 Entity — The Entity.
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
 remove	()	method	 
 public function remove(e:Entity):Entity
 Removes the Entity from the World at the end of the frame.
 
 Parameters
 e:Entity — Entity object you want to remove.
 Returns
 Entity — The removed Entity object.
 removeAll	()	method	 
 public function removeAll():void
 Removes all Entities from the World at the end of the frame.
 
 removeList	()	method	 
 public function removeList(... list):void
 Removes multiple Entities from the world.
 
 Parameters
 ... list — Several Entities (as arguments) or an Array/Vector of Entities.
 render	()	method	 
 public function render():void
 Performed by the game loop, renders all contained Entities. If you override this to give your World render code, remember to call super.render() or your Entities will not be rendered.
 
 sendBackward	()	method	 
 public function sendBackward(e:Entity):Boolean
 Shifts the Entity one place towards the back of its contained layer.
 
 Parameters
 e:Entity — The Entity to shift.
 Returns
 Boolean — If the Entity changed position.
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
 update	()	method	 
 public override function update():void
 Performed by the game loop, updates all contained Entities. If you override this to give your World update code, remember to call super.update() or your Entities will not be updated.
 
 updateLists	()	method	 
 public function updateLists():void
 Updates the add/remove lists at the end of the frame.
 
*/