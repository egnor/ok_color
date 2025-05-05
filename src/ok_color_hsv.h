// Embedded-friendly representation of RGB<>HSV conversions.

#pragma once

#include <cstdint>

#include "ok_color_helpers.h"
#include "ok_color_lrgb.h"
#include "ok_color_srgb.h"

// 24-bit HSV (Hue, Saturation, Value) based on sRGB (including gamma).
// All components range 0-255; hue 0=red, 85=green, 170=blue.
struct ok_hsv_888 { uint8_t h, s, v; };

// 360-degree "decimal" HSV. Hue ranges 0-359, saturation and value range 0-100.
struct ok_hsv_977 { uint32_t h: 9, s: 7, v: 7; };

// 32-bit HSV. Hue ranges 0-65535, saturation and value range 0-255.
struct ok_hsv_H88 { uint16_t h; uint8_t s, v; };

// 48-bit HSV. All components range 0-65535; hue 0=red, 21845=green, 43690=blue.
struct ok_hsv_HHH { uint16_t h, s, v; };

// Conversions: [ok_type]_from([ok_other_type] value)

OK_CONV_H_SV(ok_hsv_888, ok_hsv_H88, ok_conv_8_16, ok_conv_8_8);
OK_CONV_H_SV(ok_hsv_888, ok_hsv_HHH, ok_conv_8_16, ok_conv_8_16);
OK_CONV_H_SV(ok_hsv_977, ok_hsv_888, ok_conv_360_8, ok_conv_100_8);
OK_CONV_H_SV(ok_hsv_977, ok_hsv_H88, ok_conv_360_16, ok_conv_100_8);
OK_CONV_H_SV(ok_hsv_977, ok_hsv_HHH, ok_conv_360_16, ok_conv_100_16);
OK_CONV_H_SV(ok_hsv_H88, ok_hsv_HHH, ok_conv_16_16, ok_conv_8_16);

OK_CONV_EXTERN(ok_srgb_888, ok_hsv_977);
OK_CONV_EXTERN(ok_srgb_888, ok_hsv_H88);
OK_CONV_EXTERN(ok_srgb_HHH, ok_hsv_HHH);

OK_CONV_CHAIN(ok_srgb_888, ok_hsv_H88, ok_hsv_888);
OK_CONV_CHAIN(ok_srgb_888, ok_hsv_H88, ok_hsv_HHH);
OK_CONV_CHAIN(ok_srgb_HHH, ok_hsv_HHH, ok_hsv_H88);
OK_CONV_CHAIN(ok_srgb_HHH, ok_srgb_888, ok_hsv_888);
OK_CONV_CHAIN(ok_srgb_HHH, ok_srgb_888, ok_hsv_977);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_hsv_888);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_hsv_977);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_HHH, ok_hsv_H88);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_HHH, ok_hsv_HHH);

OK_CONV_CHAIN(ok_lrgb_888, ok_srgb_888, ok_hsv_888);
OK_CONV_CHAIN(ok_lrgb_888, ok_srgb_888, ok_hsv_977);
OK_CONV_CHAIN(ok_lrgb_888, ok_srgb_HHH, ok_hsv_H88);
OK_CONV_CHAIN(ok_lrgb_888, ok_srgb_HHH, ok_hsv_HHH);
OK_CONV_CHAIN(ok_lrgb_HHH, ok_srgb_888, ok_hsv_888);
OK_CONV_CHAIN(ok_lrgb_HHH, ok_srgb_888, ok_hsv_977);
OK_CONV_CHAIN(ok_lrgb_HHH, ok_srgb_HHH, ok_hsv_H88);
OK_CONV_CHAIN(ok_lrgb_HHH, ok_srgb_HHH, ok_hsv_HHH);
