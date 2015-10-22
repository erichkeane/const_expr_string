# const_expr_string
An entirely const_expr string class in C++.  Similar to string_view, most useful for compile-time constants

This header-only class is meant to be an entirely compile-time string wrapper, specifically as a replacement
for static-const char and #define X string constants.

It emulates string_view as close as possible.

Compatible with C++14 AND C++11 (though separate implementations for each for a few functions).  Tested on G++4.9 and 5.2, and clang++ 3.5 and 3.6.1.

To compile the main test, just do one of the following:

```shell
g++ -std=c++14 -O3 -Wextra -Wall -Werror main.cpp
```
```shell
g++ -std=c++11 -O3 -Wextra -Wall -Werror main.cpp
```
```shell
clang++ -std=c++14 -O3 -Wextra -Wall -Werror main.cpp
```
```shell
clang++ -std=c++11 -O3 -Wextra -Wall -Werror main.cpp
```
