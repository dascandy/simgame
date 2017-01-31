#include "Markov.h"
#include <fstream>

Markov::Markov(const char* inputFile, std::function<bool(const std::string&)> predicate)
: predicate(predicate)
{
  std::ifstream in(inputFile);
  while (in.good()) {
    std::string line;
    std::getline(in, line);
    line = "^^" + line + "$";
    for (size_t n = 0; n < line.size() - 2; n++) {
      chain[line.substr(n, 2)].push_back(line[n+2]);
    }
  }
}

// TODO: make use a random object
std::string Markov::getName() {
  std::string accum;
  do {
    accum.clear();
    std::string last = "^^";
    while (true) {
      auto& str = chain[last];
      char c = str[rand() % str.size()];
      if (c == '$') break;
      accum += c;
      last = (last + c).substr(1);
    }
  } while (!predicate(accum));
  return accum;
}


