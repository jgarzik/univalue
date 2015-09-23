
include_HEADERS = univalue.h univalue_escapes.h

lib_LTLIBRARIES = libunivalue.la

libunivalue_la_SOURCES = \
	univalue.cpp \
	univalue_read.cpp \
	univalue_write.cpp

libunivalue_la_LDFLAGS = \
	-version-info $(LIBUNIVALUE_CURRENT):$(LIBUNIVALUE_REVISION):$(LIBUNIVALUE_AGE) \
	-no-undefined

noinst_PROGRAMS = gen

gen_SOURCES = gen.cpp

