#include "Model.h"
#include "ModelLoader.h"
#include <StringUtils.h>
#include <fstream>
#include "Material.h"
#include <unordered_map>
#include <memory>
#include <mutex>
#include <glad.h>
#include <random>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>

Model::Model(const std::vector<Vertex>& v, std::mt19937& rng) 
: mass(0.0f)
, masssd(0.0f)
, rng(rng)
{
  start = Buffer::Instance().Add(v);
  length = v.size();
}

void Model::CreatePhysicsModel(const std::vector<std::string> &physicsmodel, const std::vector<Vertex>& v) {
  if (physicsmodel.size() >= 3 && physicsmodel[1] == "sphere") {
    shape = std::make_unique<btSphereShape>(strtof(physicsmodel[2].c_str(), nullptr));
  } else if (physicsmodel.size() >= 2 && physicsmodel[1] == "default") {
    btTriangleMesh trimesh;
    for (size_t i = 0; i < v.size(); i+=3)
    {
       btVector3 vertex0(v[i].pos.x, v[i].pos.y, v[i].pos.z);
       btVector3 vertex1(v[i+1].pos.x, v[i+1].pos.y, v[i+1].pos.z);
       btVector3 vertex2(v[i+2].pos.x, v[i+2].pos.y, v[i+2].pos.z);
       trimesh.addTriangle(vertex0, vertex1, vertex2);
    }
    btConvexTriangleMeshShape tmpShape(&trimesh);
    btShapeHull hull(&tmpShape);
    btScalar margin = tmpShape.getMargin();
    hull.buildHull(margin);
    shape = std::make_unique<btConvexHullShape>((btScalar*)hull.getVertexPointer(),hull.numVertices());
  } else {
    shape.reset();
  }
}

btRigidBody::btRigidBodyConstructionInfo Model::Create(btMotionState* motionState) {
  if (!shape) throw std::runtime_error("No physics model, no need to call Create");
  std::uniform_real_distribution<float> distr(0, 1.0f);
  // Sum of three floats gives a good approximation of a normal distribution without the chances of an outlier
  float a = distr(rng), b = distr(rng), c = distr(rng);
  float myMass = mass - 3*masssd + 2*masssd * (a + b + c);
  btVector3 inertia;
  shape->calculateLocalInertia(myMass, inertia);
  return btRigidBody::btRigidBodyConstructionInfo(mass, motionState, shape.get(), inertia);
}

Model::Buffer& Model::Buffer::Instance() {
  static Buffer buffer;
  return buffer;
}

Model::Buffer::Buffer() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  Bind();
  glBufferData(GL_ARRAY_BUFFER, 1000000 * sizeof(Vertex), nullptr, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*)24);
}

Model::Buffer::~Buffer() {
  glDeleteBuffers(1, &vbo);
}

void Model::Buffer::Bind() {
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

size_t Model::Buffer::Add(const std::vector<Vertex>& v) {
  Bind();
  size_t start = curVertex;
  curVertex += v.size();
  assert(curVertex <= 1000000);
  glBufferSubData(GL_ARRAY_BUFFER, start * sizeof(Vertex), v.size() * sizeof(Vertex), v.data());
  return start;
}


