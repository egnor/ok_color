#include <algorithm>

#include "ok_color_hsv.h"

template <typename RgbT, uint max_rgb, typename HsvT, uint h_wrap, uint max_sv>
static RgbT rgb_from_hsv(HsvT hsv) {
  decltype(HsvT::v) const hsv_chr = hsv.s * hsv.v / max_sv;
  decltype(RgbT::g) const rgb_range = (hsv_chr * max_rgb + max_sv / 2) / max_sv;
  decltype(RgbT::g) const rgb_top = (hsv.v * max_rgb + max_sv / 2) / max_sv;
  decltype(RgbT::g) const rgb_bot = rgb_top - rgb_range;
  decltype(RgbT::g) const rgb_delta = (hsv.h * 6 % h_wrap) * rgb_range / h_wrap;
  decltype(RgbT::g) const rgb_in = rgb_bot + rgb_delta;
  decltype(RgbT::g) const rgb_out = rgb_top - rgb_delta;
  switch (hsv.h * 6 / h_wrap) {
    case 0: return { rgb_top, rgb_in, rgb_bot };
    case 1: return { rgb_out, rgb_top, rgb_bot };
    case 2: return { rgb_bot, rgb_top, rgb_in };
    case 3: return { rgb_bot, rgb_out, rgb_top };
    case 4: return { rgb_in, rgb_bot, rgb_top };
    case 5: return { rgb_top, rgb_bot, rgb_out };
    default: return { 0, 0, 0 };  // should be unreachable
  }
}

template <typename HsvT, uint h_wrap, uint max_sv, typename RgbT, uint max_rgb>
static HsvT hsv_from_rgb(RgbT rgb) {
  decltype(RgbT::g) const rgb_top = std::max({ rgb.r, rgb.g, rgb.b });
  decltype(RgbT::g) const rgb_bot = std::min({ rgb.r, rgb.g, rgb.b });
  decltype(RgbT::g) const rgb_range = rgb_top - rgb_bot;
  decltype(HsvT::v) const val = (rgb_top * max_sv + max_rgb / 2) / max_rgb;
  if (rgb_range == 0) return { 0, 0, val };

  decltype(HsvT::h) hue;
  if (rgb_top == rgb.r && rgb_bot == rgb.b) {
    hue = (rgb.g - rgb_bot) * h_wrap / (rgb_range * 6);
  } else if (rgb_top == rgb.g && rgb_bot == rgb.b) {
    hue = (rgb_top - rgb.r + rgb_range) * h_wrap / (rgb_range * 6);
  } else if (rgb_top == rgb.g && rgb_bot == rgb.r) {
    hue = (rgb.b - rgb_bot + rgb_range * 2) * h_wrap / (rgb_range * 6);
  } else if (rgb_top == rgb.b && rgb_bot == rgb.r) {
    hue = (rgb_top - rgb.g + rgb_range * 3) * h_wrap / (rgb_range * 6);
  } else if (rgb_top == rgb.b && rgb_bot == rgb.g) {
    hue = (rgb.r - rgb_bot + rgb_range * 4) * h_wrap / (rgb_range * 6);
  } else {
    hue = (rgb_top - rgb.b + rgb_range * 5) * h_wrap / (rgb_range * 6);
  }

  decltype(HsvT::s) const sat = (rgb_range * max_sv + rgb_top / 2) / rgb_top;
  return { hue, sat, val };
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
