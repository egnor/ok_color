// Embedded-friendly representation of standard RGB color space

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

// Conversions: [ok_type]_from([ok_other_type] value)
OK_CONV_RB_G(ok_srgb_565, ok_srgb_888, ok_conv_5_8, ok_conv_6_8);
OK_CONV_RB_G(ok_srgb_565, ok_srgb_HHH, ok_conv_5_16, ok_conv_6_16);
OK_CONV_RB_G(ok_srgb_888, ok_srgb_HHH, ok_conv_8_16, ok_conv_8_16);
