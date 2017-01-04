#include "Map.h"
#include <assert.h>
#include "Model.h"
#include "Drawcall.h"
#include <glm/gtc/matrix_transform.hpp>
 
class Object;

int heightmap[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
  4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 
  4, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 
  4, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 
  4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
};

uint32_t rotateRightOne(uint32_t val) {
  return ((val >> 4) & 0x0FFF0FFF) | ((val << 12) & 0xF000F000);
}

struct MapTileType {
  MapTileType() {}
  MapTileType(uint8_t h1, uint8_t h2, uint8_t h3, uint8_t h4) {
    h = (h4 << 12) | (h3 << 8) | (h2 << 4) | (h1);
    t = 0;
  }
  uint16_t h = 0;
  uint16_t t = 0;
  enum : uint8_t {
    Water,
    Grass,
    Rock,
  } covertype = Grass;
  char coverToC(uint8_t type) {
    switch (type) {
      case Water: return 'w';
      case Grass: return 'g';
      case Rock: return 'r';
      case Sidewalk: return 's';
      default: assert(false);
    }
  }
  enum RoadType {
    None,
    Dirtroad,
    Asphalt,
    Tram,
    RiverIn,
    RiverOut,
  };
  int Minimize() {
    uint32_t h1 = (h << 16) | t;
    uint32_t h2 = rotateRightOne(h1);
    uint32_t h3 = rotateRightOne(h2);
    uint32_t h4 = rotateRightOne(h3);
    int rotation;
    uint32_t minH = std::min(std::min(h1, h2), std::min(h3, h4));
    if (h1 == minH) {
      rotation = 0;
    } else if (h2 == minH) {
      rotation = 1;
    } else if (h3 == minH) {
      rotation = 2;
    } else if (h4 == minH) {
      rotation = 3;
    }
    h = (h >> (rotation*4)) | (h << (16-rotation*4));
    t = (t >> (rotation*4)) | (t << (16-rotation*4));
    return rotation;
  }
  std::string toString() {
    char buffer[20];
    sprintf(buffer, "%04X_%04X_%c", h, t, coverToC(covertype));
    return buffer;
  }
};

class MapTile {
public:
  MapTile(uint16_t x, uint16_t y, uint8_t h1, uint8_t h2, uint8_t h3, uint8_t h4) 
  : x(x)
  , y(y)
  , model(nullptr)
  , rotation(0)
  {
    h = std::min(std::min(h1, h2), std::min(h3, h4));
    type = MapTileType(h1-h, h2-h, h3-h, h4-h);
  }
  uint16_t x, y;
  MapTileType type;
  Model* model;
  std::vector<Object*> staticObjects;
  int rotation;
  uint8_t h;
  void resolve() {
    rotation = type.Minimize();
    model = Model::Get("tiles/" + type.toString());
  }
  void getDrawcalls(glm::mat4 vp, std::vector<Drawcall>& calls) {
    calls.push_back(Drawcall{glm::rotate(glm::translate(vp, glm::vec3(x*21, h*5, y*21)), (float)((5-rotation) * M_PI / 2), glm::vec3(0, 1, 0)), model->start, model->length});
    for (auto& o : staticObjects) {
      // do something
    }
  }
};

void Map::PlaceRoadX(size_t start, size_t end, size_t y) {
  if (end < start) std::swap(start, end);
  for (; start < end; start++) {
    if ((mapTile[y*32+start].type.h != 0x0110 &&
         mapTile[y*32+start].type.h != 0x1001 &&
         mapTile[y*32+start].type.h != 0x0000) ||
        (mapTile[y*32+start+1].type.h != 0x0110 &&
         mapTile[y*32+start+1].type.h != 0x1001 &&
         mapTile[y*32+start+1].type.h != 0x0000)) {
      return;
    }

    mapTile[y*32+start  ].type.t |= 0x0020;
    mapTile[y*32+start+1].type.t |= 0x2000;
  }
}

void Map::PlaceRoadY(size_t start, size_t end, size_t x) {
  if (end < start) std::swap(start, end);
  for (; start < end; start++) {
    if ((mapTile[start*32+x].type.h != 0x1100 &&
         mapTile[start*32+x].type.h != 0x0011 &&
         mapTile[start*32+x].type.h != 0x0000) ||
        (mapTile[start*32+x+32].type.h != 0x1100 &&
         mapTile[start*32+x+32].type.h != 0x0011 &&
         mapTile[start*32+x+32].type.h != 0x0000)) {
      
      return;
    }

    mapTile[start*32+x  ].type.t |= 0x0200;
    mapTile[start*32+x+32].type.t |= 0x0002;
  }
}

Map::Map(size_t w, size_t h)
: w(w)
, h(h)
{
  mapTile.reserve(w * h);
  for (size_t y = 0; y < h; y++) {
    for (size_t x = 0; x < w; x++) {
      uint8_t h1 = heightmap[y*33+x];
      uint8_t h2 = heightmap[y*33+x+1];
      uint8_t h3 = heightmap[y*33+x+34];
      uint8_t h4 = heightmap[y*33+x+33];
      mapTile.emplace_back(x, y, h1, h2, h3, h4);
    }
  }
  PlaceRoadY(4, 24, 16);
  PlaceRoadX(4, 24, 16);
  PlaceRoadY(8, 16, 13);
  PlaceRoadX(8, 16, 13);
  for (auto& tile : mapTile) {
    tile.resolve();
  }
}

Map::~Map() {}

MapTile& Map::operator()(size_t x, size_t y) {
  assert(x < w);
  assert(y < h);
  return mapTile[y*w+x];
}

glm::vec2 Map::getCenter() {
  return glm::vec2(w*10, h*10);
}

void Map::getMapDrawcalls(glm::mat4 vp, std::vector<Drawcall>& calls) {
  for (auto& tile : mapTile) {
    tile.getDrawcalls(vp, calls);
  }
}


