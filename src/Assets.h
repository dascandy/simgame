#pragma once
#include <random>

class Assets {
private:
  std::mt19937 mt;
public:
  const char* getRandomTree();
  const char* squareBuildingWithDoor();
  const char* squareWithWindow();
  const char* RaisedSquareWithDoor();
};


