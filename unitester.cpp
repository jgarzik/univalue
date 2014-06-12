#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cassert>
#include <string>
#include "univalue.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

using namespace std;

static void runtest(const char *filename, const string& jdata)
{
	fprintf(stderr, "test %s\n", filename);

	string filename_(filename);
	string prefix = filename_.substr(0, 4);

	bool wantPass = (prefix == "pass");
	bool wantFail = (prefix == "fail");
	assert(wantPass || wantFail);

	bool testResult = true;
	try {
	    UniValue val;
	    val.read(jdata);
	}
	catch (std::exception& e) {
	    string strPrint = string("error: ") + e.what();
	    fprintf(stderr, "%s\n", strPrint.c_str());
	    testResult = false;
	}
	catch (...) {
	    string strPrint = string("unknown exception");
	    fprintf(stderr, "%s\n", strPrint.c_str());
	    testResult = false;
	}

	if (wantPass) {
	    assert(testResult == true);
	} else {
	    assert(testResult == false);
	}
}

static void runtest_file(const char *filename)
{
	FILE *f = fopen(filename, "r");
	assert(f != NULL);

	string jdata;

	char buf[4096];
	while (!feof(f)) {
		int bread = fread(buf, 1, sizeof(buf), f);
		assert(!ferror(f));

		string s(buf, bread);
		jdata += s;
	}

	assert(!ferror(f));
	fclose(f);

	runtest(filename, jdata);
}

static const char *filenames[] = {
        "fail10.json",
        "fail11.json",
        "fail12.json",
        "fail13.json",
        "fail14.json",
        "fail15.json",
        "fail16.json",
        "fail17.json",
        "fail18.json",
        "fail19.json",
        "fail1.json",
        "fail20.json",
        "fail21.json",
        "fail22.json",
        "fail23.json",
        "fail24.json",
        "fail25.json",
        "fail26.json",
        "fail27.json",
        "fail28.json",
        "fail29.json",
        "fail2.json",
        "fail30.json",
        "fail31.json",
        "fail32.json",
        //"fail33.json",
        "fail3.json",
        "fail4.json",
        "fail5.json",
        "fail6.json",
        "fail7.json",
        "fail8.json",
        //"fail9.json",
        //"pass1.json",
        //"pass2.json",
        "pass3.json",
};

int main (int argc, char *argv[])
{
    for (unsigned int fidx = 0; fidx < ARRAY_SIZE(filenames); fidx++) {
        runtest_file(filenames[fidx]);
    }
}

