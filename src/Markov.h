#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

class Markov {
public:
  Markov(const char* input, std::function<bool(const std::string&)> predicate);
  std::string getName();
private:
  std::unordered_map<std::string, std::string> chain;
  std::function<bool(const std::string&)> predicate;
};

