#include "Fixed.h"

TEST(basicMath) {
  Fixed a = 1, b = 2, c(3), d = 4;
  Fixed ab = a*b;
  Fixed ac = a+c;
  Fixed two = d - b;
  Fixed dsq = ac * d;
  Fixed Athird = a / c;
  ASSERT(a.value == 1 * 4294967296);
  ASSERT(b.value == 2 * 4294967296);
  ASSERT(c.value == 3 * 4294967296);
  ASSERT(d.value == 4 * 4294967296);
  ASSERT(two == b);
  ASSERT(ac == d);
  ASSERT(ab == b);
  ASSERT(dsq.value == 16 * 4294967296);
  ASSERT(Athird.value == 1431655765);
}


