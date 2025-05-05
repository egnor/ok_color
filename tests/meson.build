project(
  'ok_color_tests', ['cpp'],
  default_options: {
    'buildtype': 'debug',
    'cpp_std': 'c++11',
    'stdsplit': false,
    'warning_level': '3',
    'werror': true,
  },
)

ok_color_lib = library(
  'ok_color_lib', [
    '../src/ok_color_hsv.cpp',
    '../src/ok_color_lrgb.cpp',
  ],
  include_directories: '../src',
)

doctest_dep = dependency('doctest')

foreach test_name : ['helpers_test']
  test(
    test_name, executable(
      test_name, [test_name + '.cpp'],
      link_with: ok_color_lib,
      dependencies: doctest_dep,
    )
  )
endforeach
