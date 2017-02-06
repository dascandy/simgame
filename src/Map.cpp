#include "Map.h"
#include <assert.h>
#include "Model.h"
#include "Drawcall.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Object.h"

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
    Sidewalk,
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
  void AddObject(std::unique_ptr<Object> obj) {
    staticObjects.push_back(std::move(obj));
  }
  std::vector<std::unique_ptr<Object>> staticObjects;
  int rotation;
  uint8_t h;
  void resolve() {
    rotation = type.Minimize();
    model = Model::Get("tiles/" + type.toString());
  }
  void getDrawcalls(glm::mat4 vp, std::vector<Drawcall>& calls) {
    calls.push_back(Drawcall{glm::rotate(glm::translate(vp, glm::vec3(x*20, h*5, y*20)), (float)((5-rotation) * M_PI / 2), glm::vec3(0, 1, 0)), model->start, model->length});
    for (auto& o : staticObjects) {
      glm::vec3 p(o->p0.x.ToDouble(), o->p0.y.ToDouble(), o->p0.z.ToDouble());
      glm::quat r(o->r0.x.ToDouble(), o->r0.y.ToDouble(), o->r0.z.ToDouble(), o->r0.w.ToDouble());
      calls.push_back(Drawcall{glm::toMat4(r) * glm::translate(vp, p), o->model->start, o->model->length});
    }
  }
  float getHeight(float x, float y) {
    switch(type.h) {
      case 0x0000: return h*5;
      case 0x0001: 
      case 0x0011:
      case 0x0111: return h * 5 + 5;
      default: fprintf(stderr, "%04X\n", type.h); assert(false);
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

static const char* getRandomTree() {
  const char* trees[] = {
    "models/naturePack_051",
    "models/naturePack_052",
    "models/naturePack_053",
    "models/naturePack_054",
    "models/naturePack_055",
    "models/naturePack_056",
    "models/naturePack_061",
    "models/naturePack_062",
    "models/naturePack_063",
    "models/naturePack_064",
    "models/naturePack_065",
    "models/naturePack_066",
    "models/naturePack_067",
    "models/naturePack_068",
    "models/naturePack_069",
    "models/naturePack_070",
    "models/naturePack_071",
    "models/naturePack_072",
    "models/naturePack_073",
    "models/naturePack_074",
    "models/naturePack_081",
    "models/naturePack_084",
    "models/naturePack_085",
    "models/naturePack_087",
    "models/naturePack_088",
    "models/naturePack_089",
    "models/naturePack_094",
    "models/naturePack_114",
    "models/naturePack_129",
    "models/naturePack_130",
    "models/naturePack_139",
    "models/naturePack_140",
    "models/naturePack_148",
    "models/naturePack_149",
    "models/naturePack_150",
    "models/naturePack_151",
    "models/naturePack_159",
    "models/naturePack_160",
    "models/naturePack_161",
    "models/naturePack_162",
    "models/naturePack_163",
    "models/naturePack_164",
    "models/naturePack_165",
    "models/naturePack_166",
    "models/naturePack_167",
    "models/naturePack_168",
    "models/naturePack_169",
  };
  size_t count = sizeof(trees) / sizeof(trees[0]);
  return trees[rand() % count];
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
  for (size_t n = 0; n < 500; n++) {
    float x = rand() % 640, y = rand() % 640;
    AddObject(std::make_unique<Object>(Model::Get(getRandomTree()), glm::vec3(x, getHeightAt(x, y), y), glm::quat()));
  }
  AddObject(std::make_unique<Object>(Model::Get("models/basicCharacter"), glm::vec3(320, getHeightAt(320, 320), 320), glm::quat()));
}

void Map::AddObject(std::unique_ptr<Object> obj) {
  int xoff = int(obj->p0.x.ToInt() / 20);
  int yoff = int(obj->p0.y.ToInt() / 20);
  assert(xoff > 0 && xoff < w);
  assert(yoff > 0 && yoff < h);
  auto& tile = mapTile[yoff * w + xoff];
  tile.AddObject(std::move(obj));
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

float Map::getHeightAt(float x, float y) {
  size_t xoff = size_t(x / 20);
  size_t yoff = size_t(y / 20);
  auto& tile = mapTile[yoff * w + xoff];
  float xd = x - xoff * 20, yd = y - yoff * 20;
  return tile.getHeight(xd, yd);
}

void Map::getMapDrawcalls(glm::mat4 vp, std::vector<Drawcall>& calls) {
  for (auto& tile : mapTile) {
    tile.getDrawcalls(vp, calls);
  }
}


