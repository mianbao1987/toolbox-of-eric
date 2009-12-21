#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)

# automake
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_YACC
AC_PROG_CC
AC_PROG_LEX

AC_ARG_WITH(liberty, [  --with-libiberty=PATH		specify prefix directory for installed libiberty package.
				Equivalent to --with-libiberty-include=PATH/include
				plus --with-mpfr-lib=PATH/lib])
AC_ARG_WITH(liberty_include, [  --with-libiberty-include=PATH	specify directory for installed libiberty include files])
AC_ARG_WITH(liberty_lib, [  --with-libiberty-lib=PATH	specify directory for installed libiberty library])

if test "x$with_libiberty" != x; then
  liberty_inc="-I$with_libiberty/include"
  liberty_lib="-L$with_libiberty/lib"
fi

if test "x$with_libiberty_include" != x; then
  liberty_inc="-I$with_libiberty/include"
fi

if test "x$with_libiberty_lib" != x; then
  liberty_lib="-L$with_libiberty/lib"
fi

AC_SUBST(liberty_inc)
AC_SUBST(liberty_lib)

# Checks for libraries.
# FIXME: Replace `main' with a function in `-liberty':
AC_CHECK_LIB([iberty], [xstrdup], , [echo "Error! libiberty library is required." && exit -1])

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
