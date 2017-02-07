#include "Physics.h"
#include "Object.h"

PhysicsWorld::PhysicsWorld(Fixed ups) 
: ups(Fixed(1) / ups)
{

}

void PhysicsWorld::Step() {
  for (auto& obj : objs) {
    obj->StepPhysics(ups);
  }
}


