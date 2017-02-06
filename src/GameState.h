#pragma once

#include "Map.h"
#include "Physics.h"

class GameState {
public:
  GameState();
  Map map;
  PhysicsWorld world;
};

