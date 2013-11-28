README for SFMT-installer
================================================================================

This is an unofficial installer of SIMD-oriented Fast Mersenne Twister
for C/C++: SFMT and dSFMT.

http://www.math.sci.hiroshima-u.ac.jp/~%20m-mat/MT/SFMT/index.html


Installation
--------------------------------------------------------------------------------

::

   ./configure
   make
   sudo make install


Usage
--------------------------------------------------------------------------------

::

   #define HAVE_SSE2
   #define SFMT_MEXP 19937
   #define DSFMT_MEXP 19937
   #define DSFMT_DO_NOT_USE_OLD_NAMES
   #include <dSFMT.h>
   //#include <SFMT.h>

   int main() {
       unsinged int seed = 42;
       dsfmt_t state;
       dsfmt_init_gen_rand(&state, seed);

       // real [0, 1)
       double x = dsfmt_genrand_close_open(&state);

       // integer [0, 2^32 - 1]
       unsigned int y = dsfmt_genrand_uint32(&state);

       return 0;
   }

