#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"
#include <axl.util/File.hpp>

const axl::util::String LICENSE_STR = 
"MIT License\n"
"\n"
"Copyright (c) 2021 Natnael Eshetu\n"
"\n"
"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
"of this software and associated documentation files (the \"Software\"), to deal\n"
"in the Software without restriction, including without limitation the rights\n"
"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
"copies of the Software, and to permit persons to whom the Software is\n"
"furnished to do so, subject to the following conditions:\n"
"\n"
"The above copyright notice and this permission notice shall be included in all\n"
"copies or substantial portions of the Software.\n"
"\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
"SOFTWARE.\n";

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u --- [File] test\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	{ // File::exists
		Assertv(File::exists(AXLUTIL_SOURCE_DIR"/LICENSE"), verbose);
		Assertv(!File::exists("non_existent_file.nope"), verbose);
	}
	{ // File::getSize
		Assertv(File::getSize(AXLUTIL_SOURCE_DIR"/LICENSE") == 1092, verbose);
		Assertv(File::getSize("non_existent_file.nope") == 0, verbose);
	}
	{ // File::getStringContent
		Assertv(File::getStringContent(AXLUTIL_SOURCE_DIR"/LICENSE") == LICENSE_STR, verbose);
		Assertv(File::getWStringContent(AXLUTIL_SOURCE_DIR"/LICENSE") == WString(LICENSE_STR), verbose);
	}
	
	if(assert::_num_failed_tests > 0) puts("----------------------------------------");
	printf("# %d Failed!\n", assert::_num_failed_tests);
	return assert::_num_failed_tests;
}