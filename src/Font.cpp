#include <stdint.h>
#include "Font.h"
#include "Vertex.h"
#include "Material.h"

static const uint64_t chars[] = {
  0b00000011001001011110100101001000000, // A
  0b00000111001001011100100101110000000, // B
  0b00000011001001010000100100110000000, // C
  0b00000111001001010010100101110000000, // D
  0b00000111001000011000100001110000000, // E
  0b00000111001000011000100001000000000, // F
  0b00000011101000010110100100110000000, // G
  0b00000100101001011110100101001000000, // H
  0b00000100001000010000100001000000000, // I
  0b00000000100001000010100100110000000, // J
  0b00000100101010011000101001001000000, // K
  0b00000100001000010000100001110000000, // L
  0b00000100011101110101100011000100000, // M
  0b00000100011100110101100111000100000, // N
  0b00000011001001010010100100110000000, // O
  0b00000111001001011100100001000000000, // P
  0b00000011001001010010100100110000010, // Q
  0b00000111001001011100100101001000000, // R
  0b00000011101000000110000010111000000, // S
  0b00000111000100001000010000100000000, // T
  0b00000100101001010010100100110000000, // U
  0b00000100011000101010010100010000000, // V
  0b00000100011010110101101010101000000, // W
  0b00000100010101000100010101000100000, // X
  0b00000100010101000100001000010000000, // Y
  0b00000111000010001000100001110000000, // Z
  0b00000000000000000000000000000000000, // ' '
  0b00000111000001001100000000100000000, // ?
  0b00000100001000010000000001000000000, // !
  0b00100011101000001100100000111000100, // &
  0b00000011101010110110100000111000000, // @
  0b00100011101000001100000101110001000, // $
  0b00000011001001010010100100110000000, // 0
  0b00000110000100001000010001110000000, // 1
  0b00000111000001001100100001111000000, // 2
  0b00000111000001001100000101110000000, // 3
  0b00000001001010010100111100010000000, // 4
  0b00000111101000011100000101110000000, // 5
  0b00000011001000011100100100110000000, // 6
  0b00000111100001000100010000100000000, // 7
  0b00000011001001001100100100110000000, // 8
  0b00000011001001001110000100110000000, // 9
};

#define XSCALE 0.7
#define YSCALE 0.5
#define XOFF_SCALE 0.2

int getIndexFor(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A';
  } else if (c >= 'a' && c <= 'z') {
    return c - 'a';
  } else if (c >= '0' && c <= '9') {
    return c - '0' + 32;
  } else {
    switch(c) {
      case ' ': return 26; break;
      case '?': return 27; break;
      case '!': return 28; break;
      case '&': return 29; break;
      case '@': return 30; break;
      case '$': return 31; break;
    }
  }
  return -1;
}

std::vector<Vertex> getChar(char c) {
  std::vector<Vertex> rv;
  int index = getIndexFor(c);
  if (index >= 0) {
    Material* mat = Material::Get("Font");

    for (size_t y = 0; y < 7; y++) {
      for (size_t x = 0; x < 5; x++) {
        if ((chars[index] >> (y*5+x)) & 1) {
          rv.push_back(Vertex{glm::vec3(x*XSCALE + y*XOFF_SCALE               , y*YSCALE               , 0), glm::vec3(0, 1, 0), mat->id});
          rv.push_back(Vertex{glm::vec3(x*XSCALE + y*XOFF_SCALE + XSCALE * 0.9, y*YSCALE               , 0), glm::vec3(0, 1, 0), mat->id});
          rv.push_back(Vertex{glm::vec3(x*XSCALE + y*XOFF_SCALE + XSCALE * 0.9, y*YSCALE + YSCALE * 0.9, 0), glm::vec3(0, 1, 0), mat->id});
          rv.push_back(Vertex{glm::vec3(x*XSCALE + y*XOFF_SCALE + XSCALE * 0.9, y*YSCALE + YSCALE * 0.9, 0), glm::vec3(0, 1, 0), mat->id});
          rv.push_back(Vertex{glm::vec3(x*XSCALE + y*XOFF_SCALE               , y*YSCALE + YSCALE * 0.9, 0), glm::vec3(0, 1, 0), mat->id});
          rv.push_back(Vertex{glm::vec3(x*XSCALE + y*XOFF_SCALE               , y*YSCALE               , 0), glm::vec3(0, 1, 0), mat->id});
        }
      }
    }
  }
  return rv;
}

size_t getWidth(char c) {
  int index = getIndexFor(c);
  if (index == -1) return 0;
  if ((chars[index] & 0b01000010000100001000010000100001000) == 0) return 1;
  if ((chars[index] & 0b00100001000010000100001000010000100) == 0) return 2;
  if ((chars[index] & 0b00010000100001000010000100001000010) == 0) return 3;
  if ((chars[index] & 0b00001000010000100001000010000100001) == 0) return 4;
  return 5;
}


