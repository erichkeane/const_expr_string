# const_expr_string
An entirely const_expr string class in C++.  Similar to string_view, most useful for compile-time constants

This header-only class is meant to be an entirely compile-time string wrapper, specifically as a replacement 
for static-const char and #define X string constants.

It emulates string_view as close as possible.

Compatible with C++14 ONLY, and g++ versions pre-5.0 don't work (since they don't allow multi-line constexpr).

See main.cpp for examples/tests to validate that the functionality was done at compile-time!

To compile, do: clang++ -std=c++14 -O3 -I./include main.cpp
