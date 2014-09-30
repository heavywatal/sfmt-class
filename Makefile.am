MEXP = 19937
AM_CPPFLAGS = -Wall -Wextra -fno-strict-aliasing -DNDEBUG -DHAVE_SSE2 -DSFMT_MEXP=$(MEXP) -DDSFMT_MEXP=$(MEXP)
AM_CFLAGS = -O3 -msse2
export MEXP AM_CPPFLAGS AM_CFLAGS
export CFLAGS
SUBDIRS = SFMT-src-1.4.1 dSFMT-src-2.2.3
lib_LIBRARIES = libsfmt.a
libsfmt_a_SOURCES =
libsfmt_a_LIBADD = SFMT-src-1.4.1/SFMT.o dSFMT-src-2.2.3/dSFMT.o
EXTRA_DIST = README.rst
