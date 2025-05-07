// Internal helpers for ok_color_*.h color representations

#pragma once

#include <cstdint>

// Declare externally defined bidirectional conversions
#define OK_CONV_EXTERN(A, B) A A##_from(B x); B B##_from(A x);

// Define bidirectional conversions based on an intermediate type
#define OK_CONV_CHAIN(A, B, C) \
  inline A A##_from(C x) { return A##_from(B##_from(x)); } \
  inline C C##_from(A x) { return C##_from(B##_from(x)); } \

// RGB range conversion with RB and G conversions optionally separate
// Expects range conversion helper functions for *{ab, ba} parameters
#define OK_CONV_RGB(A, B, ab, ba) OK_CONV_RB_G(A, B, ab, ba, ab, ba)
#define OK_CONV_RB_G(A, B, rb_ab, rb_ba, g_ab, g_ba) \
  inline A A##_from(B x) { return { rb_ba(x.r), g_ba(x.g), rb_ba(x.b) }; } \
  inline B B##_from(A x) { return { rb_ab(x.r), g_ab(x.g), rb_ab(x.b) }; }

// HSV range conversions with H and SV conversions specified separately
// Expects range conversion helper functions for *{ab, ba} parameters
#define OK_CONV_H_SV(A, B, h_ab, h_ba, sv_ab, sv_ba) \
  inline A A##_from(B x) { return { h_ba(x.h), sv_ba(x.s), sv_ba(x.v)}; } \
  inline B B##_from(A x) { return { h_ab(x.h), sv_ab(x.s), sv_ab(x.v)}; }

// Conversion helpers for scalar values: ok_[x]_[y] converts x-bit to y-bit
// (_pc and _deg are 7-bit percent and 9-bit degree, respectively)

// Range conversions: interpolate between 0=>0 and a_max=>b_max
inline uint8_t ok_5_8(uint8_t x) { return (x * 255 + 15) / 31; }
inline uint8_t ok_8_5(uint8_t x) { return (x * 31 + 127) / 255; }
inline uint16_t ok_5_16(uint8_t x) { return (x * 65535 + 15) / 31; }
inline uint8_t ok_16_5(uint16_t x) { return (x * 31 + 32767) / 65535; }

inline uint8_t ok_6_8(uint8_t x) { return (x * 255 + 31) / 63; }
inline uint8_t ok_8_6(uint8_t x) { return (x * 63 + 127) / 255; }
inline uint16_t ok_6_16(uint8_t x) { return (x * 65535 + 31) / 63; }
inline uint8_t ok_16_6(uint16_t x) { return (x * 63 + 32767) / 65535; }

inline uint8_t ok_8_8(uint8_t x) { return x; }
inline uint16_t ok_8_16(uint8_t x) { return x * 257; }
inline uint8_t ok_16_8(uint16_t x) { return (x + 128) / 257; }
inline uint16_t ok_16_16(uint16_t x) { return x; }

inline uint8_t ok_8_pc(uint8_t x) { return (x * 100 + 127) / 255; }
inline uint8_t ok_pc_8(uint8_t x) { return (x * 255 + 50) / 100; }
inline uint16_t ok_pc_16(uint8_t x) { return (x * 65535 + 50) / 100; }
inline uint8_t ok_16_pc(uint16_t x) { return (x * 100 + 32767) / 65535; }

// Angle conversions: interpolate between 0=>0 and (a_max+1)=>(a_max+1)
inline uint16_t ok_8_16_a(uint8_t x) { return x * 256; }
inline uint8_t ok_16_8_a(uint16_t x) { return x / 256; }
inline uint16_t ok_8_deg(uint8_t x) { return (x * 360 + 128) / 256; }
inline uint8_t ok_deg_8(uint16_t x) { return (x * 256 + 180) / 360; }
inline uint16_t ok_deg_16(uint16_t x) { return x * 65536 / 360; }
inline uint16_t ok_16_deg(uint16_t x) { return (x * 360 + 359) / 65536; }
