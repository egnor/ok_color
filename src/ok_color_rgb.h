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

// Color space conversions

#define CHAIN_FROM(ta, tb, tc) \
  inline ta ta##_from(tc c) { return ta##_from(tb##_from(c)); }

ok_srgb24 ok_srgb24_from(ok_srgb16);
ok_srgb24 ok_srgb24_from(ok_srgb48);
ok_srgb24 ok_srgb24_from(ok_lrgb24);
ok_srgb24_ok_srgb24_from(ok_lrgb48);
ok_srgb24 ok_srgb24_from(ok_hsv24);
ok_srgb24 ok_srgb24_from(ok_hsv360);
ok_srgb24 ok_srgb24_from(ok_hsv32);
ok_srgb24 ok_srgb24_from(ok_hsv48);

ok_srgb16 ok_srgb16_from(ok_srgb24);
ok_srgb16 ok_srgb16_from(ok_srgb48);
CHAIN_FROM(ok_srgb16, ok_srgb24, ok_lrgb24);
CHAIN_FROM(ok_srgb16, ok_srgb24, ok_lrgb48);
CHAIN_FROM(ok_srgb16, ok_srgb24, ok_hsv24);
CHAIN_FROM(ok_srgb16, ok_srgb24, ok_hsv360);
CHAIN_FROM(ok_srgb16, ok_srgb24, ok_hsv32);
CHAIN_FROM(ok_srgb16, ok_srgb24, ok_hsv48);

ok_srgb48 ok_srgb48_from(ok_srgb24);
ok_srgb48 ok_srgb48_from(ok_srgb16);
ok_srgb48 ok_srgb48_from(ok_lrgb24);
ok_srgb48 ok_srgb48_from(ok_lrgb48);
CHAIN_FROM(ok_srgb48, ok_srgb24, ok_hsv24);
CHAIN_FROM(ok_srgb48, ok_srgb24, ok_hsv360);
ok_srgb48 ok_srgb48_from(ok_hsv32);
ok_srgb48 ok_srgb48_from(ok_hsv48);

ok_lrgb24 ok_lrgb24_from(ok_srgb24);
CHAIN_FROM(ok_lrgb24, ok_srgb24, ok_srgb16);
ok_lrgb24 ok_lrgb24_from(ok_srgb48);
ok_lrgb24 ok_lrgb24_from(ok_lrgb48);
CHAIN_FROM(ok_lrgb24, ok_srgb24, ok_hsv24);
CHAIN_FROM(ok_lrgb24, ok_srgb24, ok_hsv360);
CHAIN_FROM(ok_lrgb24, ok_srgb48, ok_hsv32);
CHAIN_FROM(ok_lrgb24, ok_srgb48, ok_hsv48);

ok_lrgb48 ok_lrgb48_from(ok_srgb24);
CHAIN_FROM(ok_lrgb48, ok_srgb24, ok_srgb16);
ok_lrgb48 ok_lrgb48_from(ok_srgb48);
ok_lrgb48 ok_lrgb48_from(ok_lrgb24);
CHAIN_FROM(ok_lrgb48, ok_srgb24, ok_hsv24);
CHAIN_FROM(ok_lrgb48, ok_srgb24, ok_hsv360);
CHAIN_FROM(ok_lrgb48, ok_srgb48, ok_hsv32);
CHAIN_FROM(ok_lrgb48, ok_srgb48, ok_hsv48);

ok_hsv24 ok_hsv24_from(ok_srgb24);
CHAIN_FROM(ok_hsv24, ok_srgb24, ok_srgb16);
CHAIN_FROM(ok_hsv24, ok_srgb24, ok_srgb48);
CHAIN_FROM(ok_hsv24, ok_srgb24, ok_lrgb24);
CHAIN_FROM(ok_hsv24, ok_srgb24, ok_lrgb48);
ok_hsv24 ok_hsv24_from(ok_hsv360);
ok_hsv24 ok_hsv24_from(ok_hsv32);
ok_hsv24 ok_hsv24_from(ok_hsv48);

ok_hsv360 ok_hsv360_from(ok_srgb24);
CHAIN_FROM(ok_hsv360, ok_srgb24, ok_srgb16);
CHAIN_FROM(ok_hsv360, ok_srgb24, ok_srgb48);
CHAIN_FROM(ok_hsv360, ok_srgb24, ok_lrgb24);
CHAIN_FROM(ok_hsv360, ok_srgb24, ok_lrgb48);
ok_hsv360 ok_hsv360_from(ok_hsv24);
ok_hsv360 ok_hsv360_from(ok_hsv32);
ok_hsv360 ok_hsv360_from(ok_hsv48);

ok_hsv32 ok_hsv32_from(ok_srgb24);
CHAIN_FROM(ok_hsv32, ok_srgb24, ok_srgb16);
ok_hsv32 ok_hsv32_from(ok_srgb48);
CHAIN_FROM(ok_hsv32, ok_srgb48, ok_lrgb24);
CHAIN_FROM(ok_hsv32, ok_srgb48, ok_lrgb48);
ok_hsv32 ok_hsv32_from(ok_hsv24);
ok_hsv32 ok_hsv32_from(ok_hsv360);
ok_hsv32 ok_hsv32_from(ok_hsv48);

ok_hsv48 ok_hsv48_from(ok_srgb24);
CHAIN_FROM(ok_hsv48, ok_srgb24, ok_srgb16);
ok_hsv48 ok_hsv48_from(ok_srgb48);
CHAIN_FROM(ok_hsv48, ok_srgb48, ok_lrgb24);
CHAIN_FROM(ok_hsv48, ok_srgb48, ok_lrgb48);
CHAIN_FROM(ok_hsv48, ok_hsv32, ok_hsv24);
ok_hsv48 ok_hsv48_from(ok_hsv360);
ok_hsv48 ok_hsv48_from(ok_hsv32);

#undef CHAIN_FROM
