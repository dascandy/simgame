#include "BulletDebug.h"
#include "glad.h"
#include "di.h"
#include "Settings.h"

void BulletDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) 
{
  uint32_t fromC = (uint8_t(fromColor.x() * 255) << 16) | (uint8_t(fromColor.y() * 255) << 8) | (uint8_t(fromColor.z() * 255) << 0);
  verticesLine.push_back(vert{vec3(from.x(), from.y(), from.z()), fromC});
  uint32_t toC = (uint8_t(toColor.x() * 255) << 16) | (uint8_t(toColor.y() * 255) << 8) | (uint8_t(toColor.z() * 255) << 0);
  verticesLine.push_back(vert{vec3(to.x(), to.y(), to.z()), toC});
}

void BulletDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) 
{
  uint32_t c = (uint8_t(color.x() * 255) << 16) | (uint8_t(color.y() * 255) << 8) | (uint8_t(color.z() * 255) << 0);
  verticesLine.push_back(vert{vec3(from.x(), from.y(), from.z()), c});
  verticesLine.push_back(vert{vec3(to.x(), to.y(), to.z()), c});
}

void BulletDebug::drawSphere(const btVector3& /*p*/, btScalar /*radius*/, const btVector3& /*color*/) 
{

}

void BulletDebug::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar /*alpha*/) 
{
  uint32_t col = (uint8_t(color.x() * 255) << 16) | (uint8_t(color.y() * 255) << 8) | (uint8_t(color.z() * 255) << 0);
  verticesTri.push_back(vert{vec3(a.x(), a.y(), a.z()), col});
  verticesTri.push_back(vert{vec3(b.x(), b.y(), b.z()), col});
  verticesTri.push_back(vert{vec3(c.x(), c.y(), c.z()), col});
}

void BulletDebug::drawContactPoint(const btVector3& /*PointOnB*/, const btVector3& /*normalOnB*/, btScalar /*distance*/, int /*lifeTime*/, const btVector3& /*color*/) 
{
  
}

void BulletDebug::reportErrorWarning(const char* warningString) 
{
  fprintf(stderr, "%s\n", warningString);
}

void BulletDebug::draw3dText(const btVector3& /*location*/, const char* /*textString*/) 
{
}

void BulletDebug::Render(glm::mat4 vp) 
{
  if (DI::Get<Settings>()->clearDepthBeforeBulletDebug)
    glClear(GL_DEPTH_BUFFER_BIT);
  shader.SetActive();
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  size_t numLine = verticesLine.size(), numTri = verticesTri.size();
  std::vector<vert> vertices;
  std::swap(vertices, verticesLine);
  vertices.insert(vertices.end(), verticesTri.begin(), verticesTri.end());
  verticesTri.clear();
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vert), vertices.data());
  shader.Set("mat_mvp", vp);
  glDrawArrays(GL_LINES, 0, numLine);
  glDrawArrays(GL_TRIANGLES, numLine, numTri);
}

int BulletDebug::getDebugMode() const {
  return DI::Get<Settings>()->bulletWireframe * 1 +
         DI::Get<Settings>()->bulletAabb * 2 +
         DI::Get<Settings>()->bulletFeaturesText * 4 +
         DI::Get<Settings>()->bulletContactPoints * 8 +
         DI::Get<Settings>()->bulletNoDeactivation * 16 +
         DI::Get<Settings>()->bulletNoHelpText * 32 +
         DI::Get<Settings>()->bulletDrawText * 64 +
         DI::Get<Settings>()->bulletProfileTimings * 128 +
         DI::Get<Settings>()->bulletEnableSatComparison * 256 +
         DI::Get<Settings>()->bulletDisableBulletLCP * 512 +
         DI::Get<Settings>()->bulletEnableCCD * 1024 +
         DI::Get<Settings>()->bulletDrawConstraints * 2048 +
         DI::Get<Settings>()->bulletDrawConstraintLimits * 4096 +
         DI::Get<Settings>()->bulletFastWireframe * 8192 +
         DI::Get<Settings>()->bulletDrawNormals * 16384 +
         DI::Get<Settings>()->bulletDrawFrames * 32768;
}

extern const char bulletdebug_vert[];
extern const char bulletdebug_frag[];

static const char*invars[] = {
  "in_loc",
  "in_col",
  nullptr
};

BulletDebug::BulletDebug()
: shader(__FILE__, bulletdebug_vert, bulletdebug_frag, invars)
{
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 131072 * sizeof(vert), nullptr, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(vert), (void*)12);
}

BulletDebug::~BulletDebug() {
  glDeleteBuffers(1, &vbo);
}

DEFINE_SERVICE(BulletDebug);

