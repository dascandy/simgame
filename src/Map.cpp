#include "Map.h"
#include <assert.h>

Map::Map(size_t w, size_t h)
: w(w)
, h(h)
{
  mapTile = new MapTile[h*w];  
}

Map::~Map() {
  delete [] mapTile;
}

MapTile& Map::operator()(size_t x, size_t y) {
  assert(x < w);
  assert(y < h);
  return mapTile[y*w+x];
}


