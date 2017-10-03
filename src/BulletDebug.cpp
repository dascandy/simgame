#include "BulletDebug.h"
#include "glad.h"
#include "di.h"

void BulletDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) 
{
  uint32_t fromC = (uint8_t(fromColor.x() * 255) << 16) | (uint8_t(fromColor.y() * 255) << 8) | (uint8_t(fromColor.z() * 255) << 0);
  verticesLine.push_back(vert{vec3(from.x(), from.y(), from.z()), fromC});
  uint32_t toC = (uint8_t(toColor.x() * 255) << 16) | (uint8_t(toColor.y() * 255) << 8) | (uint8_t(toColor.z() * 255) << 0);
  verticesLine.push_back(vert{vec3(to.x(), to.y(), to.z()), toC});
}

void BulletDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) 
{

}

void BulletDebug::drawSphere(const btVector3& p, btScalar radius, const btVector3& color) 
{

}

void BulletDebug::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha) 
{

}

void BulletDebug::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) 
{

}

void BulletDebug::reportErrorWarning(const char* warningString) 
{

}

void BulletDebug::draw3dText(const btVector3& location, const char* textString) 
{

}

void BulletDebug::Render(glm::mat4 vp) 
{
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
