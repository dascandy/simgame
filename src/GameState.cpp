#include "GameState.h"
#include "di.h"
#include "BulletDebug.h"

GameState::GameState()
: worldSize(640, 640)
, map(worldSize.x / 20, worldSize.y / 20)
, dispatcher(&collisionConfiguration)
, dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration)
{
  dynamicsWorld.setDebugDrawer(DI::Get<BulletDebug>().get());
}

void GameState::DebugDrawBullet(glm::mat4 vp) {
  dynamicsWorld.debugDrawWorld();
  DI::Get<BulletDebug>()->Render(vp);
}

glm::vec2 GameState::getCenter() {
  return worldSize / 2.0f;
}

void GameState::getDrawcalls(glm::mat4 vp, std::vector<Drawcall>& calls) {
  map.getDrawcalls(vp, calls);
}


