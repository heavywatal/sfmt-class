.. -*- restructuredtext -*-

SFMT-installer
================================================================================

This is an unofficial installer of SFMT and dSFMT for C/C++.
SFMT is a new variant of Mersenne Twister (MT) introduced by Mutsuo Saito and Makoto Matsumoto.

http://www.math.sci.hiroshima-u.ac.jp/~%20m-mat/MT/SFMT/index.html


Installation
--------------------------------------------------------------------------------

Download and extract `released archive`__::

   % ./configure
   % make
   % sudo make install

.. __: https://github.com/heavywatal/sfmt-installer/releases

If you are building the latest development version from github,
you need to run ``get_source.sh`` and **autotools**
to get the SFMT source files and ``configure`` script::

   % ./get_source.sh
   % autoreconf -i


Usage
--------------------------------------------------------------------------------

See ``example.cpp``::

   % clang++ -lsfmt example.cpp
   % ./a.out
   0.454631
   3501832039
