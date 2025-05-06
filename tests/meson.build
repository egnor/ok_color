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

ok_color_inc = include_directories('../src')

ok_color_lib = library(
  'ok_color_lib', [
    '../src/ok_color_hsv.cpp',
    '../src/ok_color_srgb.cpp',
  ],
  include_directories: ok_color_inc,
)

doctest_dep = dependency('doctest')

foreach test_name : ['helpers_test']
  test(
    test_name, executable(
      test_name, [test_name + '.cpp'],
      dependencies: doctest_dep,
      include_directories: ok_color_inc,
      link_with: ok_color_lib,
    )
  )
endforeach
