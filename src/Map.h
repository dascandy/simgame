#pragma once

#include <cstddef>
#include <memory>
#include "view.h"
#include <vector>
#include <glm/glm.hpp>

struct Drawcall;
class MapTile;

class Map {
public:
  Map(size_t w, size_t h);
  ~Map();
  size_t w, h;
  MapTile& operator()(size_t x, size_t y);
  void getMapDrawcalls(glm::mat4 vp, std::vector<Drawcall>&);
  void PlaceRoadX(size_t, size_t, size_t);
  void PlaceRoadY(size_t, size_t, size_t);

  glm::vec2 getCenter();
private:
  std::vector<MapTile> mapTile;
};


