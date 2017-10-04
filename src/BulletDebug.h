#pragma once

#include "LinearMath/btIDebugDraw.h"
#include "glm.h"
#include <vector>
#include <cstdint>
#include "ShaderProgram.h"

class BulletDebug : public btIDebugDraw
{
  struct vert {
    vec3 pos;
    uint32_t color;
  };
  static_assert(sizeof(vert) == 16);
  std::vector<vert> verticesLine;
  std::vector<vert> verticesTri;
  ShaderProgram shader;
  unsigned int vbo, vao;
public:
  BulletDebug();
  ~BulletDebug();
  void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) override;
  void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
  void drawSphere(const btVector3& p, btScalar radius, const btVector3& color) override;
  void drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha) override;
  void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
  void reportErrorWarning(const char* warningString) override;
  void draw3dText(const btVector3& location, const char* textString) override;
  void setDebugMode(int ) override {}
  int getDebugMode() const override;

  void Render(glm::mat4 vp);
};
