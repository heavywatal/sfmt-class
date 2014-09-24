.. -*- restructuredtext -*-

README for SFMT-installer
================================================================================

This is an unofficial installer of SIMD-oriented Fast Mersenne Twister
for C/C++: SFMT and dSFMT.

http://www.math.sci.hiroshima-u.ac.jp/~%20m-mat/MT/SFMT/index.html


Installation
--------------------------------------------------------------------------------

If you are building from the latest development version from github,
you need to run ``get_source.sh`` and **autotools**
to get the SFMT source files and ``configure`` script::

   ./get_source.sh
   autoreconf -i

Then, build and install::

   ./configure
   make
   sudo make install


Usage
--------------------------------------------------------------------------------

See ``example.cpp``::

   % clang++ -lsfmt example.cpp
   % ./a.out
   0.454631
   3501832039   

