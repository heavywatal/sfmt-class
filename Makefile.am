MEXP = 19937
AM_CPPFLAGS = -Wall -Wextra -fno-strict-aliasing -DNDEBUG -DHAVE_SSE2 -DSFMT_MEXP=$(MEXP) -DDSFMT_MEXP=$(MEXP)
AM_CFLAGS = -O3 -msse2
AM_LDFLAGS = -avoid-version
ACLOCAL_AMFLAGS = -I m4
export MEXP AM_CPPFLAGS AM_CFLAGS
export CFLAGS
lib_LIBRARIES = libsfmt.a
lib_LTLIBRARIES = libsfmt.la
libsfmt_a_SOURCES = SFMT/SFMT.c dSFMT/dSFMT.c
libsfmt_la_SOURCES = SFMT/SFMT.c dSFMT/dSFMT.c
libsfmt_la_CFLAGS = $(AM_CFLAGS) -fPIC
nobase_include_HEADERS = SFMT/SFMT.h SFMT/SFMT-params.h SFMT/SFMT-params$(MEXP).h dSFMT/dSFMT.h sfmt.hpp
EXTRA_DIST = README.md example.cpp\
 SFMT/SFMT-common.h SFMT/SFMT-sse2.h\
 SFMT/CHANGE-LOG.txt SFMT/FILES.txt SFMT/LICENSE.txt SFMT/README.txt\
 dSFMT/dSFMT-common.h dSFMT/dSFMT-params.h dSFMT/dSFMT-params19937.h\
 dSFMT/CHANGE-LOG.txt dSFMT/FILES.txt dSFMT/LICENSE.txt dSFMT/README.txt

example: a.out
	./$<

a.out: example.cpp
	$(CXX) -O3 -std=c++14 -Wall -I$(includedir) $< -L$(libdir) -lsfmt -o $@
