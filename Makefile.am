ACLOCAL_AMFLAGS = -I build-aux/m4

include_HEADERS = lib/univalue.h lib/univalue_escapes.h

lib_LTLIBRARIES = lib/libunivalue.la

lib_libunivalue_la_SOURCES = \
	lib/univalue.cpp \
	lib/univalue_read.cpp \
	lib/univalue_write.cpp

lib_libunivalue_la_LDFLAGS = \
	-version-info $(LIBUNIVALUE_CURRENT):$(LIBUNIVALUE_REVISION):$(LIBUNIVALUE_AGE) \
	-no-undefined

noinst_PROGRAMS = lib/gen

lib_gen_SOURCES = lib/gen.cpp

SUBDIRS = . test

