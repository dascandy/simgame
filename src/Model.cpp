#include "Model.h"
#include <StringUtils.h>
#include <fstream>
#include "Material.h"
#include <unordered_map>
#include <memory>
#include <GLAD/glad.h>

static void AddFace(std::vector<Vertex>& v, Material* m, const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals, const std::string& v1, const std::string& v2, const std::string& v3) {
  auto v1d = split(v1, '/', false),
       v2d = split(v2, '/', false),
       v3d = split(v3, '/', false);

  if (v1d.size() < 3 || v2d.size() < 3 || v3d.size() < 3) std::terminate();
  v.push_back(Vertex{positions[atoi(v1d[0].c_str())-1], normals[atoi(v1d[2].c_str())-1], m->id});
  v.push_back(Vertex{positions[atoi(v2d[0].c_str())-1], normals[atoi(v2d[2].c_str())-1], m->id});
  v.push_back(Vertex{positions[atoi(v3d[0].c_str())-1], normals[atoi(v3d[2].c_str())-1], m->id});
}

Model::Model(const std::string& str) {
  std::vector<Vertex> v;
  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  Material* mat = nullptr;

  std::ifstream f(str);
  assert(f.good() || (fprintf(stderr, "Can't read file %s\n", str.c_str()), 0));
  while (f.good()) {
    std::string line;
    std::getline(f, line);
    auto p = split(line);
    if (p.size() == 0) continue;
    if (p[0] == "usemtl") {
      mat = Material::Get(p[1].c_str());
    } else if (p[0] == "v") {
      positions.emplace_back(strtof(p[1].c_str(), nullptr), strtof(p[2].c_str(), nullptr), strtof(p[3].c_str(), nullptr));
    } else if (p[0] == "vn") {
      normals.emplace_back(strtof(p[1].c_str(), nullptr), strtof(p[2].c_str(), nullptr), strtof(p[3].c_str(), nullptr));
    } else if (p[0] == "f") {
      while (p.size() - 1 >= 3) {
        AddFace(v, mat, positions, normals, p[1], p[p.size() - 2], p[p.size() - 1]);
        p.pop_back();
      }
    }
  }

  start = Buffer::Instance().Add(v);
  length = v.size();
}

Model* Model::Get(const std::string& name) {
  static std::unordered_map<std::string, std::unique_ptr<Model>> models;
  auto& i = models[name];
  if (!i) {
    i = std::make_unique<Model>("assets/" + name + ".obj");
  }
  return i.get();
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
  glBufferData(GL_ARRAY_BUFFER, 100000 * sizeof(Vertex), nullptr, GL_STATIC_DRAW);
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
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

size_t Model::Buffer::Add(const std::vector<Vertex>& v) {
  Bind();
  size_t start = curVertex;
  curVertex += v.size();
  assert(curVertex <= 100000);
  glBufferSubData(GL_ARRAY_BUFFER, start * sizeof(Vertex), v.size() * sizeof(Vertex), v.data());
  return start;
}


