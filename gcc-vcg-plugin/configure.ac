#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(gcc-vcg-plugin, 0.1, joefoxreal@gmail.com)
AC_CONFIG_HEADERS(config.h)

# m4
AC_CONFIG_MACRO_DIR([m4])
#ACLOCAL_FLAGS="-I m4"

# automake
AM_INIT_AUTOMAKE

# add the m4 dir
# AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_YACC
AC_PROG_CC
AC_PROG_LEX

# libtool
LT_INIT
AC_PROG_LIBTOOL

AC_ARG_WITH(libiberty, [  --with-libiberty=PATH		specify prefix directory for installed libiberty package.
				Equivalent to --with-libiberty-include=PATH/include
				plus --with-mpfr-lib=PATH/lib])
AC_ARG_WITH(libiberty_include, [  --with-libiberty-include=PATH	specify directory for installed libiberty include files])
AC_ARG_WITH(libiberty_lib, [  --with-libiberty-lib=PATH	specify directory for installed libiberty library])

if test "x$with_libiberty" != x; then
  liberty_inc="-I$with_libiberty/include"
  liberty_lib="-L$with_libiberty/lib"
fi

if test "x$with_libiberty_include" != x; then
  liberty_inc="-I$with_libiberty_include"
fi

if test "x$with_libiberty_lib" != x; then
  liberty_lib="-L$with_libiberty_lib"
fi

AC_SUBST(liberty_inc)
AC_SUBST(liberty_lib)

# Checks for libraries.
#saved_LIBS="$LIBS"
LIBS="$LIBS $liberty_lib"
AC_CHECK_LIB([iberty], [xstrdup], , [echo "Error! libiberty library is required." && exit -1])
#LIBS="$saved_LIBS"

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_FUNC_OBSTACK

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
