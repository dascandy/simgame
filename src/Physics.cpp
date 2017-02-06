#include "Physics.h"
#include "Object.h"

PhysicsWorld::PhysicsWorld(Fixed ups) 
: ups(ups)
{

}

void PhysicsWorld::Step() {
  Fixed step = Fixed(1) / ups;
  for (auto& obj : objs) {
    obj->StepPhysics(step);
  }
}


