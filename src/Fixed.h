#pragma once

#include <stdint.h>
#include <stdio.h>

class Fixed {
public:
  int64_t value;
private:
  struct raw_ {} raw;
  Fixed(const raw_&, int64_t val) : value(val) {}
public:
  Fixed() : value(0) {}
  Fixed(int32_t val) : value(val * 0x100000000LL) {}
  Fixed& operator+=(const Fixed& f) {
    value += f.value;
    return *this;
  }
  Fixed operator+(const Fixed& f) const {
    Fixed rv;
    rv.value = value + f.value;
    return rv;
  }
  Fixed operator-(const Fixed& f) const {
    Fixed rv;
    rv.value = value - f.value;
    return rv;
  }
  Fixed operator*(const Fixed& f) const {
    __int128 val = f.value;
    val *= value;
    return Fixed{raw, static_cast<int64_t>(val >> 32)};
  }
  Fixed operator/(const Fixed& f) const {
    __int128 val = value;
    val <<= 32;
    val /= f.value;
    return Fixed{raw, static_cast<int64_t>(val)};
  }
  bool operator==(const Fixed& f) const {
    return f.value == value;
  }
  int highestbit(uint64_t val) const {
    int offs = 0;
    if ((val >> offs) & 0xFFFFFFFF00000000ULL) { offs += 32; }
    if ((val >> offs) & 0x00000000FFFF0000ULL) { offs += 16; }
    if ((val >> offs) & 0x000000000000FF00ULL) { offs += 8; }
    if ((val >> offs) & 0x00000000000000F0ULL) { offs += 4; }
    if ((val >> offs) & 0x000000000000000CULL) { offs += 2; }
    if ((val >> offs) & 0x0000000000000002ULL) { offs += 1; }
    return ((val >> offs) & 1) ? offs : -1;
  }
  int ToInt() const {
    return int(value >> 32);
  }
  double ToDouble() const {
    bool negative = false;
    uint64_t val = (uint64_t)value;
    if (val & 0x8000000000000000ULL) {
      negative = true;
      val = (~val) + 1;
    }
    if (val == 0) {
      return 0.0;
    }
    int highestBitSet = highestbit(val);
    uint64_t exponent = 991 + highestBitSet;
    if (highestBitSet > 52) {
      val >>= (highestBitSet - 52);
    } else if (highestBitSet < 52) {
      val <<= (52 - highestBitSet);
    }
    union {
      double d;
      uint64_t u;
    } conv;
    conv.u = (negative ? 0x8000000000000000ULL : 0) + (exponent << 52) + (val & 0xFFFFFFFFFFFFFULL);
    return conv.d;
  }
};

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

using vec3f = glm::tvec3<Fixed>;
using quatf = glm::tquat<Fixed>;

