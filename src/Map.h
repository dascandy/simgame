#pragma once

#include <cstddef>
#include <memory>

class MapTile {
  
};

class Map {
public:
  Map(size_t w, size_t h);
  ~Map();
  size_t w, h;
  MapTile& operator()(size_t x, size_t y);
private:
  std::unique_ptr<MapTile[]> mapTile;
};


