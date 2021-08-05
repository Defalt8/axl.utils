#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"

#ifdef AXUTIL_BUILD
#	error("AXUTIL_BUILD defined!")
#endif

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	if(assert::_num_failed_tests > 0 || verbose) puts("----------------------------------------");
	printf("# %d Failed!\n", assert::_num_failed_tests);
	return assert::_num_failed_tests;
}