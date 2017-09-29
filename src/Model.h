#pragma once

#include <glm.h>
#include <map>
#include <string>
#include <vector>
#include "Vertex.h"
class Material;
struct CollisionMesh;

class Model {
public:
  Model(const std::string& str);
  Model(CollisionMesh* mesh) : mesh(mesh) {}
  static Model* Get(const std::string& str);
  uint16_t start, length;
  CollisionMesh* mesh;
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


