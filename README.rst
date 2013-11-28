README for SFMT-installer
================================================================================

This is an unofficial installer of SIMD-oriented Fast Mersenne Twister
for C/C++: SFMT and dSFMT.

http://www.math.sci.hiroshima-u.ac.jp/~%20m-mat/MT/SFMT/index.html


Installation
--------------------------------------------------------------------------------

First, download the source files::

   ./get_source.sh

Then, build and install::

   ./configure
   make
   sudo make install


Usage
--------------------------------------------------------------------------------

.. literalinclude:: example.cpp

build and run::

   % clang++ -lsfmt main.cpp
   % ./a.out
   0.454631
   3501832039   

