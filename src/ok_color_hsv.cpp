#include <algorithm>

#include "ok_color_hsv.h"

template <typename RgbT, int max_rgb, typename HsvT, int h_wrap, int max_sv>
static RgbT rgb_from_hsv(HsvT hsv) {
  auto const range = hsv.v * hsv.s / max_sv;
  auto const max = hsv.v, min = max - range;
  auto const partial = (hsv.h * 6 % h_wrap) * range / h_wrap;
  switch (hsv.h * 6 / h_wrap) {
    case 0: return { max, min + partial, min };
    case 1: return { max - partial, max, min };
    case 2: return { min, max, min + partial };
    case 3: return { min, max - partial, max };
    case 4: return { min + partial, min, max };
    case 5: return { max, min, max - partial };
    default: return { 0, 0, 0 };  // unreachable
  }
}

template <typename HsvT, int h_wrap, int max_sv, typename RgbT, int max_rgb>
static HsvT hsv_from_rgb(RgbT rgb) {
  auto const max = std::max({ rgb.r, rgb.g, rgb.b });
  auto const min = std::min({ rgb.r, rgb.g, rgb.b });
  auto const range = max - min;
  if (range == 0) return { 0, 0, max };

  auto const sat = range * max_sv / max;
  if (max == rgb.r && min == rgb.b) {
    return { (rgb.g - min) * h_wrap / (range * 6), sat, max };
  } else if (max == rgb.g && min == rgb.b) {
    return { (max - rgb.r + range) * h_wrap / (range * 6), sat, max };
  } else if (max == rgb.g && min == rgb.r) {
    return { (rgb.b - min + range * 2) * h_wrap / (range * 6), sat, max };
  } else if (max == rgb.b && min == rgb.r) {
    return { (max - rgb.g + range * 3) * h_wrap / (range * 6), sat, max };
  } else if (max == rgb.b && min == rgb.g) {
    return { (rgb.r - min + range * 4) * h_wrap / (range * 6), sat, max };
  } else {
    return { (max - rgb.b + range * 5) * h_wrap / (range * 6), sat, max };
  }
}

ok_srgb_888 ok_srgb_888_from(ok_hsv_H88 hsv) {
  return rgb_from_hsv<ok_srgb_888, 255, ok_hsv_H88, 65536, 255>(hsv);
}

ok_hsv_H88 ok_hsv_H88_from(ok_srgb_888 rgb) {
  return hsv_from_rgb<ok_hsv_H88, 65536, 255, ok_srgb_888, 255>(rgb);
}

ok_srgb_888 ok_srgb_888_from(ok_hsv_977 hsv) {
  return rgb_from_hsv<ok_srgb_888, 255, ok_hsv_977, 360, 100>(hsv);
}

ok_hsv_977 ok_hsv_977_from(ok_srgb_888 rgb) {
  return hsv_from_rgb<ok_hsv_977, 360, 100, ok_srgb_888, 255>(rgb);
}

ok_srgb_HHH ok_srgb_HHH_from(ok_hsv_HHH hsv) {
  return rgb_from_hsv<ok_srgb_HHH, 65535, ok_hsv_HHH, 65536, 65535>(hsv);
}

ok_hsv_HHH ok_hsv_HHH_from(ok_srgb_HHH rgb) {
  return hsv_from_rgb<ok_hsv_HHH, 65536, 65535, ok_srgb_HHH, 65535>(rgb);
}
