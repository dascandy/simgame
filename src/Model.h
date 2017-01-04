#pragma once

#include <glm/glm.hpp>
#include <map>
#include <string>
#include <vector>
#include "Vertex.h"
class Material;

class Model {
public:
  Model(const std::string& str);
  static Model* Get(const std::string& str);
  uint16_t start, length;
  class Buffer {
  private:
    Buffer();
    ~Buffer();
    size_t curVertex;
    unsigned int vbo, vao;
    size_t Add(const std::vector<Vertex>& vertices);
  public:
    static Buffer& Instance();
    void Bind();
    friend Model;
  };
};


