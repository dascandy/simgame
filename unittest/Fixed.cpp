#include "Fixed.h"
#include "test.h"

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

TEST(asDouble) {
  Fixed Athird = Fixed(1) / 3;
  ASSERT(Athird.ToDouble() >= 0.333333);
  ASSERT(Athird.ToDouble() <= 0.333334);
}

TEST(asDoubleIncrements) {
  Fixed tinyF = Fixed(1) / 10;
  double tinyD = 0.1;
  Fixed accF = -2;
  double accD = -2;
  for (size_t n = 0; n < 50; n++) {
    ASSERT(accF.ToDouble() >= accD - 0.00000001);
    ASSERT(accF.ToDouble() <= accD + 0.00000001);
    accF += tinyF;
    accD += tinyD;
  }
}


