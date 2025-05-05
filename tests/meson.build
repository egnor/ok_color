project('ok_color_test', 'cpp')

ok_color_lib = library(
  'ok_color_lib', [
    '../src/ok_color_hsv.cpp',
    '../src/ok_color_lrgb.cpp',
  ],
  include_directories: '../src',
)

foreach test_name : ['helpers_test']
  test(
    test_name, executable(
      test_name, [test_name + '.cpp'],
      link_with: [ok_color_lib],
      dependencies: [dependency('doctest')],
    )
  )
endforeach
