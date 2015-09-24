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

TESTS = test/unitester

noinst_PROGRAMS = lib/gen $(TESTS)

lib_gen_SOURCES = lib/gen.cpp

TEST_DATA_DIR=test

test_unitester_SOURCES = test/unitester.cpp
test_unitester_LDADD = lib/libunivalue.la
test_unitester_CXXFLAGS = -I$(top_srcdir)/lib -DJSON_TEST_SRC=\"$(srcdir)/$(TEST_DATA_DIR)\"

TEST_FILES = \
	$(TEST_DATA_DIR)/fail10.json \
	$(TEST_DATA_DIR)/fail11.json \
	$(TEST_DATA_DIR)/fail12.json \
	$(TEST_DATA_DIR)/fail13.json \
	$(TEST_DATA_DIR)/fail14.json \
	$(TEST_DATA_DIR)/fail15.json \
	$(TEST_DATA_DIR)/fail16.json \
	$(TEST_DATA_DIR)/fail17.json \
	$(TEST_DATA_DIR)/fail18.json \
	$(TEST_DATA_DIR)/fail19.json \
	$(TEST_DATA_DIR)/fail1.json \
	$(TEST_DATA_DIR)/fail20.json \
	$(TEST_DATA_DIR)/fail21.json \
	$(TEST_DATA_DIR)/fail22.json \
	$(TEST_DATA_DIR)/fail23.json \
	$(TEST_DATA_DIR)/fail24.json \
	$(TEST_DATA_DIR)/fail25.json \
	$(TEST_DATA_DIR)/fail26.json \
	$(TEST_DATA_DIR)/fail27.json \
	$(TEST_DATA_DIR)/fail28.json \
	$(TEST_DATA_DIR)/fail29.json \
	$(TEST_DATA_DIR)/fail2.json \
	$(TEST_DATA_DIR)/fail30.json \
	$(TEST_DATA_DIR)/fail31.json \
	$(TEST_DATA_DIR)/fail32.json \
	$(TEST_DATA_DIR)/fail33.json \
	$(TEST_DATA_DIR)/fail34.json \
	$(TEST_DATA_DIR)/fail3.json \
	$(TEST_DATA_DIR)/fail4.json \
	$(TEST_DATA_DIR)/fail5.json \
	$(TEST_DATA_DIR)/fail6.json \
	$(TEST_DATA_DIR)/fail7.json \
	$(TEST_DATA_DIR)/fail8.json \
	$(TEST_DATA_DIR)/fail9.json \
	$(TEST_DATA_DIR)/pass1.json \
	$(TEST_DATA_DIR)/pass2.json \
	$(TEST_DATA_DIR)/pass3.json

EXTRA_DIST=$(TEST_FILES)
