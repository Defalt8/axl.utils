#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <wchar.h>
#include "Assert.hpp"
#include "lib.hpp"
#include <axl.util/WString.hpp>


int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u --- [WString] test\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	Assertve(sizeof(WString::char_t) == 2U, verbose);
	{ // Static variables tests
		Assertv(WString::NullWChar == '\0', verbose);
		Assertv(WString::NullCWStr == (const WString::char_t*)0, verbose);
		Assertv(WString::NullWStr == (WString::char_t*)0, verbose);
	}
	{ // Static methods tests
		{
			Assertv(WString::scwLength(L"Hello World!") == 12, verbose);
			Assertv(WString::scwLength(L"Hello World!", 13) == 12, verbose);
			Assertv(WString::scwLength(L"Hello World!", 12) == 12, verbose);
			Assertv(WString::scwLength(L"Hello World!", 11) == 11, verbose);
		}
		{
			WString::char_t buffer[32] = {L"123456789abcdef"};
			WString::scwCopy(L"Hello World!", buffer, 13);
			Assertv(0 == wcsncmp(buffer, L"Hello World!", 13), verbose);
		}
		{
			WString::char_t buffer[32] = L"123456789abcdef";
			WString::scwCopy(L"Hello World!", buffer, 7, 6);
			Assertv(0 == wcsncmp(buffer, L"World!", 7), verbose);
		}
		{
			WString::char_t buffer[32] = L"123456789abcdef";
			WString::scwCopy(L"Hello World!", buffer, 12, 0, 3);
			Assertv(0 == wcsncmp(buffer, L"123Hello World!", 16), verbose);
		}
		{
			WString::char_t buffer[32] = {L"123456789abcdef"};
			WString::scCopy("Hello World!", buffer, 13);
			Assertv(0 == wcsncmp(buffer, L"Hello World!", 13), verbose);
		}
		{
			WString::char_t buffer[32] = L"123456789abcdef";
			WString::scCopy("Hello World!", buffer, 7, 6);
			Assertv(0 == wcsncmp(buffer, L"World!", 7), verbose);
		}
		{
			WString::char_t buffer[32] = L"123456789abcdef";
			WString::scCopy("Hello World!", buffer, 12, 0, 3);
			Assertv(0 == wcsncmp(buffer, L"123Hello World!", 16), verbose);
		}
		{ // scEqual
			const WString::char_t* hello = L"Hello World!";
			Assertv(!WString::scwEquals(0, 0), verbose);
			Assertv(WString::scwEquals(L"", L""), verbose);
			Assertv(WString::scwEquals(L"1", L"1"), verbose);
			Assertv(!WString::scwEquals(L"1", L"2"), verbose);
			Assertv(WString::scwEquals(hello, L"Hello World!"), verbose);
			Assertv(!WString::scwEquals(hello, L"Hello World! "), verbose);
			Assertv(!WString::scwEquals(hello, L"Hello World"), verbose);
			Assertv(!WString::scwEquals(hello, L"Hello"), verbose);
			Assertv(!WString::scwEquals(hello, L"Hello Morld!"), verbose);
		}
	}
	{ // Destructor tests
		{ // Non-sensitive
			WString wstr(L"Hello");
			WString::char_t* cwstr = wstr.wstr();
			Assertv(0 == wcscmp(wstr.cwstr(), L"Hello"), verbose);
			Assertv(cwstr == wstr.cwstr(), verbose);
			wstr.destroy();
			Assertv(wstr.cwstr() == WString::NullCWStr, verbose);
			Assertv(wstr.size() == 0U, verbose);
			Assertv(wstr.length() == 0U, verbose);
			Assertv(wstr.length(false) == 0U, verbose);
			Assertv(wstr.length(true) == 0U, verbose);
		}
		{ // Sensitive
			WString wstr(L"Hello World! How are you?");
			WString::char_t* cwstr = wstr.wstr();
			Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World! How are you?"), verbose);
			Assertv(cwstr == wstr.cwstr(), verbose);
			wstr.destroy();
			Assertv(wstr.cwstr() == WString::NullCWStr, verbose);
			Assertv(wstr.size() == 0U, verbose);
			Assertv(wstr.length() == 0U, verbose);
			Assertv(wstr.length(false) == 0U, verbose);
			Assertv(wstr.length(true) == 0U, verbose);
			Assertv(0 != wcsncmp(cwstr, L"Hello World! How are you?", 6), verbose);
		}
	}
	{ // Constructor tests
		{ // Default constructor
			WString wstr;
			Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
			Assertv(wstr.cwstr() == wstr.wstr(), verbose);
			Assertv(wstr.isNull(), verbose);
			Assertv(wstr.size() == 1U, verbose);
			Assertv(wstr.length() == 0U, verbose);
			Assertv(wstr.cwstr()[0] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(wstr.cwstr(), L""), verbose);
		}
		{ // Length constructor
			WString wstr(12);
			Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
			Assertv(wstr.cwstr() == wstr.wstr(), verbose);
			Assertv(wstr.isNull(), verbose);
			Assertv(wstr.size() == 13U, verbose);
			Assertv(wstr.length() == 0U, verbose);
			Assertv(wstr.cwstr()[0] == WString::NullWChar, verbose);
			WString::scwCopy(L"Hello World!", wstr.wstr(), 13);
			Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
			Assertv(!wstr.isNull(), verbose);
			Assertv(wstr.size() == 13U, verbose);
			Assertv(wstr.length() == 0U, verbose);
			Assertv(wstr.length(true) == 12U, verbose);
			Assertv(wstr.length() == 12U, verbose);
			Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
		}
		{ // Cstring constructors
			{
				WString wstr(L"");
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr.cwstr() == wstr.wstr(), verbose);
				Assertv(wstr.isNull(), verbose);
				Assertv(wstr.size() == 1U, verbose);
				Assertv(wstr.length() == 0U, verbose);
				Assertv(wstr.cwstr()[0] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L""), verbose);
			}
			{
				WString wstr(L"Hello World!");
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr.cwstr() == wstr.wstr(), verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
			}
			{
				WString wstr(L"Hello World!", 5);
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr.cwstr() == wstr.wstr(), verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 6U, verbose);
				Assertv(wstr.length() == 5U, verbose);
				Assertv(wstr.cwstr()[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello"), verbose);
			}
			{
				WString wstr(L"Hello World!", 6, 6);
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr.cwstr() == wstr.wstr(), verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 7U, verbose);
				Assertv(wstr.length() == 6U, verbose);
				Assertv(wstr.cwstr()[6] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"World!"), verbose);
			}
		}
		{ // Copy constructors
			{
				WString wstr(L"Hello World!");
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr.cwstr() == wstr.wstr(), verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
				WString copy_str(wstr);
				Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
				Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
				Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
				Assertv(!copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 13U, verbose);
				Assertv(copy_str.length() == 12U, verbose);
				Assertv(copy_str.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(copy_str.cwstr(), L"Hello World!"), verbose);
			}
			{
				WString wstr(L"Hello World!");
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr.cwstr() == wstr.wstr(), verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
				wstr.wstr()[5] = WString::NullWChar;
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.length(true) == 5U, verbose);
				Assertv(wstr.length() == 5U, verbose);
				Assertv(wstr.cwstr()[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello"), verbose);
				Assertv(0 == wcsncmp(wstr.cwstr(), L"Hello\0World!", 13), verbose);
				WString copy_str(wstr);
				Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
				Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
				Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
				Assertv(!copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 6U, verbose);
				Assertv(copy_str.length() == 5U, verbose);
				Assertv(copy_str.cwstr()[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(copy_str.cwstr(), L"Hello"), verbose);
			}
			{
				const WString wstr(L"Hello World!");
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
				{
					WString copy_str(wstr, 5);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 6U, verbose);
					Assertv(copy_str.length() == 5U, verbose);
					Assertv(copy_str.cwstr()[5] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"Hello"), verbose);
				}
				{
					WString copy_str(wstr, 6, 6);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 7U, verbose);
					Assertv(copy_str.length() == 6U, verbose);
					Assertv(copy_str.cwstr()[6] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"World!"), verbose);
				}
				{
					WString copy_str(wstr, 0, 6);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L""), verbose);
				}
				{
					WString copy_str(wstr, 1, 6);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 2U, verbose);
					Assertv(copy_str.length() == 1U, verbose);
					Assertv(copy_str.cwstr()[1] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"W"), verbose);
				}
				{
					WString copy_str(wstr, 7, 6);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 7U, verbose);
					Assertv(copy_str.length() == 6U, verbose);
					Assertv(copy_str.cwstr()[6] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"World!"), verbose);
				}
				{
					WString copy_str(wstr, 8, 6);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 7U, verbose);
					Assertv(copy_str.length() == 6U, verbose);
					Assertv(copy_str.cwstr()[6] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"World!"), verbose);
				}
				{
					WString copy_str(wstr, 6, 11);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 2U, verbose);
					Assertv(copy_str.length() == 1U, verbose);
					Assertv(copy_str.cwstr()[1] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"!"), verbose);
				}
				{
					WString copy_str(wstr, 6, 12);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L""), verbose);
				}
				{
					WString copy_str(wstr, 6, 13);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L""), verbose);
				}
				{
					WString copy_str(wstr, 6, 14);
					Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
					Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L""), verbose);
				}
			}
			{
				const String str("Hello World!");
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
				{
					WString copy_str(str);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 13U, verbose);
					Assertv(copy_str.length() == 12U, verbose);
					Assertv(copy_str.cwstr()[12] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"Hello World!"), verbose);
				}
				{
					WString copy_str(str, 5);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 6U, verbose);
					Assertv(copy_str.length() == 5U, verbose);
					Assertv(copy_str.cwstr()[5] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"Hello"), verbose);
				}
				{
					WString copy_str(str, 6, 6);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 7U, verbose);
					Assertv(copy_str.length() == 6U, verbose);
					Assertv(copy_str.cwstr()[6] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"World!"), verbose);
				}
				{
					WString copy_str(str, 0, 6);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L""), verbose);
				}
				{
					WString copy_str(str, 1, 6);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 2U, verbose);
					Assertv(copy_str.length() == 1U, verbose);
					Assertv(copy_str.cwstr()[1] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"W"), verbose);
				}
				{
					WString copy_str(str, 7, 6);
					
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 7U, verbose);
					Assertv(copy_str.length() == 6U, verbose);
					Assertv(copy_str.cwstr()[6] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"World!"), verbose);
				}
				{
					WString copy_str(str, 8, 6);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 7U, verbose);
					Assertv(copy_str.length() == 6U, verbose);
					Assertv(copy_str.cwstr()[6] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"World!"), verbose);
				}
				{
					WString copy_str(str, 6, 11);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 2U, verbose);
					Assertv(copy_str.length() == 1U, verbose);
					Assertv(copy_str.cwstr()[1] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"!"), verbose);
				}
				{
					WString copy_str(str, 6, 12);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L""), verbose);
				}
				{
					WString copy_str(str, 6, 13);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L""), verbose);
				}
				{
					WString copy_str(str, 6, 14);
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L""), verbose);
				}
			}
		}
		{ // Move constructor
			{
				WString wstr(WString(L"Hello World!"));
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr.cwstr() == wstr.wstr(), verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
			}
		}
	}
	{ // Assignment operators
		{ // Copy assignment operators
			{
				const WString wstr(L"Hello World!");
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
				WString copy_str;
				Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
				Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
				Assertv(copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 1U, verbose);
				Assertv(copy_str.length() == 0U, verbose);
				Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
				copy_str = wstr;
				Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
				Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
				Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
				Assertv(!copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 13U, verbose);
				Assertv(copy_str.length() == 12U, verbose);
				Assertv(copy_str.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(copy_str.cwstr(), L"Hello World!"), verbose);
			}
			{
				WString wstr(L"Hello World!");
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr.cwstr() == wstr.wstr(), verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
				wstr.wstr()[5] = WString::NullWChar;
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.length(true) == 5U, verbose);
				Assertv(wstr.length() == 5U, verbose);
				Assertv(wstr.cwstr()[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello"), verbose);
				Assertv(0 == wcsncmp(wstr.cwstr(), L"Hello\0World!", 13), verbose);
				WString copy_str;
				Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
				Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
				Assertv(copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 1U, verbose);
				Assertv(copy_str.length() == 0U, verbose);
				Assertv(copy_str.cwstr()[0] == WString::NullWChar, verbose);
				copy_str = wstr;
				Assertv(wstr.cwstr() != copy_str.cwstr(), verbose);
				Assertv(copy_str.wstr() != WString::NullCWStr, verbose);
				Assertv(copy_str.cwstr() == copy_str.wstr(), verbose);
				Assertv(!copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 6U, verbose);
				Assertv(copy_str.length() == 5U, verbose);
				Assertv(copy_str.cwstr()[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(copy_str.cwstr(), L"Hello"), verbose);
			}
			{
				const String str("Hello World!");
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
				{
					WString copy_str;
					Assertv(copy_str.isNull(), verbose);
					copy_str = str;
					Assertv(copy_str.cwstr() != WString::NullCWStr, verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 13U, verbose);
					Assertv(copy_str.length() == 12U, verbose);
					Assertv(copy_str.cwstr()[12] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(copy_str.cwstr(), L"Hello World!"), verbose);
				}
			}
			{ // Cstring assignment operator
				WString wstr;
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr.isNull(), verbose);
				Assertv(wstr.size() == 1U, verbose);
				Assertv(wstr.length() == 0U, verbose);
				Assertv(wstr.cwstr()[0] == WString::NullWChar, verbose);
				wstr = L"Hello World!";
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
				wstr = L"Jello";
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 6U, verbose);
				Assertv(wstr.length() == 5U, verbose);
				Assertv(wstr.cwstr()[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Jello"), verbose);
				const WString::char_t* cwstr = wstr.cwstr();
				wstr = L"Hello";
				Assertv(wstr.cwstr() == cwstr, verbose);
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 6U, verbose);
				Assertv(wstr.length() == 5U, verbose);
				Assertv(wstr.cwstr()[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello"), verbose);
			}
		}
		{ // Move assignment operators
			const WString wstr = WString(L"Hello World!");
			Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
			Assertv(!wstr.isNull(), verbose);
			Assertv(wstr.size() == 13U, verbose);
			Assertv(wstr.length() == 12U, verbose);
			Assertv(wstr.cwstr()[12] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
		}
	}
	{ // Operators tests
		{ // Square bracket operators
			{
				const WString wstr = L"Hello World!";
				Assertv(wstr[0] == 'H', verbose);
				Assertv(wstr[10] == 'd', verbose);
				Assertv(wstr[11] == '!', verbose);
				Assertv(wstr[12] == '\0', verbose);
				Assertv(0 == wcscmp(&wstr[0], L"Hello World!"), verbose);
			}
			{
				WString wstr = L"Hello World!";
				Assertv(wstr[0] == 'H', verbose);
				Assertv(wstr[10] == 'd', verbose);
				Assertv(wstr[11] == '!', verbose);
				Assertv(wstr[12] == '\0', verbose);
				Assertv(0 == wcscmp(&wstr[0], L"Hello World!"), verbose);
				wstr[0] = 'J';
				Assertv(wstr[0] == 'J', verbose);
				Assertv(0 == wcscmp(&wstr[0], L"Jello World!"), verbose);
			}
		}
		{ // Addition operator
			{
				const WString str1 = L"Hello Mars!";
				const WString str2 = L"This is Earth.";
				WString wstr = str1 + str2;
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 26U, verbose);
				Assertv(wstr.length() == 25U, verbose);
				Assertv(wstr.cwstr()[25] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello Mars!This is Earth."), verbose);
			}
			{
				const WString str1 = L"Hello Mars!";
				const WString::char_t* str2 = L"This is Earth.";
				WString wstr = str1 + str2;
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 26U, verbose);
				Assertv(wstr.length() == 25U, verbose);
				Assertv(wstr.cwstr()[25] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello Mars!This is Earth."), verbose);
			}
			{
				WString wstr = L"Hello Mars!";
				const WString str2 = L"This is Earth.";
				wstr += str2;
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 26U, verbose);
				Assertv(wstr.length() == 25U, verbose);
				Assertv(wstr.cwstr()[25] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello Mars!This is Earth."), verbose);
			}
			{
				WString wstr = L"Hello Mars!";
				const WString::char_t* str2 = L"This is Earth.";
				wstr += str2;
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(!wstr.isNull(), verbose);
				Assertv(wstr.size() == 26U, verbose);
				Assertv(wstr.length() == 25U, verbose);
				Assertv(wstr.cwstr()[25] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello Mars!This is Earth."), verbose);
			}
		}
		
		{ // Comparison operators
			{ // Equality operator
				const WString str1 = L"Hello World!";
				const WString str2 = L"Hello World!";
				const WString str3 = L"Jello World!";
				const WString str4 = L"Hello Morld!";
				const WString str5 = L"Hello World";
				Assertv(str1 == str2, verbose);
				Assertv(!(str1 == str3), verbose);
				Assertv(!(str1 == str4), verbose);
				Assertv(!(str1 == str5), verbose);
			}
			{ // Inequality operator
				const WString str1 = L"Hello World!";
				const WString str2 = L"Hello World!";
				const WString str3 = L"Jello World!";
				const WString str4 = L"Hello Morld!";
				const WString str5 = L"Hello World";
				Assertv(!(str1 != str2), verbose);
				Assertv(str1 != str3, verbose);
				Assertv(str1 != str4, verbose);
				Assertv(str1 != str5, verbose);
			}
			{
				const WString Cat = L"Cat";
				const WString Car = L"Car";
				const WString Coat = L"Coat";
				const WString Apple = L"Apple";
				const WString Juice = L"Juice";
				const WString Ape = L"Ape";
				const WString Mango = L"Mango";
				{ // Greater than or equal to
					Assertv(Cat >= Cat, verbose);
					Assertv(Cat >= Car, verbose);
					Assertv(!(Cat >= Coat), verbose);
					Assertv(Cat >= Apple, verbose);
					Assertv(!(Cat >= Juice), verbose);
					Assertv(Cat >= Ape, verbose);
					Assertv(!(Cat >= Mango), verbose);
					Assertv(Juice >= Juice, verbose);
					Assertv(Juice >= Cat, verbose);
					Assertv(Juice >= Car, verbose);
					Assertv(Juice >= Coat, verbose);
					Assertv(Juice >= Apple, verbose);
					Assertv(Juice >= Ape, verbose);
					Assertv(!(Juice >= Mango), verbose);
				}
				{ // Less than or equal to
					Assertv(Cat <= Cat, verbose);
					Assertv(!(Cat <= Car), verbose);
					Assertv(Cat <= Coat, verbose);
					Assertv(!(Cat <= Apple), verbose);
					Assertv(Cat <= Juice, verbose);
					Assertv(!(Cat <= Ape), verbose);
					Assertv(Cat <= Mango, verbose);
					Assertv(Juice <= Juice, verbose);
					Assertv(!(Juice <= Cat), verbose);
					Assertv(!(Juice <= Car), verbose);
					Assertv(!(Juice <= Coat), verbose);
					Assertv(!(Juice <= Apple), verbose);
					Assertv(!(Juice <= Ape), verbose);
					Assertv(Juice <= Mango, verbose);
				}
				{ // Greater than
					Assertv(!(Cat > Cat), verbose);
					Assertv(Cat > Car, verbose);
					Assertv(!(Cat > Coat), verbose);
					Assertv(Cat > Apple, verbose);
					Assertv(!(Cat > Juice), verbose);
					Assertv(Cat > Ape, verbose);
					Assertv(!(Cat > Mango), verbose);
					Assertv(!(Juice > Juice), verbose);
					Assertv(Juice > Cat, verbose);
					Assertv(Juice > Car, verbose);
					Assertv(Juice > Coat, verbose);
					Assertv(Juice > Apple, verbose);
					Assertv(Juice > Ape, verbose);
					Assertv(!(Juice > Mango), verbose);
				}
				{ // Less than
					Assertv(!(Cat < Cat), verbose);
					Assertv(!(Cat < Car), verbose);
					Assertv(Cat < Coat, verbose);
					Assertv(!(Cat < Apple), verbose);
					Assertv(Cat < Juice, verbose);
					Assertv(!(Cat < Ape), verbose);
					Assertv(Cat < Mango, verbose);
					Assertv(!(Juice < Juice), verbose);
					Assertv(!(Juice < Cat), verbose);
					Assertv(!(Juice < Car), verbose);
					Assertv(!(Juice < Coat), verbose);
					Assertv(!(Juice < Apple), verbose);
					Assertv(!(Juice < Ape), verbose);
					Assertv(Juice < Mango, verbose);
				}
			}
		}
	}
	{ // Methods tests
		{ // Resize
			{
				WString wstr;
				Assertv(wstr.size() == 1U, verbose);
				Assertv(wstr.length() == 0U, verbose);
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr[0] == WString::NullWChar, verbose);
				Assertv(wstr.resize(5), verbose);
				Assertv(wstr.size() == 6U, verbose);
				Assertv(wstr.length() == 0U, verbose);
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr[0] == WString::NullWChar, verbose);
				Assertv(wstr.resize(2), verbose);
				Assertv(wstr.size() == 3U, verbose);
				Assertv(wstr.length() == 0U, verbose);
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr[0] == WString::NullWChar, verbose);
			}
			{
				WString wstr = L"Hello";
				Assertv(wstr.size() == 6U, verbose);
				Assertv(wstr.length() == 5U, verbose);
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello"), verbose);
				Assertv(wstr.resize(12), verbose);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 5U, verbose);
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello"), verbose);
				WString::scwCopy(L"Hello World!", wstr.wstr(), 13);
				Assertv(wstr.size() == 13U, verbose);
				Assertv(wstr.length() == 5U, verbose);
				Assertv(wstr.length(true) == 12U, verbose);
				Assertv(wstr.length() == 12U, verbose);
				Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
				Assertv(wstr[12] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
			}
		}
		{ // Append
			{ // Append WString
				{
					WString wstr = L"Hello World!";
					const WString app_str = L" It's me Nati.";
					wstr.append(app_str);
					Assertv(wstr.size() == 27U, verbose);
					Assertv(wstr.length() == 26U, verbose);
					Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
					Assertv(wstr[26] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World! It's me Nati."), verbose);
				}
				{
					WString wstr = L"Hello World!";
					const WString app_str = L" It's me Nati.";
					wstr.append(app_str, 0);
					Assertv(wstr.size() == 27U, verbose);
					Assertv(wstr.length() == 26U, verbose);
					Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
					Assertv(wstr[26] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World! It's me Nati."), verbose);
				}
				{
					WString wstr = L"Hello World!";
					const WString app_str = L" It's me Nati.";
					wstr.append(app_str, 8);
					Assertv(wstr.size() == 21U, verbose);
					Assertv(wstr.length() == 20U, verbose);
					Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
					Assertv(wstr[20] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World! It's me"), verbose);
				}
				{
					WString wstr = L"Hello World!";
					const WString app_str = L" It's me Nati.";
					wstr.append(app_str, 5, 9);
					Assertv(wstr.size() == 18U, verbose);
					Assertv(wstr.length() == 17U, verbose);
					Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
					Assertv(wstr[17] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!Nati."), verbose);
				}
			}
			{ // Append cstring
				{
					WString wstr = L"Hello World!";
					const WString::char_t* app_str = L" It's me Nati.";
					wstr.append(app_str);
					Assertv(wstr.size() == 27U, verbose);
					Assertv(wstr.length() == 26U, verbose);
					Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
					Assertv(wstr[26] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World! It's me Nati."), verbose);
				}
				{
					WString wstr = L"Hello World!";
					const WString::char_t* app_str = L" It's me Nati.";
					wstr.append(app_str, 0);
					Assertv(wstr.size() == 27U, verbose);
					Assertv(wstr.length() == 26U, verbose);
					Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
					Assertv(wstr[26] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World! It's me Nati."), verbose);
				}
				{
					WString wstr = L"Hello World!";
					const WString::char_t* app_str = L" It's me Nati.";
					wstr.append(app_str, 8);
					Assertv(wstr.size() == 21U, verbose);
					Assertv(wstr.length() == 20U, verbose);
					Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
					Assertv(wstr[20] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World! It's me"), verbose);
				}
				{
					WString wstr = L"Hello World!";
					const WString::char_t* app_str = L" It's me Nati.";
					wstr.append(app_str, 5, 9);
					Assertv(wstr.size() == 18U, verbose);
					Assertv(wstr.length() == 17U, verbose);
					Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
					Assertv(wstr[17] == WString::NullWChar, verbose);
					Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!Nati."), verbose);
				}
			}
		}
		{ // Substring
			const WString wstr = L"Hello World!";
			Assertv(wstr.size() == 13U, verbose);
			Assertv(wstr.length() == 12U, verbose);
			Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
			Assertv(wstr[12] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
			{
				const WString sub_str = wstr.substring(5);
				Assertv(sub_str.size() == 6U, verbose);
				Assertv(sub_str.length() == 5U, verbose);
				Assertv(sub_str.cwstr() != WString::NullCWStr, verbose);
				Assertv(sub_str[5] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(sub_str.cwstr(), L"Hello"), verbose);
			}
			{
				const WString sub_str = wstr.substring(6, 6);
				Assertv(sub_str.size() == 7U, verbose);
				Assertv(sub_str.length() == 6U, verbose);
				Assertv(sub_str.cwstr() != WString::NullCWStr, verbose);
				Assertv(sub_str[6] == WString::NullWChar, verbose);
				Assertv(0 == wcscmp(sub_str.cwstr(), L"World!"), verbose);
			}
		}
		{ // Reverse
			const WString wstr = L"Hello World!";
			Assertv(wstr.size() == 13U, verbose);
			Assertv(wstr.length() == 12U, verbose);
			Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
			Assertv(wstr[12] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World!"), verbose);
			const WString rev_str = wstr.reverse();
			Assertv(rev_str.size() == 13U, verbose);
			Assertv(rev_str.length() == 12U, verbose);
			Assertv(rev_str.cwstr() != WString::NullCWStr, verbose);
			Assertv(rev_str[12] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(rev_str.cwstr(), L"!dlroW olleH"), verbose);
		}
		{ // ToUpper
			const WString wstr = L"Hello World! 1234@#$%";
			Assertv(wstr.size() == 22U, verbose);
			Assertv(wstr.length() == 21U, verbose);
			Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
			Assertv(wstr[21] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(wstr.cwstr(), L"Hello World! 1234@#$%"), verbose);
			const WString upper_str = wstr.toUpper();
			Assertv(upper_str.size() == 22U, verbose);
			Assertv(upper_str.length() == 21U, verbose);
			Assertv(upper_str.cwstr() != WString::NullCWStr, verbose);
			Assertv(upper_str[21] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(upper_str.cwstr(), L"HELLO WORLD! 1234@#$%"), verbose);
		}
		{ // ToLower
			const WString wstr = L"HeLLo WoRLD! 1234@#$%";
			Assertv(wstr.size() == 22U, verbose);
			Assertv(wstr.length() == 21U, verbose);
			Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
			Assertv(wstr[21] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(wstr.cwstr(), L"HeLLo WoRLD! 1234@#$%"), verbose);
			const WString lower_str = wstr.toLower();
			Assertv(lower_str.size() == 22U, verbose);
			Assertv(lower_str.length() == 21U, verbose);
			Assertv(lower_str.cwstr() != WString::NullCWStr, verbose);
			Assertv(lower_str[21] == WString::NullWChar, verbose);
			Assertv(0 == wcscmp(lower_str.cwstr(), L"hello world! 1234@#$%"), verbose);
		}
		{ // format
			{
				WString str(18);
				Assertv(str.format(L"Doom%s %d", L"Ethernal", 3) == L"DoomEthernal 3", verbose);
			}
			{
				WString str(15);
				Assertv(str.format(L"Doom%s %d", L"Ethernal", 3) == L"DoomEthernal 3", verbose);
			}
			{
				WString str(35);
				Assertv(str.format(L"Temperature: %.1f, %.1lf", 24.5f, 72.66f) == L"Temperature: 24.5, 72.7", verbose);
			}
		}
		{ // ToString
			WString wstr = L"Hello Mars!";
			Assertv(wstr.size() == 12U, verbose);
			Assertv(wstr.length() == 11U, verbose);
			Assertv(wstr.cwstr() != WString::NullCWStr, verbose);
			Assertv(0 == wcscmp(wstr.cwstr(), L"Hello Mars!"), verbose);
			String str = wstr.toString();
			Assertv(str.size() == 12U, verbose);
			Assertv(str.length() == 11U, verbose);
			Assertv(str.cstr() != String::NullCStr, verbose);
			Assertv(0 == strcmp(str.cstr(), "Hello Mars!"), verbose);
		}
	}
	if(assert::_num_failed_tests > 0) puts("----------------------------------------");
	printf("# %d Failed!\n", assert::_num_failed_tests);
	return assert::_num_failed_tests;
}