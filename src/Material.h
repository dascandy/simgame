#pragma once

#include <glm.h>
#include <string>

class Material {
public:
  Material(const std::string& str, uint8_t id);
  static Material* Get(const char* name);
  std::string name;
  uint8_t id;
  static inline unsigned int GetBuffer() { return ubo; }
private:
  glm::vec3 ambient, diffuse, specular;
  float specExponent;
  static unsigned int ubo;
};


