MEXP = 19937
AM_CPPFLAGS = -Wall -Wextra -fno-strict-aliasing -DNDEBUG -DHAVE_SSE2 -DSFMT_MEXP=$(MEXP) -DDSFMT_MEXP=$(MEXP)
AM_CFLAGS = -O3 -msse2
AM_LDFLAGS = -avoid-version
ACLOCAL_AMFLAGS = -I m4
export MEXP AM_CPPFLAGS AM_CFLAGS
export CFLAGS
SUBDIRS = SFMT-src-1.4.1 dSFMT-src-2.2.3
lib_LIBRARIES = libsfmt.a
lib_LTLIBRARIES = libsfmt.la
libsfmt_a_SOURCES = SFMT-src-1.4.1/SFMT.c dSFMT-src-2.2.3/dSFMT.c
libsfmt_la_SOURCES = SFMT-src-1.4.1/SFMT.c dSFMT-src-2.2.3/dSFMT.c
libsfmt_la_CFLAGS = $(AM_CFLAGS) -fPIC
EXTRA_DIST = README.md
