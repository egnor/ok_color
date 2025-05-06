// Conversion functions between sRGB and linear RGB
// https://en.wikipedia.org/wiki/SRGB
//
// References:
// https://blog.pkh.me/p/38-porting-oklab-colorspace-to-integer-arithmetic.html
// https://chilliant.blogspot.com/2012/08/srgb-approximations-for-hlsl.html
// https://chilliant.blogspot.com/2015/11/srgb-integer-conversions.html
// https://github.com/BSVino/sRGB-Int
// https://github.com/ncruces/go-image/blob/master/imageutil/srgb.go

#include "ok_color_srgb.h"

ok_srgb_HHH ok_srgb_HHH_from(ok_lrgb_HHH lin) {
  (void) lin;
  return {};
}

ok_srgb_888 ok_srgb_888_from(ok_lrgb_HHH lin) {
  (void) lin;
  return {};
}

ok_lrgb_HHH ok_lrgb_HHH_from(ok_srgb_HHH std) {
  (void) std;
  return {};
}

ok_lrgb_HHH ok_lrgb_HHH_from(ok_srgb_888 std) {
  (void) std;
  return {};
}
