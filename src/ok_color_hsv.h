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

//
// Conversions: <type>_from(<other>), eg. ok_hsv_977_from(ok_srgb_888 value)
//

// ok_hsv_{888,977,H88,HHH} <-> each other
// (using angle conversions for hue values)
OK_CONV_H_SV(ok_hsv_888, ok_hsv_H88, ok_8_16_a, ok_16_8_a, ok_8_8, ok_8_8);
OK_CONV_H_SV(ok_hsv_888, ok_hsv_HHH, ok_8_16_a, ok_16_8_a, ok_8_16, ok_16_8);
OK_CONV_H_SV(ok_hsv_977, ok_hsv_888, ok_deg_8, ok_8_deg, ok_pc_8, ok_8_pc);
OK_CONV_H_SV(ok_hsv_977, ok_hsv_H88, ok_deg_16, ok_16_deg, ok_pc_8, ok_8_pc);
OK_CONV_H_SV(ok_hsv_977, ok_hsv_HHH, ok_deg_16, ok_16_deg, ok_pc_16, ok_16_pc);
OK_CONV_H_SV(ok_hsv_H88, ok_hsv_HHH, ok_16_16, ok_16_16, ok_8_16, ok_16_8);

// ok_hsv_{888,977,H88,HHH} <-> ok_srgb_{888,HHH}
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

// ok_hsv_{888,977,H88,HHH} <-> ok_lrgb_{888,HHH}
OK_CONV_CHAIN(ok_lrgb_888, ok_srgb_888, ok_hsv_888);
OK_CONV_CHAIN(ok_lrgb_888, ok_srgb_888, ok_hsv_977);
OK_CONV_CHAIN(ok_lrgb_888, ok_srgb_HHH, ok_hsv_H88);
OK_CONV_CHAIN(ok_lrgb_888, ok_srgb_HHH, ok_hsv_HHH);
OK_CONV_CHAIN(ok_lrgb_HHH, ok_srgb_888, ok_hsv_888);
OK_CONV_CHAIN(ok_lrgb_HHH, ok_srgb_888, ok_hsv_977);
OK_CONV_CHAIN(ok_lrgb_HHH, ok_srgb_HHH, ok_hsv_H88);
OK_CONV_CHAIN(ok_lrgb_HHH, ok_srgb_HHH, ok_hsv_HHH);
