// Embedded-friendly representation of useful RGB-based color spaces.

#pragma once

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
// Color space conversions
//

// Simple ratio RGB conversions (G ratio specified separately to allow 5:6:5)
#define G_RB_RATIO_BETWEEN(A, B, j, k, a, b) \
  inline A A##_from(B x) { return { x.r * a / b, x.g * j / k, x.b * a / b }; } \
  inline B B##_from(A x) { return { x.r * b / a, x.g * k / j, x.b * b / a }; }

// Simple ratio HSV conversions (H ratio specified separately)
#define H_SV_RATIO_BETWEEN(A, B, j, k, a, b) \
  inline A A##_from(B x) { return { x.h * j / k, x.s * a / b, x.v * a / b }; } \
  inline B B##_from(A x) { return { x.h * j / k, x.s * b / a, x.v * b / a }; }

// Multi-step conversions
#define CHAIN_BETWEEN(A, B, C) \
  inline A A##_from(C x) { return A##_from(B##_from(x)); } \
  inline C C##_from(A x) { return C##_from(B##_from(x)); } \

G_RB_RATIO_BETWEEN(ok_srgb16, ok_srgb24, 63, 255, 31, 255);
G_RB_RATIO_BETWEEN(ok_srgb16, ok_srgb48, 63, 65535, 31, 65535);
CHAIN_BETWEEN(ok_srgb16, ok_srgb24, ok_lrgb24);
CHAIN_BETWEEN(ok_srgb16, ok_srgb24, ok_lrgb48);
CHAIN_BETWEEN(ok_srgb16, ok_srgb24, ok_hsv24);
CHAIN_BETWEEN(ok_srgb16, ok_srgb24, ok_hsv360);
CHAIN_BETWEEN(ok_srgb16, ok_srgb48, ok_hsv32);
CHAIN_BETWEEN(ok_srgb16, ok_srgb48, ok_hsv48);

G_RB_RATIO_BETWEEN(ok_srgb24, ok_srgb48, 255, 65535, 255, 65535);
CHAIN_BETWEEN(ok_srgb24, ok_srgb48, ok_lrgb24);
CHAIN_BETWEEN(ok_srgb24, ok_srgb48, ok_lrgb48);
CHAIN_BETWEEN(ok_srgb24, ok_hsv32, ok_hsv24);
CHAIN_BETWEEN(ok_srgb24, ok_hsv32, ok_hsv360);
// ok_srgb24 <-> ok_hsv32 defined below
CHAIN_BETWEEN(ok_srgb24, ok_hsv32, ok_hsv48);

CHAIN_BETWEEN(ok_srgb48, ok_lrgb48, ok_lrgb24);
// ok_srgb48 <-> ok_lrgb48 defined below
CHAIN_BETWEEN(ok_srgb48, ok_srgb24, ok_hsv24);
CHAIN_BETWEEN(ok_srgb48, ok_srgb24, ok_hsv360);
CHAIN_BETWEEN(ok_srgb48, ok_hsv48, ok_hsv32);
// ok_srgb48 <-> ok_hsv48 defined below

G_RB_RATIO_BETWEEN(ok_lrgb24, ok_lrgb48, 255, 65535, 255, 65535);
CHAIN_BETWEEN(ok_lrgb24, ok_srgb24, ok_hsv24);
CHAIN_BETWEEN(ok_lrgb24, ok_srgb24, ok_hsv360);
CHAIN_BETWEEN(ok_lrgb24, ok_srgb48, ok_hsv32);
CHAIN_BETWEEN(ok_lrgb24, ok_srgb48, ok_hsv48);

CHAIN_BETWEEN(ok_lrgb48, ok_srgb24, ok_hsv24);
CHAIN_BETWEEN(ok_lrgb48, ok_srgb24, ok_hsv360);
CHAIN_BETWEEN(ok_lrgb48, ok_srgb48, ok_hsv32);
CHAIN_BETWEEN(ok_lrgb48, ok_srgb48, ok_hsv48);

H_SV_RATIO_BETWEEN(ok_hsv24, ok_hsv360, 255, 360, 255, 100);
H_SV_RATIO_BETWEEN(ok_hsv24, ok_hsv32, 255, 65535, 255, 255);
H_SV_RATIO_BETWEEN(ok_hsv24, ok_hsv48, 255, 65535, 255, 65535);

H_SV_RATIO_BETWEEN(ok_hsv360, ok_hsv32, 360, 65535, 255, 255);
H_SV_RATIO_BETWEEN(ok_hsv360, ok_hsv48, 360, 65535, 255, 65535);

H_SV_RATIO_BETWEEN(ok_hsv32, ok_hsv48, 65535, 65535, 255, 65535);

#undef G_RB_RATIO_BETWEEN
#undef H_SV_RATIO_BETWEEN
#undef CHAIN_BETWEEN

inline ok_srgb24 ok_srgb24_from(ok_hsv32 hsv) {
}

inline ok_hsv32 ok_hsv32_from(ok_srgb24 rgb) {
}

inline ok_srgb48 ok_srgb24_from(ok_hsv48 hsv) {
}

inline ok_hsv48 ok_hsv32_from(ok_srgb48 rgb) {
}

inline ok_srgb48 ok_srgb48_from(ok_lrgb48 lin) {
}

inline ok_lrgb48 ok_lrgb48_from(ok_srgb48 std) {
}
