// Embedded-friendly representation of useful RGB-based color spaces.

#pragma once

#include <algorithm>
#include <cstdint>

// 24-bit sRGB color as used in PC graphics, #xxxxxx codes, image files, etc.
// https://en.wikipedia.org/wiki/SRGB
//
// sRGB component values have a nonlinear "gamma", eg. r/g/b = 127 (50%)
// repreesnts only ~21% the optical intensity of r/g/b = 255 (100%).
// This is partly historical and partly to match human perception.
struct ok_srgb24 { uint8_t r, g, b; };

// 16-bit sRGB with 5 bit red (0-31), 6 bit green (0-63), and 5 bit blue (0-31).
struct ok_srgb16 { uint16_t r: 5, g: 6, b: 5; };

// 48-bit sRGB (0-65535 instead of 0-255).
struct ok_srgb48 { uint16_t r, g, b; };

// Linear 8-bit RGB as used for LED output, raw camera data, color mixing, etc.
// Uses the same primaries as sRGB but without the transfer function.
struct ok_lrgb24 { uint8_t r, g, b; }

// Linear 48-bit RGB (0-65535 instead of 0-255).
struct ok_lrgb48 { uint16_t r, g, b; };

// 24-bit HSV (Hue, Saturation, Value) based on sRGB (including gamma).
// All components range 0-255; hue 0=red, 85=green, 170=blue.
struct ok_hsv24 { uint8_t h, s, v; };

// 360-degree "decimal" HSV. Hue ranges 0-359, saturation and value range 0-100.
struct ok_hsv360 { uint16_t h; uint8_t s, v; };

// 32-bit HSV. Hue ranges 0-65535, saturation and value range 0-255.
struct ok_hsv32 { uint16_t h; uint8_t s, v; };

// 48-bit HSV. All components range 0-65535; hue 0=red, 21845=green, 43690=blue.
struct ok_hsv48 { uint16_t h, s, v; };

//
// Color space conversions: [ok_type]_from([ok_other_type] value)
//

// Range conversion helper
struct ok_ratio { const int num, den; }
int operator*(ok_ratio r, int x) { return (x * r.num + r.den / 2) / r.den; }
int operator/(ok_ratio r, int x) { return (x * r.den + r.num / 2) / r.num; }

// Simple ratio RGB conversions (G ratio specified separately to allow 5:6:5)
#define RB_G_RATIO(A, B, rat, g_rat) \
  inline A A##_from(B x) { return { x.r * rat, x.g * g_rat, x.b * rat }; } \
  inline B B##_from(A x) { return { x.r / rat, x.g * g_rat, x.b * rat }; }

// Simple ratio HSV conversions (H ratio specified separately)
#define H_SV_RATIO(A, B, h_rat, rat) \
  inline A A##_from(B x) { return { x.h * h_rat, x.s * rat, x.v * rat }; } \
  inline B B##_from(A x) { return { x.h / h_rat, x.s / rat, x.v * rat }; }

// Multi-step conversions
#define CHAIN(A, B, C) \
  inline A A##_from(C x) { return A##_from(B##_from(x)); } \
  inline C C##_from(A x) { return C##_from(B##_from(x)); } \

RB_G_RATIO(ok_srgb16, ok_srgb24, ok_ratio{31, 255}, ok_ratio{31, 255});
RB_G_RATIO(ok_srgb16, ok_srgb48, ok_ratio{31, 65535}, ok_ratio{63, 65535});
CHAIN(ok_srgb16, ok_srgb24, ok_lrgb24);
CHAIN(ok_srgb16, ok_srgb24, ok_lrgb48);
CHAIN(ok_srgb16, ok_srgb24, ok_hsv24);
CHAIN(ok_srgb16, ok_srgb24, ok_hsv360);
CHAIN(ok_srgb16, ok_srgb48, ok_hsv32);
CHAIN(ok_srgb16, ok_srgb48, ok_hsv48);

RB_G_RATIO(ok_srgb24, ok_srgb48, ok_ratio{255, 65535}, ok_ratio{255, 65535});
CHAIN(ok_srgb24, ok_srgb48, ok_lrgb24);
CHAIN(ok_srgb24, ok_srgb48, ok_lrgb48);
CHAIN(ok_srgb24, ok_hsv32, ok_hsv24);
CHAIN(ok_srgb24, ok_hsv32, ok_hsv360);
// ok_srgb24 <-> ok_hsv32 defined below
CHAIN(ok_srgb24, ok_hsv32, ok_hsv48);

CHAIN(ok_srgb48, ok_lrgb48, ok_lrgb24);
// ok_srgb48 <-> ok_lrgb48 defined below
CHAIN(ok_srgb48, ok_srgb24, ok_hsv24);
CHAIN(ok_srgb48, ok_srgb24, ok_hsv360);
CHAIN(ok_srgb48, ok_hsv48, ok_hsv32);
// ok_srgb48 <-> ok_hsv48 defined below

RB_G_RATIO(ok_lrgb24, ok_lrgb48, ok_ratio{255, 65535}, ok_ratio{255, 65535});
CHAIN(ok_lrgb24, ok_srgb24, ok_hsv24);
CHAIN(ok_lrgb24, ok_srgb24, ok_hsv360);
CHAIN(ok_lrgb24, ok_srgb48, ok_hsv32);
CHAIN(ok_lrgb24, ok_srgb48, ok_hsv48);
CHAIN(ok_lrgb48, ok_srgb24, ok_hsv24);
CHAIN(ok_lrgb48, ok_srgb24, ok_hsv360);
CHAIN(ok_lrgb48, ok_srgb48, ok_hsv32);
CHAIN(ok_lrgb48, ok_srgb48, ok_hsv48);

H_SV_RATIO(ok_hsv24, ok_hsv360, ok_ratio{255, 360}, ok_ratio{255, 100});
H_SV_RATIO(ok_hsv24, ok_hsv32, ok_ratio{255, 65535}, ok_ratio{255, 255});
H_SV_RATIO(ok_hsv24, ok_hsv48, ok_ratio{255, 65535}, ok_ratio{255, 65535});
H_SV_RATIO(ok_hsv360, ok_hsv32, ok_ratio{360, 65535}, ok_ratio{255, 255});
H_SV_RATIO(ok_hsv360, ok_hsv48, ok_ratio{360, 65535}, ok_ratio{255, 65535});
H_SV_RATIO(ok_hsv32, ok_hsv48, ok_ratio{65535, 65535}, ok_ratio{255, 65535});

#undef G_RB_RATIO
#undef H_SV_RATIO
#undef CHAIN

inline ok_srgb24 ok_srgb24_from(ok_hsv32 hsv) {
  uint8_t const range = hsv.v * hsv.s / 255;
  uint8_t const max = hsv.v, min = max - range;
  uint8_t const partial = (hsv.h * 6 % 65536) * range / 65536;
  switch (hsv.h * 6 / 65536) {
    case 0: return { max, min + partial, min };
    case 1: return { max - partial, max, min };
    case 2: return { min, max, min + partial };
    case 3: return { min, max - partial, max };
    case 4: return { min + partial, min, max };
    case 5: return { max, min, max - partial };
    default: return { 0, 0, 0 };  // unreachable
  }
}

inline ok_hsv32 ok_hsv32_from(ok_srgb24 rgb) {
  uint8_t const max = std::max({ rgb.r, rgb.g, rgb.b });
  uint8_t const min = std::min({ rgb.r, rgb.g, rgb.b });
  uint8_t const range = max - min;
  if (range == 0) return { 0, 0, max };

  uint8_t const sat = range * 255 / max;
  if (max == rgb.r && min == rgb.b) {
    return { (rgb.g - min) * 65536 / (range * 6), sat, max };
  } else if (max == rgb.g && min == rgb.b) {
    return { (max - rgb.r + range) * 65536 / (range * 6), sat, max };
  } else if (max == rgb.g && min == rgb.r) {
    return { (rgb.b - min + range * 2) * 65536 / (range * 6), sat, max };
  } else if (max == rgb.b && min == rgb.r) {
    return { (max - rgb.g + range * 3) * 65536 / (range * 6), sat, max };
  } else if (max == rgb.b && min == rgb.g) {
    return { (rgb.r - min + range * 4) * 65536 / (range * 6), sat, max };
  } else {
    return { (max - rgb.b + range * 5) * 65536 / (range * 6), sat, max };
  }
}

inline ok_srgb48 ok_srgb48_from(ok_hsv48 hsv) {
  uint16_t const range = hsv.v * hsv.s / 65535;
  uint16_t const max = hsv.v, min = max - range;
  uint16_t const partial = (hsv.h * 6 % 65536) * range / 65536;
  switch (hsv.h * 6 / 65536) {
    case 0: return { max, min + partial, min };
    case 1: return { max - partial, max, min };
    case 2: return { min, max, min + partial };
    case 3: return { min, max - partial, max };
    case 4: return { min + partial, min, max };
    case 5: return { max, min, max - partial };
    default: return { 0, 0, 0 };  // unreachable
  }
}

inline ok_hsv48 ok_hsv48_from(ok_srgb48 rgb) {
}

inline ok_srgb48 ok_srgb48_from(ok_lrgb48 lin) {
}

inline ok_lrgb48 ok_lrgb48_from(ok_srgb48 std) {
}
