#pragma once

#include <vector>
#include <string>
class Vertex;

std::vector<Vertex> loadModelData(const std::string& str, std::vector<std::string>& physicsmodel, float& mass, float& masssd);

