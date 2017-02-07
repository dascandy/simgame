#include "test.h"
#include "Physics.h"
#include "Fixed.h"
#include "Model.h"
#include "Object.h"

TEST(sphereFallsToGroundInTimeXWithNormalGravity) {
  PhysicsWorld world(60);
  BoundingSphere sphere(1);
  Model model(&sphere);
  Object obj(&model, vec3f(0, 0, 40), quatf());
  vec3f gravity(0, 0, Fixed(-981) / 100);
  world.objs.push_back(&obj);
  size_t n = 0;
  while (obj.p0.z >= Fixed(0)) {
    for (auto& obj : world) {
      obj->AddForce(obj->mass * gravity);
    }
    world.Step();
    n++;
  }
  ASSERT(n >= 170 && n <= 173);  // 2.86 seconds, give or take
}

TEST(sphereBouncesOnWorldbox) {
  PhysicsWorld world(60);
  world.worldbox = std::make_unique<WorldBox>(vec3f(-10, -10, 0), vec3f(10, 10, 100));
  BoundingSphere sphere(1);
  Model model(&sphere);
  Object obj(&model, vec3f(0, 0, 40), quatf());
  vec3f gravity(0, 0, Fixed(-981) / 100);
  world.objs.push_back(&obj);
  for (size_t n = 0; n < 1000; n++) {
    for (auto& obj : world) {
      obj->AddForce(obj->mass * gravity);
    }
    world.Step();
  }
  ASSERT(obj.p0.z > 0); // It bounced.
}

TEST(sphereBouncesOnWorldboxAndStopsAtSomePointWithDrag) {
  PhysicsWorld world(60);
  world.worldbox = std::make_unique<WorldBox>(vec3f(-10, -10, 0), vec3f(10, 10, 100));
  BoundingSphere sphere(1);
  Model model(&sphere);
  Object obj(&model, vec3f(0, 0, 40), quatf());
  vec3f gravity(0, 0, Fixed(-981) / 100);
  world.objs.push_back(&obj);
  for (size_t n = 0; n < 100000; n++) {
    for (auto& obj : world) {
      obj->AddForce(obj->mass * gravity);
      obj->AddForce(obj->p1 / Fixed(-128));
    }
    world.Step();
    std::cout << n << ": " << obj.p0 << " " << obj.p1 << "\n";
  }
}


