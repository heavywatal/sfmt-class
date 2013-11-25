#!/bin/sh
base_url=http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/
d_version=2.2.2
if [ ! -e dSFMT-src-${d_version} ]; then
    curl -o - ${base_url}dSFMT-src-${d_version}.tar.gz | tar xz
fi
cp -u dSFMT-Makefile.am dSFMT-src-${d_version}/Makefile.am

i_version=1.4
if [ ! -e SFMT-src-${i_version} ]; then
    curl -o - ${base_url}SFMT-src-${i_version}.tar.gz | tar xz
fi
cp -u SFMT-Makefile.am SFMT-src-${i_version}/Makefile.am
