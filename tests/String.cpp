#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"
#include <axl.util/String.hpp>


int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u --- [String] test\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	Assertve(sizeof(String::char_t) == 1U, verbose);
	{ // Static variables tests
		Assertv(String::NullChar == '\0', verbose);
		Assertv(String::NullCStr == (const String::char_t*)0, verbose);
		Assertv(String::NullStr == (String::char_t*)0, verbose);
	}
	{ // Static methods tests
		{
			Assertv(String::scLength("Hello World!") == 12, verbose);
			Assertv(String::scLength("Hello World!", 13) == 12, verbose);
			Assertv(String::scLength("Hello World!", 12) == 12, verbose);
			Assertv(String::scLength("Hello World!", 11) == 11, verbose);
		}
		{
			String::char_t buffer[32] = {"123456789abcdef"};
			String::scCopy("Hello World!", buffer, 13);
			Assertv(0 == strncmp(buffer, "Hello World!", 13), verbose);
		}
		{
			String::char_t buffer[32] = "123456789abcdef";
			String::scCopy("Hello World!", buffer, 7, 6);
			Assertv(0 == strncmp(buffer, "World!", 7), verbose);
		}
		{
			String::char_t buffer[32] = "123456789abcdef";
			String::scCopy("Hello World!", buffer, 12, 0, 3);
			Assertv(0 == strncmp(buffer, "123Hello World!", 16), verbose);
		}
		{ // scEqual
			const String::char_t* hello = "Hello World!";
			Assertv(!String::scEquals(0, 0), verbose);
			Assertv(String::scEquals("", ""), verbose);
			Assertv(String::scEquals("1", "1"), verbose);
			Assertv(!String::scEquals("1", "2"), verbose);
			Assertv(String::scEquals(hello, "Hello World!"), verbose);
			Assertv(!String::scEquals(hello, "Hello World! "), verbose);
			Assertv(!String::scEquals(hello, "Hello World"), verbose);
			Assertv(!String::scEquals(hello, "Hello"), verbose);
			Assertv(!String::scEquals(hello, "Hello Morld!"), verbose);
		}
	}
	{ // Destructor tests
		{ // Non-sensitive
			String str("Hello");
			String::char_t* cstr = str.str();
			Assertv(0 == strcmp(str.cstr(), "Hello"), verbose);
			Assertv(cstr == str.cstr(), verbose);
			str.destroy();
			Assertv(str.cstr() == String::NullCStr, verbose);
			Assertv(str.size() == 0U, verbose);
			Assertv(str.length() == 0U, verbose);
			Assertv(str.length(false) == 0U, verbose);
			Assertv(str.length(true) == 0U, verbose);
		}
		{ // Sensitive
			String str("Hello World! How are you?");
			String::char_t* cstr = str.str();
			Assertv(0 == strcmp(str.cstr(), "Hello World! How are you?"), verbose);
			Assertv(cstr == str.cstr(), verbose);
			str.destroy();
			Assertv(str.cstr() == String::NullCStr, verbose);
			Assertv(str.size() == 0U, verbose);
			Assertv(str.length() == 0U, verbose);
			Assertv(str.length(false) == 0U, verbose);
			Assertv(str.length(true) == 0U, verbose);
			Assertv(0 != strncmp(cstr, "Hello World! How are you?", 6), verbose);
		}
	}
	{ // Constructor tests
		{ // Default constructor
			String str;
			Assertv(str.cstr() != String::NullCStr, verbose);
			Assertv(str.cstr() == str.str(), verbose);
			Assertv(str.isNull(), verbose);
			Assertv(str.size() == 1U, verbose);
			Assertv(str.length() == 0U, verbose);
			Assertv(str.cstr()[0] == String::NullChar, verbose);
			Assertv(0 == strcmp(str.cstr(), ""), verbose);
		}
		{ // Length constructor
			String str(12);
			Assertv(str.cstr() != String::NullCStr, verbose);
			Assertv(str.cstr() == str.str(), verbose);
			Assertv(str.isNull(), verbose);
			Assertv(str.size() == 13U, verbose);
			Assertv(str.length() == 0U, verbose);
			Assertv(str.cstr()[0] == String::NullChar, verbose);
			String::scCopy("Hello World!", str.str(), 13);
			Assertv(str.cstr() != String::NullCStr, verbose);
			Assertv(!str.isNull(), verbose);
			Assertv(str.size() == 13U, verbose);
			Assertv(str.length() == 0U, verbose);
			Assertv(str.length(true) == 12U, verbose);
			Assertv(str.length() == 12U, verbose);
			Assertv(str.cstr()[12] == String::NullChar, verbose);
			Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
		}
		{ // Cstring constructors
			{
				String str("");
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str.cstr() == str.str(), verbose);
				Assertv(str.isNull(), verbose);
				Assertv(str.size() == 1U, verbose);
				Assertv(str.length() == 0U, verbose);
				Assertv(str.cstr()[0] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), ""), verbose);
			}
			{
				String str("Hello World!");
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str.cstr() == str.str(), verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
			}
			{
				String str("Hello World!", 5);
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str.cstr() == str.str(), verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 6U, verbose);
				Assertv(str.length() == 5U, verbose);
				Assertv(str.cstr()[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello"), verbose);
			}
			{
				String str("Hello World!", 6, 6);
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str.cstr() == str.str(), verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 7U, verbose);
				Assertv(str.length() == 6U, verbose);
				Assertv(str.cstr()[6] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "World!"), verbose);
			}
		}
		{ // Copy constructors
			{
				String str("Hello World!");
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str.cstr() == str.str(), verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
				String copy_str(str);
				Assertv(str.cstr() != copy_str.cstr(), verbose);
				Assertv(copy_str.str() != String::NullCStr, verbose);
				Assertv(copy_str.cstr() == copy_str.str(), verbose);
				Assertv(!copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 13U, verbose);
				Assertv(copy_str.length() == 12U, verbose);
				Assertv(copy_str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(copy_str.cstr(), "Hello World!"), verbose);
			}
			{
				String str("Hello World!");
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str.cstr() == str.str(), verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
				str.str()[5] = String::NullChar;
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.length(true) == 5U, verbose);
				Assertv(str.length() == 5U, verbose);
				Assertv(str.cstr()[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello"), verbose);
				Assertv(0 == strncmp(str.cstr(), "Hello\0World!", 13), verbose);
				String copy_str(str);
				Assertv(str.cstr() != copy_str.cstr(), verbose);
				Assertv(copy_str.str() != String::NullCStr, verbose);
				Assertv(copy_str.cstr() == copy_str.str(), verbose);
				Assertv(!copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 6U, verbose);
				Assertv(copy_str.length() == 5U, verbose);
				Assertv(copy_str.cstr()[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(copy_str.cstr(), "Hello"), verbose);
			}
			{
				const String str("Hello World!");
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
				{
					String copy_str(str, 5);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 6U, verbose);
					Assertv(copy_str.length() == 5U, verbose);
					Assertv(copy_str.cstr()[5] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), "Hello"), verbose);
				}
				{
					String copy_str(str, 6, 6);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 7U, verbose);
					Assertv(copy_str.length() == 6U, verbose);
					Assertv(copy_str.cstr()[6] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), "World!"), verbose);
				}
				{
					String copy_str(str, 0, 6);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cstr()[0] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), ""), verbose);
				}
				{
					String copy_str(str, 1, 6);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 2U, verbose);
					Assertv(copy_str.length() == 1U, verbose);
					Assertv(copy_str.cstr()[1] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), "W"), verbose);
				}
				{
					String copy_str(str, 7, 6);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 7U, verbose);
					Assertv(copy_str.length() == 6U, verbose);
					Assertv(copy_str.cstr()[6] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), "World!"), verbose);
				}
				{
					String copy_str(str, 8, 6);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 7U, verbose);
					Assertv(copy_str.length() == 6U, verbose);
					Assertv(copy_str.cstr()[6] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), "World!"), verbose);
				}
				{
					String copy_str(str, 6, 11);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(!copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 2U, verbose);
					Assertv(copy_str.length() == 1U, verbose);
					Assertv(copy_str.cstr()[1] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), "!"), verbose);
				}
				{
					String copy_str(str, 6, 12);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cstr()[0] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), ""), verbose);
				}
				{
					String copy_str(str, 6, 13);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cstr()[0] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), ""), verbose);
				}
				{
					String copy_str(str, 6, 14);
					Assertv(str.cstr() != copy_str.cstr(), verbose);
					Assertv(copy_str.str() != String::NullCStr, verbose);
					Assertv(copy_str.cstr() == copy_str.str(), verbose);
					Assertv(copy_str.isNull(), verbose);
					Assertv(copy_str.size() == 1U, verbose);
					Assertv(copy_str.length() == 0U, verbose);
					Assertv(copy_str.cstr()[0] == String::NullChar, verbose);
					Assertv(0 == strcmp(copy_str.cstr(), ""), verbose);
				}
			}
		}
		{ // Move constructor
			{
				String str(String("Hello World!"));
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str.cstr() == str.str(), verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
			}
		}
	}
	{ // Assignment operators
		{ // Copy assignment operators
			{
				const String str("Hello World!");
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
				String copy_str;
				Assertv(copy_str.cstr() != String::NullCStr, verbose);
				Assertv(copy_str.cstr() == copy_str.str(), verbose);
				Assertv(copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 1U, verbose);
				Assertv(copy_str.length() == 0U, verbose);
				Assertv(copy_str.cstr()[0] == String::NullChar, verbose);
				copy_str = str;
				Assertv(str.cstr() != copy_str.cstr(), verbose);
				Assertv(copy_str.str() != String::NullCStr, verbose);
				Assertv(copy_str.cstr() == copy_str.str(), verbose);
				Assertv(!copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 13U, verbose);
				Assertv(copy_str.length() == 12U, verbose);
				Assertv(copy_str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(copy_str.cstr(), "Hello World!"), verbose);
			}
			{
				String str("Hello World!");
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str.cstr() == str.str(), verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
				str.str()[5] = String::NullChar;
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.length(true) == 5U, verbose);
				Assertv(str.length() == 5U, verbose);
				Assertv(str.cstr()[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello"), verbose);
				Assertv(0 == strncmp(str.cstr(), "Hello\0World!", 13), verbose);
				String copy_str;
				Assertv(copy_str.cstr() != String::NullCStr, verbose);
				Assertv(copy_str.cstr() == copy_str.str(), verbose);
				Assertv(copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 1U, verbose);
				Assertv(copy_str.length() == 0U, verbose);
				Assertv(copy_str.cstr()[0] == String::NullChar, verbose);
				copy_str = str;
				Assertv(str.cstr() != copy_str.cstr(), verbose);
				Assertv(copy_str.str() != String::NullCStr, verbose);
				Assertv(copy_str.cstr() == copy_str.str(), verbose);
				Assertv(!copy_str.isNull(), verbose);
				Assertv(copy_str.size() == 6U, verbose);
				Assertv(copy_str.length() == 5U, verbose);
				Assertv(copy_str.cstr()[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(copy_str.cstr(), "Hello"), verbose);
			}
			{ // Cstring assignment operator
				String str;
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str.isNull(), verbose);
				Assertv(str.size() == 1U, verbose);
				Assertv(str.length() == 0U, verbose);
				Assertv(str.cstr()[0] == String::NullChar, verbose);
				str = "Hello World!";
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.cstr()[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
				str = "Jello";
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 6U, verbose);
				Assertv(str.length() == 5U, verbose);
				Assertv(str.cstr()[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Jello"), verbose);
				const String::char_t* cstr = str.cstr();
				str = "Hello";
				Assertv(str.cstr() == cstr, verbose);
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 6U, verbose);
				Assertv(str.length() == 5U, verbose);
				Assertv(str.cstr()[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello"), verbose);
			}
		}
		{ // Move assignment operators
			const String str = String("Hello World!");
			Assertv(str.cstr() != String::NullCStr, verbose);
			Assertv(!str.isNull(), verbose);
			Assertv(str.size() == 13U, verbose);
			Assertv(str.length() == 12U, verbose);
			Assertv(str.cstr()[12] == String::NullChar, verbose);
			Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
		}
	}
	{ // Operators tests
		{ // Square bracket operators
			{
				const String str = "Hello World!";
				Assertv(str[0] == 'H', verbose);
				Assertv(str[10] == 'd', verbose);
				Assertv(str[11] == '!', verbose);
				Assertv(str[12] == '\0', verbose);
				Assertv(0 == strcmp(&str[0], "Hello World!"), verbose);
			}
			{
				String str = "Hello World!";
				Assertv(str[0] == 'H', verbose);
				Assertv(str[10] == 'd', verbose);
				Assertv(str[11] == '!', verbose);
				Assertv(str[12] == '\0', verbose);
				Assertv(0 == strcmp(&str[0], "Hello World!"), verbose);
				str[0] = 'J';
				Assertv(str[0] == 'J', verbose);
				Assertv(0 == strcmp(&str[0], "Jello World!"), verbose);
			}
		}
		{ // Addition operator
			{
				const String str1 = "Hello Mars!";
				const String str2 = "This is Earth.";
				String str = str1 + str2;
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 26U, verbose);
				Assertv(str.length() == 25U, verbose);
				Assertv(str.cstr()[25] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello Mars!This is Earth."), verbose);
			}
			{
				const String str1 = "Hello Mars!";
				const String::char_t* str2 = "This is Earth.";
				String str = str1 + str2;
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 26U, verbose);
				Assertv(str.length() == 25U, verbose);
				Assertv(str.cstr()[25] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello Mars!This is Earth."), verbose);
			}
			{
				String str = "Hello Mars!";
				const String str2 = "This is Earth.";
				str += str2;
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 26U, verbose);
				Assertv(str.length() == 25U, verbose);
				Assertv(str.cstr()[25] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello Mars!This is Earth."), verbose);
			}
			{
				String str = "Hello Mars!";
				const String::char_t* str2 = "This is Earth.";
				str += str2;
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(!str.isNull(), verbose);
				Assertv(str.size() == 26U, verbose);
				Assertv(str.length() == 25U, verbose);
				Assertv(str.cstr()[25] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello Mars!This is Earth."), verbose);
			}
		}
		
		{ // Comparison operators
			{ // Equality operator
				const String str1 = "Hello World!";
				const String str2 = "Hello World!";
				const String str3 = "Jello World!";
				const String str4 = "Hello Morld!";
				const String str5 = "Hello World";
				Assertv(str1 == str2, verbose);
				Assertv(!(str1 == str3), verbose);
				Assertv(!(str1 == str4), verbose);
				Assertv(!(str1 == str5), verbose);
			}
			{ // Inequality operator
				const String str1 = "Hello World!";
				const String str2 = "Hello World!";
				const String str3 = "Jello World!";
				const String str4 = "Hello Morld!";
				const String str5 = "Hello World";
				Assertv(!(str1 != str2), verbose);
				Assertv(str1 != str3, verbose);
				Assertv(str1 != str4, verbose);
				Assertv(str1 != str5, verbose);
			}
			{
				const String Cat = "Cat";
				const String Car = "Car";
				const String Coat = "Coat";
				const String Apple = "Apple";
				const String Juice = "Juice";
				const String Ape = "Ape";
				const String Mango = "Mango";
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
				String str;
				Assertv(str.size() == 1U, verbose);
				Assertv(str.length() == 0U, verbose);
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str[0] == String::NullChar, verbose);
				Assertv(str.resize(5), verbose);
				Assertv(str.size() == 6U, verbose);
				Assertv(str.length() == 0U, verbose);
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str[0] == String::NullChar, verbose);
				Assertv(str.resize(2), verbose);
				Assertv(str.size() == 3U, verbose);
				Assertv(str.length() == 0U, verbose);
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str[0] == String::NullChar, verbose);
			}
			{
				String str = "Hello";
				Assertv(str.size() == 6U, verbose);
				Assertv(str.length() == 5U, verbose);
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello"), verbose);
				Assertv(str.resize(12), verbose);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 5U, verbose);
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello"), verbose);
				String::scCopy("Hello World!", str.str(), 13);
				Assertv(str.size() == 13U, verbose);
				Assertv(str.length() == 5U, verbose);
				Assertv(str.length(true) == 12U, verbose);
				Assertv(str.length() == 12U, verbose);
				Assertv(str.cstr() != String::NullCStr, verbose);
				Assertv(str[12] == String::NullChar, verbose);
				Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
			}
		}
		{ // Append
			{ // Append String
				{
					String str = "Hello World!";
					const String app_str = " It's me Nati.";
					str.append(app_str);
					Assertv(str.size() == 27U, verbose);
					Assertv(str.length() == 26U, verbose);
					Assertv(str.cstr() != String::NullCStr, verbose);
					Assertv(str[26] == String::NullChar, verbose);
					Assertv(0 == strcmp(str.cstr(), "Hello World! It's me Nati."), verbose);
				}
				{
					String str = "Hello World!";
					const String app_str = " It's me Nati.";
					str.append(app_str, 0);
					Assertv(str.size() == 27U, verbose);
					Assertv(str.length() == 26U, verbose);
					Assertv(str.cstr() != String::NullCStr, verbose);
					Assertv(str[26] == String::NullChar, verbose);
					Assertv(0 == strcmp(str.cstr(), "Hello World! It's me Nati."), verbose);
				}
				{
					String str = "Hello World!";
					const String app_str = " It's me Nati.";
					str.append(app_str, 8);
					Assertv(str.size() == 21U, verbose);
					Assertv(str.length() == 20U, verbose);
					Assertv(str.cstr() != String::NullCStr, verbose);
					Assertv(str[20] == String::NullChar, verbose);
					Assertv(0 == strcmp(str.cstr(), "Hello World! It's me"), verbose);
				}
				{
					String str = "Hello World!";
					const String app_str = " It's me Nati.";
					str.append(app_str, 5, 9);
					Assertv(str.size() == 18U, verbose);
					Assertv(str.length() == 17U, verbose);
					Assertv(str.cstr() != String::NullCStr, verbose);
					Assertv(str[17] == String::NullChar, verbose);
					Assertv(0 == strcmp(str.cstr(), "Hello World!Nati."), verbose);
				}
			}
			{ // Append cstring
				{
					String str = "Hello World!";
					const char* app_str = " It's me Nati.";
					str.append(app_str);
					Assertv(str.size() == 27U, verbose);
					Assertv(str.length() == 26U, verbose);
					Assertv(str.cstr() != String::NullCStr, verbose);
					Assertv(str[26] == String::NullChar, verbose);
					Assertv(0 == strcmp(str.cstr(), "Hello World! It's me Nati."), verbose);
				}
				{
					String str = "Hello World!";
					const char* app_str = " It's me Nati.";
					str.append(app_str, 0);
					Assertv(str.size() == 27U, verbose);
					Assertv(str.length() == 26U, verbose);
					Assertv(str.cstr() != String::NullCStr, verbose);
					Assertv(str[26] == String::NullChar, verbose);
					Assertv(0 == strcmp(str.cstr(), "Hello World! It's me Nati."), verbose);
				}
				{
					String str = "Hello World!";
					const String::char_t* app_str = " It's me Nati.";
					str.append(app_str, 8);
					Assertv(str.size() == 21U, verbose);
					Assertv(str.length() == 20U, verbose);
					Assertv(str.cstr() != String::NullCStr, verbose);
					Assertv(str[20] == String::NullChar, verbose);
					Assertv(0 == strcmp(str.cstr(), "Hello World! It's me"), verbose);
				}
				{
					String str = "Hello World!";
					const String::char_t* app_str = " It's me Nati.";
					str.append(app_str, 5, 9);
					Assertv(str.size() == 18U, verbose);
					Assertv(str.length() == 17U, verbose);
					Assertv(str.cstr() != String::NullCStr, verbose);
					Assertv(str[17] == String::NullChar, verbose);
					Assertv(0 == strcmp(str.cstr(), "Hello World!Nati."), verbose);
				}
			}
		}
		{ // Substring
			const String str = "Hello World!";
			Assertv(str.size() == 13U, verbose);
			Assertv(str.length() == 12U, verbose);
			Assertv(str.cstr() != String::NullCStr, verbose);
			Assertv(str[12] == String::NullChar, verbose);
			Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
			{
				const String sub_str = str.substring(5);
				Assertv(sub_str.size() == 6U, verbose);
				Assertv(sub_str.length() == 5U, verbose);
				Assertv(sub_str.cstr() != String::NullCStr, verbose);
				Assertv(sub_str[5] == String::NullChar, verbose);
				Assertv(0 == strcmp(sub_str.cstr(), "Hello"), verbose);
			}
			{
				const String sub_str = str.substring(6, 6);
				Assertv(sub_str.size() == 7U, verbose);
				Assertv(sub_str.length() == 6U, verbose);
				Assertv(sub_str.cstr() != String::NullCStr, verbose);
				Assertv(sub_str[6] == String::NullChar, verbose);
				Assertv(0 == strcmp(sub_str.cstr(), "World!"), verbose);
			}
		}
		{ // Reverse
			const String str = "Hello World!";
			Assertv(str.size() == 13U, verbose);
			Assertv(str.length() == 12U, verbose);
			Assertv(str.cstr() != String::NullCStr, verbose);
			Assertv(str[12] == String::NullChar, verbose);
			Assertv(0 == strcmp(str.cstr(), "Hello World!"), verbose);
			const String rev_str = str.reverse();
			Assertv(rev_str.size() == 13U, verbose);
			Assertv(rev_str.length() == 12U, verbose);
			Assertv(rev_str.cstr() != String::NullCStr, verbose);
			Assertv(rev_str[12] == String::NullChar, verbose);
			Assertv(0 == strcmp(rev_str.cstr(), "!dlroW olleH"), verbose);
		}
		{ // ToUpper
			const String str = "Hello World! 1234@#$%";
			Assertv(str.size() == 22U, verbose);
			Assertv(str.length() == 21U, verbose);
			Assertv(str.cstr() != String::NullCStr, verbose);
			Assertv(str[21] == String::NullChar, verbose);
			Assertv(0 == strcmp(str.cstr(), "Hello World! 1234@#$%"), verbose);
			const String upper_str = str.toUpper();
			Assertv(upper_str.size() == 22U, verbose);
			Assertv(upper_str.length() == 21U, verbose);
			Assertv(upper_str.cstr() != String::NullCStr, verbose);
			Assertv(upper_str[21] == String::NullChar, verbose);
			Assertv(0 == strcmp(upper_str.cstr(), "HELLO WORLD! 1234@#$%"), verbose);
		}
		{ // ToLower
			const String str = "HeLLo WoRLD! 1234@#$%";
			Assertv(str.size() == 22U, verbose);
			Assertv(str.length() == 21U, verbose);
			Assertv(str.cstr() != String::NullCStr, verbose);
			Assertv(str[21] == String::NullChar, verbose);
			Assertv(0 == strcmp(str.cstr(), "HeLLo WoRLD! 1234@#$%"), verbose);
			const String lower_str = str.toLower();
			Assertv(lower_str.size() == 22U, verbose);
			Assertv(lower_str.length() == 21U, verbose);
			Assertv(lower_str.cstr() != String::NullCStr, verbose);
			Assertv(lower_str[21] == String::NullChar, verbose);
			Assertv(0 == strcmp(lower_str.cstr(), "hello world! 1234@#$%"), verbose);
		}
		{ // format
			{
				String str(18);
				Assertv(str.format("Doom%s %d", "Ethernal", 3) == "DoomEthernal 3", verbose);
			}
			{
				String str(15);
				Assertv(str.format("Doom%s %d", "Ethernal", 3) == "DoomEthernal 3", verbose);
			}
			{
				String str(35);
				Assertv(str.format("Temperature: %.1f, %.1lf", 24.5f, 72.66f) == "Temperature: 24.5, 72.7", verbose);
			}
		}
	}
	if(assert::_num_failed_tests > 0) puts("----------------------------------------");
	printf("# %d Failed!\n", assert::_num_failed_tests);
	return assert::_num_failed_tests;
}