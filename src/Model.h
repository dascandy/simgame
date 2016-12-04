#pragma once

#include <glm/glm.hpp>
#include <map>
#include <string>
#include <vector>
#include "Vertex.h"
class Material;
class Model {
private:
  void AddFace(Material* m, const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals, const std::string& v1, const std::string& v2, const std::string& v3);
public:
  Model(const std::string& str);
  static Model* Get(const char* name);
  std::map<Material*, std::vector<Vertex>> vertices;
};


