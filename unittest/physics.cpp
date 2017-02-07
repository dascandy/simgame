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
  for (size_t n = 0; n < 100; n++) {
    for (auto& obj : world) {
      obj->AddForce(obj->mass * gravity);
    }
    world.Step();
    printf("%f %f %f\n", obj.p0.x.ToDouble(), obj.p0.y.ToDouble(), obj.p0.z.ToDouble());
  }
}


