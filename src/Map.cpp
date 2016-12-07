#include "Map.h"
#include <assert.h>

Map::Map(size_t w, size_t h)
: w(w)
, h(h)
{
  mapTile = std::make_unique<MapTile[]>(h*w);
}

Map::~Map() {}

MapTile& Map::operator()(size_t x, size_t y) {
  assert(x < w);
  assert(y < h);
  return mapTile[y*w+x];
}

