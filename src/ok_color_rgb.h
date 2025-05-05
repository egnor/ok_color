// Embedded-friendly representation of useful RGB-based color spaces.

#pragma once

#include <cstdint>

#include "ok_color_helpers.h"

// 24-bit sRGB color as used in PC graphics, #xxxxxx codes, image files, etc.
// https://en.wikipedia.org/wiki/SRGB
//
// sRGB component values have a nonlinear "gamma", eg. r/g/b = 127 (50%)
// repreesnts only ~21% the optical intensity of r/g/b = 255 (100%).
// This is partly historical and partly to match human perception.
struct ok_srgb_888 { uint8_t r, g, b; };

// 16-bit sRGB with 5 bit red (0-31), 6 bit green (0-63), and 5 bit blue (0-31).
struct ok_srgb_565 { uint16_t r: 5, g: 6, b: 5; };

// 48-bit sRGB (0-65535 instead of 0-255).
struct ok_srgb_HHH { uint16_t r, g, b; };

// Linear 8-bit RGB as used for LED output, raw camera data, color mixing, etc.
// Uses the same primaries as sRGB but without the transfer function.
struct ok_lrgb_888 { uint8_t r, g, b; }

// Linear 48-bit RGB (0-65535 instead of 0-255).
struct ok_lrgb_HHH { uint16_t r, g, b; };

//
// RGB conversions: [ok_type]_from([ok_other_type] value)
// 

OK_CONV_RB_G(ok_srgb_565, ok_srgb_888, ok_ratio{31, 255}, ok_ratio{31, 255});
OK_CONV_RB_G(ok_srgb_565, ok_srgb_HHH, ok_ratio{31, 65535}, ok_ratio{63, 65535});
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_lrgb_888);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_lrgb_HHH);

OK_CONV_RB_G(ok_srgb_888, ok_srgb_HHH, ok_ratio{1, 257}, ok_ratio{1, 257});
OK_CONV_CHAIN(ok_srgb_888, ok_srgb_HHH, ok_lrgb_888);
OK_CONV_CHAIN(ok_srgb_888, ok_srgb_HHH, ok_lrgb_HHH);

OK_CONV_CHAIN(ok_srgb_HHH, ok_lrgb_HHH, ok_lrgb_888);
OK_CONV_EXTERN(ok_srgb_HHH, ok_lrgb_HHH);

OK_CONV_RB_G(ok_lrgb_888, ok_lrgb_HHH, ok_ratio{1, 257}, ok_ratio{1, 257});
