#pragma once

#include "Scene.h"
class GameState;

class GameScene : public Scene {
public:
  GameScene(GameState* state);
  ~GameScene() override;
  void Update(size_t frameno) override;
  void Render() override;
  void Resize(size_t x, size_t y) override;
private:
  GameState* state;
};

