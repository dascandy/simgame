#pragma once

#include <cstddef>
#include <memory>
#include <random>
#include "glm.h"
class Vertex;
class Model;

class ModelFactory {
public:
  std::shared_ptr<Model> FromFile(const std::string& filename);
  std::shared_ptr<Model> CreateBuilding(size_t x, size_t y, size_t volume, size_t height);
private:
  void Instantiate(std::vector<Vertex>& nv, const char* modelName, float scale, vec3 pos, quat rot);
  std::mt19937 rng;
};


