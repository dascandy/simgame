#pragma once

class Fixed {
private:
  int64_t value;
public:
  Fixed(int64_t val) : value(val) {}
  Fixed operator+(const Fixed& f) {
    Fixed rv;
    rv.value = value + f.value;
  }
  Fixed operator-(const Fixed& f) {
    Fixed rv;
    rv.value = value - f.value;
  }
  Fixed operator*(const Fixed& f) {
    __int128 val = f.value;
    val *= value;
    return Fixed{val >> 32};
  }
  Fixed operator/(const Fixed& f) {
    __int128 val = value;
    val <<= 32;
    val /= f.value;
    return Fixed{val};
  }
};


