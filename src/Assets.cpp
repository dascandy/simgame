#include "Assets.h"
#include "di.h"

const char* Assets::getRandomTree() {
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
  uint32_t treeId = std::uniform_int_distribution<uint32_t>(0, count-1)(mt);
  return trees[treeId];
}

const char* Assets::squareBuildingWithDoor() {
  static const char* models[] = {
    "assets/modular/Models/modularBuildings_069.obj",
    "assets/modular/Models/modularBuildings_053.obj",
    "assets/modular/Models/modularBuildings_054.obj",
    "assets/modular/Models/modularBuildings_055.obj",
    "assets/modular/Models/modularBuildings_028.obj",
    "assets/modular/Models/modularBuildings_023.obj"
  };
  size_t count = sizeof(models) / sizeof(models[0]);
  uint32_t modelId = std::uniform_int_distribution<uint32_t>(0, count-1)(mt);
  return models[modelId];
}

const char* Assets::squareWithWindow() {
  static const char* models[] = {
    "assets/modular/Models/modularBuildings_067.obj",
    "assets/modular/Models/modularBuildings_068.obj",
    "assets/modular/Models/modularBuildings_063.obj",
    "assets/modular/Models/modularBuildings_062.obj",
    "assets/modular/Models/modularBuildings_046.obj",
    "assets/modular/Models/modularBuildings_047.obj",
    "assets/modular/Models/modularBuildings_048.obj",
    "assets/modular/Models/modularBuildings_041.obj",
    "assets/modular/Models/modularBuildings_040.obj",
    "assets/modular/Models/modularBuildings_034.obj",
    "assets/modular/Models/modularBuildings_035.obj",
    "assets/modular/Models/modularBuildings_036.obj",
    "assets/modular/Models/modularBuildings_030.obj",
    "assets/modular/Models/modularBuildings_029.obj",
    "assets/modular/Models/modularBuildings_028.obj",
    "assets/modular/Models/modularBuildings_021.obj",
    "assets/modular/Models/modularBuildings_022.obj",
    "assets/modular/Models/modularBuildings_023.obj",
    "assets/modular/Models/modularBuildings_058.obj",
    "assets/modular/Models/modularBuildings_070.obj",
    "assets/modular/Models/modularBuildings_071.obj",
    "assets/modular/Models/modularBuildings_042.obj"
  };
  size_t count = sizeof(models) / sizeof(models[0]);
  uint32_t modelId = std::uniform_int_distribution<uint32_t>(0, count-1)(mt);
  return models[modelId];

}

const char* Assets::RaisedSquareWithDoor() {
  static const char* models[] = {
    "assets/modular/Models/modularBuildings_024.obj",
    "assets/modular/Models/modularBuildings_025.obj",
    "assets/modular/Models/modularBuildings_026.obj",
    "assets/modular/Models/modularBuildings_027.obj"
  };
  size_t count = sizeof(models) / sizeof(models[0]);
  uint32_t modelId = std::uniform_int_distribution<uint32_t>(0, count-1)(mt);
  return models[modelId];
}
/*
plat dak 
1x1 11
2x1 1/1
3x1 1/13/1
2x2 8/8/8/8
2x3 8/9/8 8/9/8

schuin dak


verhoging
vierkant 3/4/5

*/

DEFINE_SERVICE(Assets);
