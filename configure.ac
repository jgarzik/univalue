AC_INIT([univalue], [0.0.1],
        [http://github.com/jgarzik/univalue/])

AC_PREREQ(2.52)
AC_CONFIG_SRCDIR([univalue.cpp])
AM_INIT_AUTOMAKE([gnu])
AC_CONFIG_HEADERS([univalue-config.h])


AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXXCPP
AC_PROG_INSTALL
AC_PROG_OBJC
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PROG_SED
AC_PATH_TOOL(AR, ar)
AC_PATH_TOOL(RANLIB, ranlib)
AC_PATH_TOOL(STRIP, strip)
PKG_PROG_PKG_CONFIG

# Enable wallet
AC_ARG_WITH([numfunc],
  [AS_HELP_STRING([--with-numfunc],
  [enable compiling of number parsing functions (default is yes)])],
  [use_numfunc=$withval],
  [use_numfunc=yes])
AM_CONDITIONAL([USE_NUMFUNC], [test x$use_numfunc = xyes])

AC_LANG_PUSH([C++])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

