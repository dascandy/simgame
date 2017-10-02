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
  return trees[std::uniform_int_distribution<uint32_t>(0, count)(mt)];
}

DEFINE_SERVICE(Assets);
