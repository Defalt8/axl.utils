#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../Assert.hpp"
#include "../lib.hpp"
#include <axl.util/String.hpp>
#include <axl.util/ds/Map.hpp>
#include <axl.util/uc/Tracer.hpp>

#ifdef AXUTIL_BUILD
#	error("AXUTIL_BUILD defined!")
#endif

axl::util::ds::Map<char, int> genMap0(int count = 6)
{
	axl::util::ds::Map<char, int> map;
	for(int i = 0; i < count; ++i)
		map.add('A'+i, i);
	return map;
}

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u --- [Map] test\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	{
		using namespace axl::util::ds;
		{ // Map<char, int>
			{ // Default constructor
				Map<char, int> map;
				Assertv(map.count() == 0, verbose);
				Assertv(map.isEmpty(), verbose);
			}
			{ // Copy constructor
				Map<char, int> map0;
				for(int i=0; i<=9; ++i)
					Assertv(map0.add('0'+i, i), verbose);
				Assertv(map0.count() == 10, verbose);
				Assertv(!map0.isEmpty(), verbose);
				Map<char, int> map1(map0);
				Assertv(map1.count() == 10, verbose);
				Assertv(!map1.isEmpty(), verbose);
				for(Map<char, int>::Iterator it = map1.first(); it.isNotNull(); ++it)
					Assertv(((int)it.key() - '0') == it.value(), verbose);
			}
			{ // Move constructor
				Map<char, int> map(genMap0(6));
				Assertv(map.count() == 6, verbose);
				Assertv(!map.isEmpty(), verbose);
				for(Map<char, int>::Iterator it = map.first(); it.isNotNull(); ++it)
					Assertv(((int)it.key() - 'A') == it.value(), verbose);
			}
			{ // Assignment operator
				Map<char, int> map;
				map = genMap0(6);
				Assertv(map.count() == 6, verbose);
				Assertv(!map.isEmpty(), verbose);
				for(Map<char, int>::Iterator it = map.first(); it.isNotNull(); ++it)
					Assertv(((int)it.key() - 'A') == it.value(), verbose);
			}
			{ // [] operator
				Map<char, int> map(genMap0(6));
				try
				{
					for(int i=0; i<6; ++i)
						Assertv(map['A'+i] == i, verbose);
				}
				catch(...)
				{
					assert::_assertionFailed(false, "map['A'+i] == i", __FILE__, __LINE__);
				}
				try
				{
					Assertv(map['G'] != 7, verbose);
				}
				catch(const char* str_ex)
				{
					Assertv(axl::util::String::scEquals(str_ex, "Null pointer exception"), verbose);
				}
				catch(...)
				{
					assert::_assertionFailed(false, "map['G'] != 7", __FILE__, __LINE__);
				}
				try
				{
					map['A'] = 22;
					Assertv(map['A'] == 22, verbose);
				}
				catch(...)
				{
					assert::_assertionFailed(false, "map['A'] == 22", __FILE__, __LINE__);
				}
			}
			{ // constant [] operator
				const Map<char, int> map(genMap0(6));
				try
				{
					for(int i=0; i<6; ++i)
						Assertv(map['A'+i] == i, verbose);
				}
				catch(...)
				{
					assert::_assertionFailed(false, "map['A'+i] == i", __FILE__, __LINE__);
				}
				try
				{
					Assertv(map['G'] != 7, verbose);
				}
				catch(const char* str_ex)
				{
					Assertv(axl::util::String::scEquals(str_ex, "Null pointer exception"), verbose);
				}
				catch(...)
				{
					assert::_assertionFailed(false, "map['G'] != 7", __FILE__, __LINE__);
				}
			}
			{ // positionOf
				Map<char, int> map(genMap0(6));
				Assertv(map.positionOf('O').isNull(), verbose);
				Assertv(!map.positionOf('O').isNotNull(), verbose);
				Assertv(map.positionOf('C').isNotNull(), verbose);
				Assertv(!map.positionOf('C').isNull(), verbose);
				Assertv(map.positionOf('C').key() == 'C', verbose);
				Assertv(map.positionOf('C').value() == 2, verbose);
				Assertv(map.positionOf('C').keyIt().isNotNull(), verbose);
				Assertv(map.positionOf('C').valueIt().isNotNull(), verbose);
				Assertv(map.positionOf('C').keyIt().value() == 'C', verbose);
				Assertv(map.positionOf('C').valueIt().value() == 2, verbose);
			}
			{ // at
				Map<char, int> map(genMap0(6));
				for(int i=0; i<6; ++i)
				{
					Assertv(map.at(i).isNotNull(), verbose);
					Assertv(map.at(i).key() == 'A' + i, verbose);
					Assertv(map.at(i).value() == i, verbose);
				}
				Assertv(map.at(7).isNull(), verbose);
				Assertv(map.at(8).isNull(), verbose);
			}
			{ // add
				Map<char, int> map;
				Assertv(map.isEmpty(), verbose);
				Assertv(map.add('G', 69), verbose);
				Assertv(!map.isEmpty(), verbose);
				Assertv(!map.add('G', 72), verbose);
				Assertv(map.count() == 1, verbose);
				Assertv(map['G'] == 69, verbose);
				Assertv(map.add('X', 12), verbose);
				Assertv(map.add('F', 72), verbose);
				Assertv(!map.add('X', 72), verbose);
				Assertv(map.count() == 3, verbose);
				Assertv(map['G'] == 69, verbose);
				Assertv(map['F'] == 72, verbose);
				Assertv(map['X'] == 12, verbose);
				Assertv(!map.isEmpty(), verbose);
			}
			{ // remove
				Map<char, int> map(genMap0(6));
				Assertv(map.count() == 6, verbose);
				Assertv(map.remove('A'), verbose);
				Assertv(map.count() == 5, verbose);
				Assertv(!map.remove('A'), verbose);
				Assertv(map.remove('C'), verbose);
				Assertv(map.count() == 4, verbose);
				Assertv(!map.remove('C'), verbose);
				Assertv(map.remove('F'), verbose);
				Assertv(map.count() == 3, verbose);
				Assertv(!map.remove('F'), verbose);
				Assertv(!map.remove('G'), verbose);
				Assertv(map.count() == 3, verbose);
			}
			{ // removeAt
				Map<char, int> map(genMap0(6));
				Assertv(map.count() == 6, verbose);
				Map<char, int>::Iterator it;
				Assertv((it = map.positionOf('A')).isNotNull(), verbose);
				Assertv(map.removeAt(it), verbose);
				Assertv(map.count() == 5, verbose);
				Assertv((it = map.positionOf('A')).isNull(), verbose);
				Assertv((it = map.positionOf('C')).isNotNull(), verbose);
				Assertv(map.removeAt(it), verbose);
				Assertv(map.count() == 4, verbose);
				Assertv((it = map.positionOf('C')).isNull(), verbose);
				Assertv((it = map.positionOf('F')).isNotNull(), verbose);
				Assertv(map.removeAt(it), verbose);
				Assertv(map.count() == 3, verbose);
				Assertv((it = map.positionOf('F')).isNull(), verbose);
				Assertv((it = map.positionOf('G')).isNull(), verbose);
				Assertv(!map.removeAt(it), verbose);
				Assertv(map.count() == 3, verbose);
			}
			{ // removeAll
				Map<char, int> map(genMap0(6));
				Assertv(map.count() == 6, verbose);
				Assertv(!map.isEmpty(), verbose);
				map.removeAll();
				Assertv(map.count() == 0, verbose);
				Assertv(map.isEmpty(), verbose);
			}
			{ // set
				Map<char, int> map(genMap0(6));
				Assertv(map.set('A', 55), verbose);
				Assertv(map.set('B', 69), verbose);
				Assertv(map.set('D', 199), verbose);
				Assertv(map.set('F', 2), verbose);
				Assertv(map['A'] == 55, verbose);
				Assertv(map['B'] == 69, verbose);
				Assertv(map['D'] == 199, verbose);
				Assertv(map['F'] == 2, verbose);
				Assertv(!map.set('G', 2), verbose);
			}
			{ // get
				Map<char, int> map(genMap0(6));
				int value = -1;
				Assertv(!map.get('A', 0), verbose);
				Assertv(map.get('A', &value), verbose);
				Assertv(value == 0, verbose);
				value = -1;
				Assertv(map.get('D', &value), verbose);
				Assertv(value == 3, verbose);
				value = -1;
				Assertv(map.get('F', &value), verbose);
				Assertv(value == 5, verbose);
			}
			{ // keys and values
				Map<char, int> map(genMap0(6));
				UniList<char>& keys = map.keys();
				UniList<int>& values = map.values();
				Assertv(keys.count() == 6, verbose);
				Assertv(values.count() == 6, verbose);
				int i = 0;
				for(UniList<char>::Iterator it = keys.first(); it.isNotNull(); ++it, ++i)
				{
					Assertv(it.value() == 'A' + i, verbose);
					it.value() = 'J' + i;
				}
				i = 0;
				for(UniList<int>::Iterator it = values.first(); it.isNotNull(); ++it, ++i)
				{
					Assertv(it.value() == i, verbose);
					it.value() = i * 2;
				}
				i = 0;
				for(Map<char,int>::Iterator it = map.first(); it.isNotNull(); ++it, ++i)
				{
					Assertv(it.key() == 'J' + i, verbose);
					Assertv(it.value() == i*2, verbose);
				}
			}
			{ // constant keys and values
				const Map<char, int> map(genMap0(6));
				const UniList<char>& keys = map.keys();
				const UniList<int>& values = map.values();
				Assertv(keys.count() == 6, verbose);
				Assertv(values.count() == 6, verbose);
				int i = 0;
				for(UniList<char>::Iterator it = keys.first(); it.isNotNull(); ++it, ++i)
				{
					Assertv(it.value() == 'A' + i, verbose);
				}
				i = 0;
				for(UniList<int>::Iterator it = values.first(); it.isNotNull(); ++it, ++i)
				{
					Assertv(it.value() == i, verbose);
				}
			}
		}
		
	}
	if(assert::_num_failed_tests > 0 || verbose) puts("----------------------------------------");
	printf("# %d Failed!\n", assert::_num_failed_tests);
	return assert::_num_failed_tests;
}