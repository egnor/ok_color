// Embedded-friendly representation of linear RGB-based color space.

#pragma once

#include <cstdint>

#include "ok_color_helpers.h"
#include "ok_color_srgb.h"

// Linear 8-bit RGB as used for LED output, raw camera data, color mixing, etc.
// Uses the same primaries as sRGB but without the transfer function.
struct ok_lrgb_888 { uint8_t r, g, b; };

// Linear 48-bit RGB (0-65535 instead of 0-255).
struct ok_lrgb_HHH { uint16_t r, g, b; };

//
// Conversions: <type>_from(<other>), eg. ok_lrgb_888_from(ok_srgb_565 value)
//

// ok_lrgb_HHH <-> ok_srgb_HHH
OK_CONV_EXTERN(ok_srgb_HHH, ok_lrgb_HHH);

// ok_lrgb_888 <-> ok_lrgb_HHH
OK_CONV_RB_G(ok_lrgb_888, ok_lrgb_HHH, ok_8_16, ok_16_8, ok_8_16, ok_16_8);

// ok_srgb_{565,888,HHH} <-> ok_lrgb_{888,HHH}
OK_CONV_CHAIN(ok_srgb_HHH, ok_lrgb_HHH, ok_lrgb_888);
OK_CONV_CHAIN(ok_srgb_888, ok_srgb_HHH, ok_lrgb_HHH);
OK_CONV_CHAIN(ok_srgb_888, ok_srgb_HHH, ok_lrgb_888);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_lrgb_888);
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_lrgb_HHH);
