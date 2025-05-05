#include "ok_color_helpers.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("ok_conv_5_8") {
  for (int x = 0; x < 5; ++x) CHECK_MESSAGE(ok_conv_5_8(x) == 0, x);
  for (int x = 5; x < 13; ++x) CHECK_MESSAGE(ok_conv_5_8(x) == 1, x);
  for (int x = 13; x < 21; ++x) CHECK_MESSAGE(ok_conv_5_8(x) == 2, x);

  for (int x = 236; x < 243; ++x) CHECK_MESSAGE(ok_conv_5_8(x) == 29, x);
  for (int x = 243; x < 251; ++x) CHECK_MESSAGE(ok_conv_5_8(x) == 30, x);
  for (int x = 251; x < 256; ++x) CHECK_MESSAGE(ok_conv_5_8(x) == 31, x);

  CHECK(ok_conv_5_8_r(0) == 0);
  CHECK(ok_conv_5_8_r(1) == 8);
  CHECK(ok_conv_5_8_r(2) == 16);
  CHECK(ok_conv_5_8_r(29) == 239);
  CHECK(ok_conv_5_8_r(30) == 247);
  CHECK(ok_conv_5_8_r(31) == 255);
}
