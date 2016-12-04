#include "StringUtils.h"
#include <vector>
#include <string>

static bool isWhitespace(char c) {
  return c < ' ';
}

std::vector<std::string> split(const std::string& str, char s, bool skipMultiple) {
  std::vector<std::string> out;
  auto it = str.begin();
  while (it != str.end()) {
    if (skipMultiple) 
      while (it != str.end() && (*it == s || isWhitespace(*it))) ++it;
    auto cur = it;
    while (it != str.end() && (*it != s && !isWhitespace(*it))) ++it;
    if (it != cur)
      out.emplace_back(cur, it);
    if (it != str.end()) ++it;
  }
  return out;
}

