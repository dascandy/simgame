#pragma once

#include "Map.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "glm.h"

class GameState {
public:
  GameState();
  void DebugDrawBullet(glm::mat4 vp);
  vec2 getCenter();
  void getDrawcalls(glm::mat4 vp, std::vector<Drawcall>&);
private:
  vec2 worldSize;
  Map map;
  btDbvtBroadphase broadphase;
  btDefaultCollisionConfiguration collisionConfiguration;
  btCollisionDispatcher dispatcher;
  btSequentialImpulseConstraintSolver solver;
  btDiscreteDynamicsWorld dynamicsWorld;
};

