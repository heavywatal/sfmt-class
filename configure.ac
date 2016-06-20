#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([SFMT-installer], m4_esyscmd([git describe --tags | tr -d '\n']))
AC_PREREQ([2.68])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
CFLAGS_USER=${CFLAGS}
CFLAGS=''
AC_PROG_CC
CFLAGS=${CFLAGS_USER}
AC_PROG_MAKE_SET
AM_PROG_AR
LT_INIT

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h limits.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_CHECK_FUNCS([memset sqrt])

AC_CONFIG_FILES([Makefile
                 SFMT-src-1.4.1/Makefile
                 dSFMT-src-2.2.3/Makefile])
AC_OUTPUT
