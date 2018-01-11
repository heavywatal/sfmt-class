## SFMT-class

[![Build Status](https://travis-ci.org/heavywatal/sfmt-class.svg?branch=master)](https://travis-ci.org/heavywatal/sfmt-class)

This is an unofficial wrapper of SFMT for C++.
It can also be used as just a simple installer of SFMT for C/C++.
SFMT is a new variant of Mersenne Twister (MT) introduced by Mutsuo Saito and Makoto Matsumoto.

http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/

### Installation

The easiest way is to use [Homebrew](https://brew.sh/)/[Linuxbrew](http://linuxbrew.sh/):
```sh
% brew install --HEAD heavywatal/tap/sfmt-class
```

Alternatively, you can get the source code from GitHub manually:
```sh
% git clone https://github.com/heavywatal/sfmt-class.git
% cd sfmt-class/
% git submodule update --init
% mkdir build
% cd build/
% cmake -DCMAKE_INSTALL_PREFIX=${HOME}/local ..
% make
% make install
```

### Usage in C++

C++ header `sfmt.hpp` is installed in addition to the original C headers.
A wrapper class `wtl::sfmt19937` is compatible with `std::mt19937` and can be used in combination with `std::*_distribution` in `<random>`.
For convenience, a static object is initialized with `std::random_device`, and its reference is provided through an inline function `sfmt()`.
See ``example.cpp`` and try `make example`.
