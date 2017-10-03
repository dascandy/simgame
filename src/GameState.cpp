#include "GameState.h"
#include "di.h"
#include "BulletDebug.h"
#include "Model.h"
#include "Assets.h"
#include "Object.h"
#include "Drawcall.h"

GameState::GameState()
: worldSize(640, 640)
, map(worldSize.x / 20, worldSize.y / 20)
, dispatcher(&collisionConfiguration)
, dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration)
{
  dynamicsWorld.setDebugDrawer(DI::Get<BulletDebug>().get());
  for (size_t n = 0; n < 500; n++) {
    float x = rand() % 640, y = rand() % 640;
    AddObject(std::make_unique<Object>(Model::Get(DI::Get<Assets>()->getRandomTree()), glm::vec3(x, map.getHeightAt(x, y), y), glm::quat()));
  }
  AddObject(std::make_unique<Object>(Model::Get("models/basicCharacter"), glm::vec3(320, map.getHeightAt(320, 320), 320), glm::quat()));
  dynamicsWorld.setGravity(btVector3(0, -10, 0));
}

void GameState::AddObject(std::unique_ptr<Object> obj) {
  objs.push_back(std::move(obj));
  dynamicsWorld.addRigidBody(&objs.back()->rigidBody);
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
  for (auto& o : objs) {
    calls.push_back(Drawcall{glm::toMat4(o->getRotation()) * glm::translate(vp, o->getPosition()), o->model->start, o->model->length});
  }
}


