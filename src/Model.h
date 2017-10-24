#pragma once

#include <glm.h>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include "Vertex.h"
#include <bullet/btBulletDynamicsCommon.h>
class Material;
struct CollisionMesh;

class Model {
public:
  Model(const std::vector<Vertex>& vertices, std::mt19937& rng);
  void CreatePhysicsModel(const std::vector<std::string> &args, const std::vector<Vertex>& v);
  void WriteTo(const std::string& name);
  btRigidBody::btRigidBodyConstructionInfo Create(btMotionState* motionState);
  uint16_t start, length;
  std::unique_ptr<btCollisionShape> shape;
  float mass, masssd;
  std::mt19937& rng;
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


