#pragma once

#include <cstddef>
#include <memory>
#include <vector>
#include <glm.h>

struct Drawcall;
class MapTile;
class Object;

class Map {
public:
  Map(size_t w, size_t h);
  ~Map();
  size_t w, h;
  MapTile& operator()(size_t x, size_t y);
  void getDrawcalls(glm::mat4 vp, std::vector<Drawcall>&);
  void PlaceRoadX(size_t, size_t, size_t);
  void PlaceRoadY(size_t, size_t, size_t);
  void AddObject(std::unique_ptr<Object> obj);
  float getHeightAt(float x, float y);
private:
  std::vector<MapTile> mapTile;
};


