#pragma once

#include <glm/glm.hpp>
#include <string>

class Material {
public:
  Material(const std::string& str);
  static Material* Get(const char* name);
  std::string name;
  glm::vec3 ambient, diffuse, specular;
  float specExponent;
};


