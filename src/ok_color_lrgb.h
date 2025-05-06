// Embedded-friendly representation of linear RGB-based color space.
// Uses the same primaries as sRGB but without the "gamma" transfer function.

#pragma once

#include <cstdint>

#include "ok_color_helpers.h"

// 24-bit/pixel (8-bit/component) linear RGB as used in LED/DMX output, etc.
//
// Warning, 8-bit linear RGB values are low precision, avoid in intermediates:
// https://blog.demofox.org/2018/03/10/dont-convert-srgb-u8-to-linear-u8/
struct ok_lrgb_888 { uint8_t r, g, b; };

// 48-bit/pixel linear RGB, suitable for mixing and other processing.
struct ok_lrgb_HHH { uint16_t r, g, b; };

//
// Conversions: <type>_from(<other>), eg. ok_lrgb_888_from(ok_srgb_565 value)
//

// ok_lrgb_888 <-> ok_lrgb_HHH
OK_CONV_RB_G(ok_lrgb_888, ok_lrgb_HHH, ok_8_16, ok_16_8, ok_8_16, ok_16_8);
