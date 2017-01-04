#pragma once

#include "Scene.h"
#include "ShaderProgram.h"
class GameState;

class GameScene : public Scene {
public:
  GameScene(GameState* state);
  ~GameScene() override;
  void OnKeypress(int key, int scancode, int action, int mods) override;
  void Update(size_t frameno) override;
  void Render() override;
  void Resize(size_t x, size_t y) override;
private:
  GameState* state;
  ShaderProgram shader;
  float ratio;
};

