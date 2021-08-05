#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"
#include <axl.util/Directory.hpp>

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u --- [Directory] test\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	{ // Directory::extractPath
		Assertv(Directory::extractParent(L"") == L"", verbose);
		Assertv(Directory::extractParent(L".") == L".", verbose);
		Assertv(Directory::extractParent(L"\\") == L"\\", verbose);
		Assertv(Directory::extractParent(L"/") == L"/", verbose);
		Assertv(Directory::extractParent(L"/usr") == L"/", verbose);
		Assertv(Directory::extractParent(L"/usr/lib") == L"/usr", verbose);
		Assertv(Directory::extractParent(L"/usr/lib/axl.util") == L"/usr/lib", verbose);
		Assertv(Directory::extractParent(L"/usr/lib/axl.util", 2) == L"/usr", verbose);
		Assertv(Directory::extractParent(L"/usr/lib/axl.util", 3) == L"/", verbose);
		Assertv(Directory::extractParent(L"usr/lib/axl.util", 3) == L"", verbose);
	}
	{ // Directory::exists
		Assertv(Directory::exists(WString(argv[0])), verbose);
		Assertv(!Directory::exists(L"non_existent_file.nope"), verbose);
	}
	{ // Directory::isDirectory
		Assertv(!Directory::isDirectory(WString(argv[0])), verbose);
		Assertv(!Directory::isDirectory(L"non_existent_file.nope"), verbose);
		Assertv(Directory::isDirectory(Directory::extractParent(WString(argv[0]))), verbose);
	}
	{ // Directory::isFile
		Assertv(Directory::isFile(WString(argv[0])), verbose);
		Assertv(!Directory::isFile(L"non_existent_file.nope"), verbose);
		Assertv(!Directory::isFile(Directory::extractParent(WString(argv[0]))), verbose);
	}
	{ // Directory::getDirItems
		{ // unfiltered
			ds::UniList<Directory::DirItem> dir_items = Directory::getDirItems(AXLUTIL_TEST_DIR);
			Assertv(dir_items.count() != 0, verbose);
			for(auto it=dir_items.first(); it.isNotNull(); ++it)
			{
				Assertv(it.value().name.length() > 0, verbose);
				Assertv(it.value().type != Directory::DIT_UNSPECIFIED, verbose);
				// wprintf(L"%c   %ws\n", it.value().type==Directory::DIT_DIRECTORY ? 'd' : 'f', it.value().name.cwstr());
			}
		}
		{ // filtered directories only
			ds::UniList<Directory::DirItem> dir_items = Directory::getDirItems(AXLUTIL_TEST_DIR, Directory::DIT_DIRECTORY);
			Assertv(dir_items.count() != 0, verbose);
			for(auto it=dir_items.first(); it.isNotNull(); ++it)
			{
				Assertv(it.value().name.length() > 0, verbose);
				Assertv(it.value().type == Directory::DIT_DIRECTORY, verbose);
			}
		}
		{ // filtered files only
			ds::UniList<Directory::DirItem> dir_items = Directory::getDirItems(AXLUTIL_TEST_DIR, Directory::DIT_FILE);
			Assertv(dir_items.count() != 0, verbose);
			for(auto it=dir_items.first(); it.isNotNull(); ++it)
			{
				Assertv(it.value().name.length() > 0, verbose);
				Assertv(it.value().type == Directory::DIT_FILE, verbose);
			}
		}
		{ // get max dir items
			ds::UniList<Directory::DirItem> dir_items;
			dir_items = Directory::getDirItems(AXLUTIL_TEST_DIR, 3, 0);
			Assertv(dir_items.count() == 0, verbose);
			dir_items = Directory::getDirItems(AXLUTIL_TEST_DIR, 3, 1);
			Assertv(dir_items.count() == 1, verbose);
			dir_items = Directory::getDirItems(AXLUTIL_TEST_DIR, 3, 2);
			Assertv(dir_items.count() == 2, verbose);
		}
	}
	if(assert::_num_failed_tests > 0) puts("----------------------------------------");
	printf("# %d Failed!\n", assert::_num_failed_tests);
	return assert::_num_failed_tests;
}