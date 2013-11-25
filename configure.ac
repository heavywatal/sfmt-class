#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(SFMT-installer, 0.1, heavywatal@bitbucket)
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

CFLAGS=''

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET
AM_PROG_AR
AC_PROG_RANLIB

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
                 SFMT-src-1.4/Makefile
                 dSFMT-src-2.2.2/Makefile])
AC_OUTPUT
