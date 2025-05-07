// Embedded-friendly representation of standard RGB color space
// https://en.wikipedia.org/wiki/SRGB
//
// sRGB component values have a nonlinear "gamma", eg. r/g/b = 127 (50%)
// repreesnts only ~21% the optical intensity of r/g/b = 255 (100%).
// This is partly historical and partly to match human perception.

#pragma once

#include <cstdint>

#include "ok_color_helpers.h"
#include "ok_color_lrgb.h"

// 24-bit/pixel sRGB color as used in PC graphics, #xxxxxx codes, images, etc.
struct ok_srgb_888 { uint8_t r, g, b; };

// 16-bit sRGB with 5 bit red (0-31), 6 bit green (0-63), and 5 bit blue (0-31).
struct ok_srgb_565 { uint16_t r: 5, g: 6, b: 5; };

// 48-bit sRGB (0-65535 instead of 0-255).
struct ok_srgb_HHH { uint16_t r, g, b; };

//
// Conversions: <type>_from(<other>), eg. ok_srgb_888_from(ok_srgb_565 value)
//

// Component conversion helpers
extern uint8_t const ok_lin8_gamma8_table[256]; // 8-bit linear to sRGB channel
extern uint8_t const ok_gamma8_lin8_table[256]; // 8-bit sRGB channel to linear
extern uint16_t const ok_gamma8_lin16_table[256]; // 8-bit sRGB to 16-bit linear

inline uint8_t ok_lin8_gamma8(uint8_t v) { return ok_lin8_gamma8_table[v]; }
inline uint8_t ok_gamma8_lin8(uint8_t v) { return ok_gamma8_lin8_table[v]; }
inline uint16_t ok_gamma8_lin16(uint8_t v) { return ok_gamma8_lin16_table[v]; }

extern uint8_t ok_lin16_gamma8(uint16_t v); // 16-bit linear to 8-bit sRGB
extern uint16_t ok_lin16_gamma16(uint16_t v); // 16-bit linear to 16-bit sRGB
extern uint16_t ok_gamma16_lin16(uint16_t v); // 16-bit sRGB to 16-bit linear

// ok_srgb_{565,888,HHH} <-> each other
OK_CONV_RB_G(ok_srgb_565, ok_srgb_888, ok_5_8, ok_8_5, ok_6_8, ok_8_6);
OK_CONV_RB_G(ok_srgb_565, ok_srgb_HHH, ok_5_16, ok_16_5, ok_6_16, ok_16_6);
OK_CONV_RGB(ok_srgb_888, ok_srgb_HHH, ok_8_16, ok_16_8);

// ok_srgb_{565,888,HHH} <-> ok_lrgb_{888,HHH}
OK_CONV_RGB(ok_srgb_888, ok_lrgb_888, ok_gamma8_lin8, ok_lin8_gamma8);
OK_CONV_RGB(ok_srgb_888, ok_lrgb_HHH, ok_gamma8_lin16, ok_lin16_gamma8);
OK_CONV_RGB(ok_srgb_HHH, ok_lrgb_HHH, ok_gamma16_lin16, ok_lin16_gamma16);
OK_CONV_CHAIN(ok_srgb_HHH, ok_lrgb_HHH, ok_lrgb_888);                           
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_lrgb_888);                           
OK_CONV_CHAIN(ok_srgb_565, ok_srgb_888, ok_lrgb_HHH);
