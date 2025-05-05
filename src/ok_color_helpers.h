// Internal helpers for ok_color_*.h color representations

#pragma once

#include <cstdint>

// Declare externally defined bidirectional conversions
#define OK_CONV_EXTERN(A, B) A A##_from(B x); B B##_from(A x);

// Define bidirectional conversions based on an intermediate type
#define OK_CONV_CHAIN(A, B, C) \
  inline A A##_from(C x) { return A##_from(B##_from(x)); } \
  inline C C##_from(A x) { return C##_from(B##_from(x)); } \

// RGB range conversion (G conversion specified separately to allow 5:6:5)
// Expects a range conversion helper name for 'cv' and 'g_cv'
#define OK_CONV_RB_G(A, B, cv, g_cv) \
  inline A A##_from(B x) { return { cv(x.r), g_cv(x.g), cv(x.b) }; } \
  inline B B##_from(A x) { return { cv##_r(x.r), g_cv##_r(x.g), cv##_r(x.b) }; }

// HSV range conversions (H conversion specified separately)
// Expects a range conversion helper name for 'h_cv' and 'cv'
#define OK_CONV_H_SV(A, B, h_cv, cv) \
  inline A A##_from(B x) { return { h_cv(x.h), cv(x.s), cv(x.v)}; } \
  inline B B##_from(A x) { return { h_cv##_r(x.h), cv##_r(x.s), cv##_r(x.v)}; }

// Range conversion helpers. The odd naming scheme is helpful for macros:
//   smaller_val = ok_conv_[smaller_type]_[larger_type}(larger_val)
//   larger_val = ok_conv_[smaller_type]_[larger_type]_r(smaller_val)
inline uint8_t ok_conv_5_8(uint8_t x) { return (x * 31 + 127) / 255; }
inline uint8_t ok_conv_5_8_r(uint8_t x) { return (x * 255 + 15) / 31; }
inline uint8_t ok_conv_5_16(uint16_t x) { return (x * 31 + 32767) / 65535; }
inline uint16_t ok_conv_5_16_r(uint8_t x) { return (x * 65535 + 15) / 32767; }

inline uint8_t ok_conv_6_8(uint8_t x) { return (x * 63 + 127) / 255; }
inline uint8_t ok_conv_6_8_r(uint8_t x) { return (x * 255 + 31) / 63; }
inline uint8_t ok_conv_6_16(uint16_t x) { return (x * 63 + 32767) / 65535; }
inline uint16_t ok_conv_6_16_r(uint8_t x) { return (x * 65535 + 31) / 32767; }

inline uint8_t ok_conv_8_8(uint8_t x) { return x; }
inline uint8_t ok_conv_8_8_r(uint8_t x) { return x; }
inline uint8_t ok_conv_8_16(uint16_t x) { return (x + 128) / 257; }
inline uint16_t ok_conv_8_16_r(uint8_t x) { return x * 257; }

inline uint16_t ok_conv_16_16(uint16_t x) { return x; }
inline uint16_t ok_conv_16_16_r(uint16_t x) { return x; }

inline uint8_t ok_conv_100_8(uint8_t x) { return (x * 100 + 127) / 255; }
inline uint8_t ok_conv_100_8_r(uint8_t x) { return (x * 255 + 50) / 100; }
inline uint8_t ok_conv_100_16(uint16_t x) { return (x * 100 + 32767) / 65535; }
inline uint16_t ok_conv_100_16_r(uint8_t x) { return (x * 65535 + 50) / 100; }

inline uint16_t ok_conv_360_8(uint8_t x) { return x * 360 / 256; }
inline uint8_t ok_conv_360_8_r(uint16_t x) { return x * 256 / 360; }
inline uint16_t ok_conv_360_16(uint16_t x) { return x * 360 / 65536; }
inline uint16_t ok_conv_360_16_r(uint16_t x) { return x * 65536 / 360; }
