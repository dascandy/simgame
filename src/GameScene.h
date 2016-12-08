#pragma once

#include "Scene.h"

class GameScene : public Scene {
public:
  GameScene();
  ~GameScene() override;
  void Update(size_t frameno) override;
  void Render() override;
  void Resize(size_t x, size_t y) override;
};

