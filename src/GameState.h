#pragma once

#include "Map.h"
#include <bullet/btBulletDynamicsCommon.h>


class GameState {
public:
  GameState();
  Map map;
  btDbvtBroadphase broadphase;
  btDefaultCollisionConfiguration collisionConfiguration;
  btCollisionDispatcher dispatcher;
  btSequentialImpulseConstraintSolver solver;
  btDiscreteDynamicsWorld dynamicsWorld;

};

