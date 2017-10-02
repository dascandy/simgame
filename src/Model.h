#pragma once

#include <glm.h>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "Vertex.h"
#include <bullet/btBulletDynamicsCommon.h>
class Material;
struct CollisionMesh;

class Model {
public:
  Model(const std::string& str);
//:  Model(CollisionMesh* mesh) : mesh(mesh) {}
  static std::shared_ptr<Model> Get(const std::string& str);
  btRigidBody::btRigidBodyConstructionInfo Create(btMotionState* motionState);
  uint16_t start, length;
  std::unique_ptr<btCollisionShape> shape;
  float mass, masssd;
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


