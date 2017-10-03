#pragma once

#include "Map.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "glm.h"
#include <vector>
#include <memory>
#include "Object.h"

class GameState {
public:
  GameState();
  void DebugDrawBullet(glm::mat4 vp);
  vec2 getCenter();
  void getDrawcalls(glm::mat4 vp, std::vector<Drawcall>&);
  void AddObject(std::unique_ptr<Object> obj);
private:
  std::vector<std::unique_ptr<Object>> objs;
  vec2 worldSize;
  Map map;
  btDbvtBroadphase broadphase;
  btDefaultCollisionConfiguration collisionConfiguration;
  btCollisionDispatcher dispatcher;
  btSequentialImpulseConstraintSolver solver;
  btDiscreteDynamicsWorld dynamicsWorld;
};

