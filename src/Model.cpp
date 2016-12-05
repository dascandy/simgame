#include "Model.h"
#include <StringUtils.h>
#include <fstream>
#include "Material.h"
#include <unordered_map>
#include <memory>

Model::Model(const std::string& str) {
  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  Material* mat = NULL;

  std::ifstream f(str);
  while (f.good()) {
    std::string line;
    std::getline(f, line);
    auto p = split(line);
    if (p.size() == 0) continue;
    if (p[0] == "usemtl") {
      mat = Material::Get(p[1].c_str());
    } else if (p[0] == "v") {
      positions.emplace_back(strtof(p[1].c_str(), NULL), strtof(p[2].c_str(), NULL), strtof(p[3].c_str(), NULL));
    } else if (p[0] == "vn") {
      normals.emplace_back(strtof(p[1].c_str(), NULL), strtof(p[2].c_str(), NULL), strtof(p[3].c_str(), NULL));
    } else if (p[0] == "f") {
      while (p.size() - 1 >= 3) {
        AddFace(mat, positions, normals, p[1], p[p.size() - 2], p[p.size() - 1]);
        p.pop_back();
      }
    }
  }
}

void Model::AddFace(Material* m, const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals, const std::string& v1, const std::string& v2, const std::string& v3) {
  auto v1d = split(v1, '/', false),
       v2d = split(v2, '/', false),
       v3d = split(v3, '/', false);

  if (v1d.size() < 3 || v2d.size() < 3 || v3d.size() < 3) std::terminate();
  auto& v = vertices[m];
  v.push_back(Vertex{positions[atoi(v1d[0].c_str())-1], normals[atoi(v1d[2].c_str())-1]});
  v.push_back(Vertex{positions[atoi(v2d[0].c_str())-1], normals[atoi(v2d[2].c_str())-1]});
  v.push_back(Vertex{positions[atoi(v3d[0].c_str())-1], normals[atoi(v3d[2].c_str())-1]});
}

Model* Model::Get(const char* name) {
  static std::unordered_map<std::string, std::unique_ptr<Model>> models;
  auto& i = models[name];
  if (!i) {
    i.reset(new Model(std::string("assets/models/") + name + ".obj"));
  }
  return i.get();
}


