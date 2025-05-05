// Internal helpers for ok_color_*.h color representations

#pragma once

#include <cstdint>

// Range conversion helper
struct ok_ratio { const int num, den; }
int operator*(ok_ratio r, int x) { return (x * r.num + r.den / 2) / r.den; }
int operator/(ok_ratio r, int x) { return (x * r.den + r.num / 2) / r.num; }

// Define bidirectional conversions based on an intermediate type
#define OK_CONV_CHAIN(A, B, C) \
  inline A A##_from(C x) { return A##_from(B##_from(x)); } \
  inline C C##_from(A x) { return C##_from(B##_from(x)); } \

// Declare bidirectional externally defined conversions
#define OK_CONV_EXTERN(A, B) A A##_from(B x); B B##_from(A x);

// Simple ratio RGB conversions (G ratio specified separately to allow 5:6:5)
#define OK_CONV_RB_G(A, B, rat, g_rat) \
  inline A A##_from(B x) { return { x.r * rat, x.g * g_rat, x.b * rat }; } \
  inline B B##_from(A x) { return { x.r / rat, x.g / g_rat, x.b / rat }; }
