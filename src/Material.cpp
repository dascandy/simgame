#include "Material.h"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <memory>
#include "StringUtils.h"

Material::Material(const std::string& str) {
  enum { Unknown, Name, Ambient, Diffuse, Specular, SpecularExponent } state = Unknown;
  size_t index = 0;
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
          ambient[index++] = atof(s.c_str());
          break;
        case Diffuse:
          diffuse[index++] = atof(s.c_str());
          break;
        case Specular:
          specular[index++] = atof(s.c_str());
          break;
        case SpecularExponent:
          specExponent = atof(s.c_str());
          break;
      }
    }
  }
}

Material* Material::Get(const char* name) {
  static std::unordered_map<std::string, std::unique_ptr<Material>> mats;
  if (mats.empty()) {
    std::ifstream mtlFile("assets/allmtls.mt");
    while (mtlFile.good()) {
      std::string line;
      std::getline(mtlFile, line);
      std::unique_ptr<Material> mat = std::make_unique<Material>(line);
      mats[mat->name] = std::move(mat);
    }
  }
  auto it = mats.find(name);
  if (it == mats.end()) {
    std::cerr << "Fatal: Unknown material used: " << name << std::endl;
    std::terminate();
  }
  return it->second.get();
}

