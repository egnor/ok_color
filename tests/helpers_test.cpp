#include "ok_color_helpers.h"

#include <functional>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("range helpers") {
  std::function<int(int)> to_small, to_large;
  int small_max, large_max;
  bool is_angle = false;

  SUBCASE("ok_5_8") {
    to_small = ok_8_5;
    to_large = ok_5_8;
    small_max = 31;
    large_max = 255;
  }

  SUBCASE("ok_5_16") {
    to_small = ok_16_5;
    to_large = ok_5_16;
    small_max = 31;
    large_max = 65535;
  }

  SUBCASE("ok_6_8") {
    to_small = ok_8_6;
    to_large = ok_6_8;
    small_max = 63;
    large_max = 255;
  }

  SUBCASE("ok_6_16") {
    to_small = ok_16_6;
    to_large = ok_6_16;
    small_max = 63;
    large_max = 65535;
  }

  SUBCASE("ok_8_8") {
    to_small = ok_8_8;
    to_large = ok_8_8;
    small_max = 255;
    large_max = 255;
  }

  SUBCASE("ok_8_pc") {
    to_small = ok_8_pc;
    to_large = ok_pc_8;
    small_max = 100;
    large_max = 255;
  }

  SUBCASE("ok_8_deg") {
    to_small = ok_deg_8;
    to_large = ok_8_deg;
    small_max = 255;
    large_max = 359;
  }

  SUBCASE("ok_8_16") {
    to_small = ok_16_8;
    to_large = ok_8_16;
    small_max = 255;
    large_max = 65535;
  }

  SUBCASE("ok_8_16_a") {
    to_small = ok_16_8_a;
    to_large = ok_8_16_a;
    small_max = 255;
    large_max = 65535;
    is_angle = true;
  }

  SUBCASE("ok_pc_16") {
    to_small = ok_16_pc;
    to_large = ok_pc_16;
    small_max = 100;
    large_max = 65535;
  }

  SUBCASE("ok_deg_16") {
    to_small = ok_16_deg;
    to_large = ok_deg_16;
    small_max = 359;
    large_max = 65535;
    is_angle = true;
  }

  SUBCASE("ok_16_16") {
    to_small = ok_16_16;
    to_large = ok_16_16;
    small_max = 65535;
    large_max = 65535;
  }

  CHECK(to_large(0) == 0);
  if (!is_angle) CHECK(to_large(small_max) == large_max);

  for (int small = 0; small <= small_max; ++small) {
    int const large = to_large(small);
    CAPTURE(small);
    CAPTURE(large);
    CHECK(to_small(large) == small);
  }

  int const expected_diff = (large_max + is_angle) / (small_max + is_angle);
  for (int small = 1; small <= small_max; ++small) {
    CAPTURE(small);
    auto const large_diff = to_large(small) - to_large(small - 1);
    CHECK(large_diff >= expected_diff);
    CHECK(large_diff <= expected_diff + 1);
  }

  for (int large = 1; large <= large_max; ++large) {
    CAPTURE(large);
    auto const small_diff = to_small(large) - to_small(large - 1);
    CHECK(small_diff >= 0);
    CHECK(small_diff <= 1);
  }
}
