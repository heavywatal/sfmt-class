#!/bin/sh
base_url=http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/
d_version=2.2.3
if [ ! -e dSFMT-src-${d_version}/dSFMT.h ]; then
    curl -o - ${base_url}dSFMT-src-${d_version}.tar.gz | tar xz
fi

i_version=1.4.1
if [ ! -e SFMT-src-${i_version}/SFMT.h ]; then
    curl -o - ${base_url}SFMT-src-${i_version}.tar.gz | tar xz
fi
