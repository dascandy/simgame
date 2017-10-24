#include <glad.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <memory>
#include "Material.h"
#include "StringUtils.h"

unsigned int Material::ubo;

Material::Material(const std::string& str, uint8_t id) 
: id(id)
{
  enum { Unknown, Name, Ambient, Diffuse, Specular, SpecularExponent } state = Unknown;
  int index = 0;
  for (const auto& s : split(str)) {
    if (s == "newmtl") state = Name;
    else if (s == "Ka") { state = Ambient; index = 0; }
    else if (s == "Kd") { state = Diffuse; index = 0; }
    else if (s == "Ks") { state = Specular; index = 0; }
    else if (s == "Ns") state = SpecularExponent;
    else {
      switch(state) {
        case Unknown: std::cerr << "dunno what to do with " << s << " while parsing a material" << std::endl; std::terminate();
        case Name:
          name = s;
          break;
        case Ambient:
          ambient[index++] = strtof(s.c_str(), nullptr);
          break;
        case Diffuse:
          diffuse[index++] = strtof(s.c_str(), nullptr);
          break;
        case Specular:
          specular[index++] = strtof(s.c_str(), nullptr);
          break;
        case SpecularExponent:
          specExponent = strtof(s.c_str(), nullptr);
          break;
      }
    }
  }
}

struct gpu_material {
  glm::vec4 ambient, diffuse, specular;
};

static_assert(sizeof(gpu_material) == 48);

static std::unordered_map<std::string, std::unique_ptr<Material>> &getAllMaterials() {
  static std::unordered_map<std::string, std::unique_ptr<Material>> mats;
  if (mats.empty()) {
    uint8_t curid = 0;
    std::vector<gpu_material> gpu_mats;
    std::ifstream mtlFile("assets/allmtls.mt");
    while (mtlFile.good()) {
      std::string line;
      std::getline(mtlFile, line);
      std::unique_ptr<Material> mat = std::make_unique<Material>(line, curid++);
      gpu_material gm;
      gm.ambient = glm::vec4(mat->ambient.x, mat->ambient.y, mat->ambient.z, 0);
      gm.diffuse = glm::vec4(mat->diffuse.x, mat->diffuse.y, mat->diffuse.z, 0);
      gm.specular = glm::vec4(mat->specular.x, mat->specular.y, mat->specular.z, mat->specExponent);
      gpu_mats.push_back(gm);
      mats[mat->name] = std::move(mat);
    }

    gpu_mats.resize(64);
    glGenBuffers(1, &Material::ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, Material::ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(gpu_material) * gpu_mats.size(), gpu_mats.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }
  return mats;
}

Material* Material::Get(const char* name) {
  auto& mats = getAllMaterials();
  auto it = mats.find(name);
  if (it == mats.end()) {
    std::cerr << "Fatal: Unknown material used: " << name << std::endl;
    std::terminate();
  }
  return it->second.get();
}

Material* Material::Get(uint8_t id) {
  auto& mats = getAllMaterials();
  for (const auto& p : mats) {
    if (p.second->id == id) return p.second.get();
  }
  std::cerr << "Fatal: Unknown material used: " << id << std::endl;
  std::terminate();
}


