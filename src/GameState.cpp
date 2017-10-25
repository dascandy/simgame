#include "GameState.h"
#include "di.h"
#include "BulletDebug.h"
#include "Model.h"
#include "Assets.h"
#include "Object.h"
#include "Drawcall.h"
#include "ModelFactory.h"

GameState::GameState()
: worldSize(2560, 2560)
, map(worldSize.x / 20, worldSize.y / 20)
, dispatcher(&collisionConfiguration)
, dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration)
{
  dynamicsWorld.setDebugDrawer(DI::Get<BulletDebug>().get());
  for (size_t n = 0; n < 500; n++) {
    float x = rand() % 2560, y = rand() % 2560;
    AddObject(std::make_unique<Object>(DI::Get<ModelFactory>()->FromFile(DI::Get<Assets>()->getRandomTree()), glm::vec3(x, map.getHeightAt(x, y), y), glm::quat()));
  }
  AddObject(std::make_unique<Object>(DI::Get<ModelFactory>()->FromFile("models/basicCharacter"), glm::vec3(1280, map.getHeightAt(1280, 1280), 1280), glm::quat()));
  dynamicsWorld.setGravity(btVector3(0, -10, 0));
  for (size_t x = 0; x < 16; x++) {
    for (size_t y = 0; y < 16; y++) {
      auto houseModel = DI::Get<ModelFactory>()->CreateBuilding(2, 3, 9, 2);
      auto myObj = std::make_unique<Object>(houseModel, glm::vec3(640 + 80 * x, map.getHeightAt(640+80*x, 640+80*y), 640+80*y), glm::quat());
      AddObject(std::move(myObj));
      char name[40];
      sprintf(name, "house%03zu.obj", y*16+x);
      houseModel->WriteTo(name);
    }
  }
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


