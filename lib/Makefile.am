
include_HEADERS = univalue.h univalue_escapes.h

lib_LIBRARIES = libunivalue.a

libunivalue_a_SOURCES = \
	univalue.cpp \
	univalue_read.cpp \
	univalue_write.cpp

# ----------------------------------
# optional add numberparse functions
# ----------------------------------
if USE_NUMFUNC
libunivalue_a_SOURCES += numberparse.cpp
endif

noinst_PROGRAMS = gen

gen_SOURCES = gen.cpp

