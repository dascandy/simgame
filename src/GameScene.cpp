#include <glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm.h>
#include "GameScene.h"
#include "GameState.h"
#include "Model.h"
#include "Material.h"

extern const char gamescene_vert[];
extern const char gamescene_frag[];

const char*invars[] = {
  "in_loc",
  "in_nrm",
  "in_prop",
  nullptr
};

GameScene::GameScene(GameState* state) 
: state(state)
, shader(__FILE__, gamescene_vert, gamescene_frag, invars)
{
  glEnable(GL_DEPTH_TEST);
  shader.SetActive();
  shader.SetUBO("materials", 0);
}

GameScene::~GameScene() {}

static bool pressed[128];

void GameScene::OnKeypress(int key, int scancode, int action, int mods) {
  pressed[key] = (action);
}

static float h = 24, r = M_PI / 4;
static glm::vec2 xy;
void GameScene::Update(size_t frameno) {
  if (pressed[GLFW_KEY_Q]) h += 0.1f;
  if (pressed[GLFW_KEY_E]) h -= 0.1f;
  if (pressed[GLFW_KEY_A]) xy += glm::vec2(0.1f*cos(r), 0.1f*sin(r));
  if (pressed[GLFW_KEY_D]) xy -= glm::vec2(0.1f*cos(r), 0.1f*sin(r));
  if (pressed[GLFW_KEY_W]) xy += glm::vec2(0.1f*-sin(r), 0.1f*cos(r));
  if (pressed[GLFW_KEY_S]) xy -= glm::vec2(0.1f*-sin(r), 0.1f*cos(r));
  if (pressed[GLFW_KEY_Z]) r -= 0.01f;
  if (pressed[GLFW_KEY_C]) r += 0.01f;
}

void GameScene::Resize(size_t x, size_t y) {
  ratio = x / (float)y;
}

struct Drawcall {
  glm::mat4 mvp;
  uint16_t offset, length;
};

void GameScene::Render() {
  glClearColor(0, 0, 0.2, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.SetActive();
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, Material::GetBuffer());
  std::vector<Drawcall> calls;
  glm::mat4 p = glm::perspective(1.0, (double)ratio, 1.0, 10000.0);
  glm::vec2 mapcenter = state->map.getCenter();
  glm::mat4 v = glm::mat4()
          * glm::rotate(glm::mat4(), -(float)M_PI/3, glm::vec3(1.0f, 0.0f, 0.0f))
          * glm::rotate(glm::mat4(), (float)M_PI/2, glm::vec3(1.0f, 0.0f, 0.0f)) 
          * glm::rotate(glm::mat4(), r, glm::vec3(0.0f, 1.0f, 0.0f)) 
          * glm::translate(glm::mat4(), glm::vec3(xy.x - mapcenter.x, -h, xy.y - mapcenter.y))
          ;
  state->map.getMapDrawcalls(p*v, calls);
  Model::Buffer::Instance().Bind();
  for (auto& d : calls) {
    shader.Set("mat_mvp", d.mvp);
    glDrawArrays(GL_TRIANGLES, d.offset, d.length);
  }
}


