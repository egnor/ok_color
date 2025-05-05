// Embedded-friendly representation of RGB<>HSV conversions.

#pragma once

#include <cstdint>

#include "ok_color_helpers.h"
#include "ok_color_rgb.h"

// 24-bit HSV (Hue, Saturation, Value) based on sRGB (including gamma).
// All components range 0-255; hue 0=red, 85=green, 170=blue.
struct ok_hsv_888 { uint8_t h, s, v; };

// 360-degree "decimal" HSV. Hue ranges 0-359, saturation and value range 0-100.
struct ok_hsv_977 { uint32_t h: 9, s: 7, v: 7; };

// 32-bit HSV. Hue ranges 0-65535, saturation and value range 0-255.
struct ok_hsv_H88 { uint16_t h; uint8_t s, v; };

// 48-bit HSV. All components range 0-65535; hue 0=red, 21845=green, 43690=blue.
struct ok_hsv_HHH { uint16_t h, s, v; };

//
// HSV conversions: [ok_type]_from([ok_other_type] value)
//

// Simple ratio HSV conversions (H ratio specified separately)
#define OK_CONV_H_SV(A, B, h_rat, rat) \
  inline A A##_from(B x) { return { x.h * h_rat, x.s * rat, x.v * rat }; } \
  inline B B##_from(A x) { return { x.h / h_rat, x.s / rat, x.v / rat }; }

OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_hsv_888);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_hsv_977);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_HHH, ok_hsv_H88);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_HHH, ok_hsv_HHH);

OK_CONV_CHAIN(ok_srgb_888, ok_hsv_H88, ok_hsv_888);
OK_CONV_EXTERN(ok_srgb_888, ok_hsv_977);
OK_CONV_EXTERN(ok_srgb_888, ok_hsv_H88);
OK_CONV_CHAIN(ok_srgb_888, ok_hsv_H88, ok_hsv_HHH);

OK_CONV_CHAIN(ok_srgb_HHH, ok_srgb_888, ok_hsv_888);
OK_CONV_CHAIN(ok_srgb_HHH, ok_srgb_888, ok_hsv_977);
OK_CONV_CHAIN(ok_srgb_HHH, ok_hsv_HHH, ok_hsv_H88);
OK_CONV_EXTERN(ok_srgb_HHH, ok_hsv_HHH);

CHAIN_CONV(ok_lrgb_888, ok_srgb_888, ok_hsv_888);
CHAIN_CONV(ok_lrgb_888, ok_srgb_888, ok_hsv_977);
CHAIN_CONV(ok_lrgb_888, ok_srgb_HHH, ok_hsv_H88);
CHAIN_CONV(ok_lrgb_888, ok_srgb_HHH, ok_hsv_HHH);
CHAIN_CONV(ok_lrgb_HHH, ok_srgb_888, ok_hsv_888);
CHAIN_CONV(ok_lrgb_HHH, ok_srgb_888, ok_hsv_977);
CHAIN_CONV(ok_lrgb_HHH, ok_srgb_HHH, ok_hsv_H88);
CHAIN_CONV(ok_lrgb_HHH, ok_srgb_HHH, ok_hsv_HHH);

OK_CONV_H_SV(ok_hsv_888, ok_hsv_977, ok_ratio{255, 360}, ok_ratio{255, 100});
OK_CONV_H_SV(ok_hsv_888, ok_hsv_H88, ok_ratio{1, 257}, ok_ratio{1, 1});
OK_CONV_H_SV(ok_hsv_888, ok_hsv_HHH, ok_ratio{1, 257}, ok_ratio{1, 257});
OK_CONV_H_SV(ok_hsv_977, ok_hsv_H88, ok_ratio{360, 65535}, ok_ratio{100, 255});
OK_CONV_H_SV(ok_hsv_977, ok_hsv_HHH, ok_ratio{360, 65535}, ok_ratio{100, 65535});
OK_CONV_H_SV(ok_hsv_H88, ok_hsv_HHH, ok_ratio{1, 1}, ok_ratio{1, 257});
