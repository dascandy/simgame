#include "ModelFactory.h"
#include "Model.h"
#include "ModelLoader.h"
#include "Assets.h"
#include <vector>
#include <cstddef>
#include "di.h"

std::shared_ptr<Model> ModelFactory::FromFile(const std::string& filename) {
  static std::mutex m;
  std::lock_guard<std::mutex> l(m);
  static std::map<std::string, std::shared_ptr<Model>> cachedModels;
  auto& model = cachedModels[filename];
  if (!model) {
    float mass = 0.0f, masssd = 0.0f;
    std::vector<std::string> physicsmodel = {"physicsmodel", "default" };
    std::vector<Vertex> v = loadModelData("assets/" + filename + ".obj", physicsmodel, mass, masssd);
    model = std::make_shared<Model>(v, rng);
    model->CreatePhysicsModel(physicsmodel, v);
    model->mass = mass;
    model->masssd = masssd;
  }
  return model;
}

std::shared_ptr<Model> ModelFactory::CreateBuilding(size_t x, size_t y, size_t volume, size_t height) {
  std::uniform_int_distribution<size_t> rx(0, x-1), ry(0, y-1);
  std::vector<Vertex> vertices;
  std::vector<size_t> floormap;
  floormap.resize(x*y);
  for (size_t n = 0; n < volume; n++) {
    size_t bx = rx(rng), by = ry(rng);
    if (floormap[by*x+bx] > height) continue;
    floormap[by*x+bx]++;
    Instantiate(vertices, DI::Get<Assets>()->squareWithWindow(), 5.0f, vec3(bx*5.0f, floormap[by*x+bx]*3.125f, by * 5.0f), quat());
  }

  // TODO: do we want a per building collision model, or rather a triangle soup?
  auto model = std::make_shared<Model>(vertices, rng);
  std::vector<std::string> physicsmodel = { "physicsmodel", "default" };
  model->CreatePhysicsModel(physicsmodel, vertices);
  printf("Created building\n");
  return model;
}

void ModelFactory::Instantiate(std::vector<Vertex>& nv, const char* modelName, float scale, vec3 pos, quat rot) {
  printf("%s\n", modelName);
  float mass = 0.0f, masssd = 0.0f;
  std::vector<std::string> physicsmodel;
  std::vector<Vertex> ov = loadModelData(modelName, physicsmodel, mass, masssd);
  for (auto& vert : ov) {
    nv.push_back(Vertex{(scale * vert.pos) * rot + pos, vert.normal * rot, vert.material});
  }
}

DEFINE_SERVICE(ModelFactory);
