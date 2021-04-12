## SFMT-class

[![Build status](https://github.com/heavywatal/sfmt-class/workflows/build/badge.svg)](https://github.com/heavywatal/sfmt-class/actions)

This is an unofficial wrapper of SFMT for C++.
It can also be used as just a simple installer of SFMT for C/C++.
SFMT is a new variant of Mersenne Twister (MT) introduced by Mutsuo Saito and Makoto Matsumoto.

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/

### Installation

The easiest way is to use [Homebrew](https://brew.sh/):
```sh
% brew install heavywatal/tap/sfmt-class
```

Alternatively, you can get the source code from GitHub manually:
```sh
% git clone https://github.com/heavywatal/sfmt-class.git
% cd sfmt-class/
% git submodule update --init
% cmake -S . -B build -DCMAKE_INSTALL_PREFIX=${HOME}/local
% cmake --build build --parallel 2
% cmake --install build
```

Header files are installed to `${CMAKE_INSTALL_PREFIX}/include/`.
This library can be imported from other CMake projects:
```cmake
find_package(sfmt)
target_link_libraries(${YOUR_TARGET} PRIVATE wtl::sfmt)
```

### Usage in C++

C++ header `sfmt.hpp` is installed in addition to the original C headers.
A wrapper class `wtl::sfmt19937` is compatible with `std::mt19937` and can be used in combination with `std::*_distribution` in `<random>`.
For convenience, a static object is initialized with `std::random_device`, and its reference is provided through an inline function `sfmt()`.
See ``test/example.cpp`` and try `ctest -V`.
The 64-bit version `wtl::sfmt19937_64` and `wtl::sfmt64()` are also available, and faster than 32-bit version in most cases.
