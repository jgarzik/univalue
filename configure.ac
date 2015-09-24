m4_define([libunivalue_major_version], [1])
m4_define([libunivalue_minor_version], [1])
m4_define([libunivalue_micro_version], [1])
m4_define([libunivalue_interface_age], [1])
# If you need a modifier for the version number. 
# Normally empty, but can be used to make "fixup" releases.
m4_define([libunivalue_extraversion], [])

dnl libtool versioning from libunivalue
m4_define([libunivalue_current], [m4_eval(100 * libunivalue_minor_version + libunivalue_micro_version - libunivalue_interface_age)])
m4_define([libunivalue_binary_age], [m4_eval(100 * libunivalue_minor_version + libunivalue_micro_version)])
m4_define([libunivalue_revision], [libunivalue_interface_age])
m4_define([libunivalue_age], [m4_eval(libunivalue_binary_age - libunivalue_interface_age)])
m4_define([libunivalue_version], [libunivalue_major_version().libunivalue_minor_version().libunivalue_micro_version()libunivalue_extraversion()])


AC_INIT([univalue], [1.0.0],
        [http://github.com/jgarzik/univalue/])

AC_PREREQ(2.60)
AC_CONFIG_SRCDIR([lib/univalue.cpp])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])
AC_CONFIG_HEADERS([univalue-config.h])
AM_INIT_AUTOMAKE([gnu])

LIBUNIVALUE_MAJOR_VERSION=libunivalue_major_version
LIBUNIVALUE_MINOR_VERSION=libunivalue_minor_version
LIBUNIVALUE_MICRO_VERSION=libunivalue_micro_version
LIBUNIVALUE_INTERFACE_AGE=libunivalue_interface_age

# ABI version
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
LIBUNIVALUE_CURRENT=libunivalue_current
LIBUNIVALUE_REVISION=libunivalue_revision
LIBUNIVALUE_AGE=libunivalue_age

AC_SUBST(LIBUNIVALUE_CURRENT)
AC_SUBST(LIBUNIVALUE_REVISION)
AC_SUBST(LIBUNIVALUE_AGE)

LT_INIT

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

AC_LANG_PUSH([C++])

AC_CONFIG_FILES([
    lib/Makefile
    test/Makefile
    Makefile
    lib/libunivalue.pc
    lib/libunivalue-uninstalled.pc])
AC_OUTPUT

