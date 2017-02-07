#include "Physics.h"
#include "Object.h"
#include "Model.h"

PhysicsWorld::PhysicsWorld(Fixed ups) 
: ups(Fixed(1) / ups)
{

}

void Handle(Object* obj1, BoundingSphere* cm1, Object* obj2, WorldBox* cm2) {
  bool hit = false;
  if (obj1->p1.x < 0 && obj1->p0.x < cm2->lower.x) { hit = true; obj1->p1.x = -obj1->p1.x; }
  if (obj1->p1.y < 0 && obj1->p0.y < cm2->lower.y) { hit = true; obj1->p1.y = -obj1->p1.y; }
  if (obj1->p1.z < 0 && obj1->p0.z < cm2->lower.z) { hit = true; obj1->p1.z = -obj1->p1.z; }

  if (obj1->p1.x > 0 && obj1->p0.x > cm2->upper.x) { hit = true; obj1->p1.x = -obj1->p1.x; }
  if (obj1->p1.y > 0 && obj1->p0.y > cm2->upper.y) { hit = true; obj1->p1.y = -obj1->p1.y; }
  if (obj1->p1.z > 0 && obj1->p0.z > cm2->upper.z) { hit = true; obj1->p1.z = -obj1->p1.z; }

  if (hit) {
    obj1->p1 = obj1->p1 / Fixed(2);
  }
}

void CheckCollision(Object* obj1, CollisionMesh* cm1, Object* obj2, CollisionMesh* cm2) {
  switch(cm2->type) {
    case Type::WorldBox:
      switch(cm1->type) {
        case Type::BoundingSphere:
          Handle(obj1, (BoundingSphere*)cm1, obj2, (WorldBox*)cm2);
          break;
        default:
          fprintf(stderr, "Unimplemented: collision between %d and %d\n", (int)cm2->type, (int)cm1->type);
          assert(false);
      }
      break;
    default:
      fprintf(stderr, "Unimplemented: collision between %d and %d\n", (int)cm2->type, (int)cm1->type);
      assert(false);
  }

}

void PhysicsWorld::Step() {
  if (worldbox)
    for (auto& obj : objs) {
      CheckCollision(obj, obj->model->mesh, nullptr, worldbox.get());
    }
  // TODO: broadphase
  // TODO: collision detection
  // TODO: easing apart intersecting objects
  for (auto& obj : objs) {
    obj->StepPhysics(ups);
  }
}


