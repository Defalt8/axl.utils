#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../Assert.hpp"
#include "../lib.hpp"
#include <axl.util/ds/List.hpp>
#include <axl.util/uc/Tracer.hpp>
template class axl::util::ds::UniList<axl::util::uc::Tracer>;

#ifdef AXUTIL_BUILD
#	error("AXUTIL_BUILD defined!")
#endif

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u --- [List] test\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	{ // UniList
		using namespace axl::util::ds;
		{
			UniList<int> unilist;
			Assertv(unilist.isEmpty(), verbose);
			Assertv(unilist.insertLast(5), verbose);
			Assertv(!unilist.isEmpty(), verbose);
			Assertv(unilist.insertLast(6), verbose);
			Assertv(!unilist.isEmpty(), verbose);
			Assertv(unilist.insertLast(7), verbose);
			Assertv(!unilist.isEmpty(), verbose);
			Assertv(unilist.removeFirst() == 5, verbose);
			Assertv(!unilist.isEmpty(), verbose);
			Assertv(unilist.removeFirst() == 6, verbose);
			Assertv(!unilist.isEmpty(), verbose);
			Assertv(unilist.removeFirst() == 7, verbose);
			Assertv(unilist.isEmpty(), verbose);
			Assertv(unilist.removeFirst() == 0, verbose);
			Assertv(unilist.isEmpty(), verbose);
		}
		{ // insertFirst
			UniList<int> unilist;
			int i;
			for(i = 1; i <= 5; ++i)
				if(!unilist.insertFirst(i)) break;;
			Assertv(i == 6, verbose);
			Assertv(!unilist.isEmpty(), verbose);
			Assertv(!unilist.first().isNull(), verbose);
			Assertv(!unilist.last().isNull(), verbose);
			int counter = 6;
			for(UniList<int>::Iterator it = unilist.first(); it != unilist.end() || !it.isNull(); ++it)
			{
				Assertv(*it == --counter, verbose);
			}
			counter = 6;
			for(UniList<int>::Iterator it = unilist.first(); it != unilist.end() || !it.isNull(); it++)
			{
				Assertv(*it == --counter, verbose);
			}
		}
		{ // insertLast
			UniList<int> unilist;
			int i;
			for(i = 1; i <= 5; ++i)
				if(!unilist.insertLast(i)) break;;
			Assertv(i == 6, verbose);
			Assertv(!unilist.isEmpty(), verbose);
			Assertv(!unilist.first().isNull(), verbose);
			Assertv(!unilist.last().isNull(), verbose);
			int counter = 0;
			for(UniList<int>::Iterator it = unilist.first(); it != unilist.end() || !it.isNull(); ++it)
			{
				Assertv(*it == ++counter, verbose);
			}
			counter = 0;
			for(UniList<int>::Iterator it = unilist.first(); it != unilist.end() || !it.isNull(); it++)
			{
				Assertv(*it == ++counter, verbose);
			}
		}
		{ // positionOf
			UniList<int> unilist;
			int i;
			for(i = 1; i <= 3; ++i)
				if(!unilist.insertLast(i)) break;;
			Assertv(i == 4, verbose);
			Assertv(!unilist.positionOf(1).isNull(), verbose);
			Assertv(!unilist.positionOf(2).isNull(), verbose);
			Assertv(!unilist.positionOf(3).isNull(), verbose);
			Assertv(unilist.positionOf(4).isNull(), verbose);
			Assertv(unilist.positionOf(0).isNull(), verbose);
		}
		{ // insertAfter
			UniList<int> unilist;
			Assertv(unilist.insertAfter(0), verbose);
			Assertv(unilist.insertLast(2), verbose);
			Assertv(unilist.insertLast(4), verbose);
			Assertv(unilist.insertAfter(1, unilist.first()), verbose);
			Assertv(unilist.insertAfter(3, unilist.positionOf(2)), verbose);
			Assertv(unilist.insertAfter(5, unilist.positionOf(4)), verbose);
			Assertv(unilist.count() == 6, verbose);
			int counter = 0;
			for(UniList<int>::Iterator it = unilist.first(); it != unilist.end(); ++it)
			{
				Assertv(*it == counter++, verbose);
			}
		}
		{ // insertAfterValue
			UniList<int> unilist;
			Assertv(unilist.insertLast(0), verbose);
			Assertv(unilist.insertAfterValue(2, 0), verbose);
			Assertv(unilist.insertAfterValue(3, 2), verbose);
			Assertv(unilist.insertAfterValue(1, 0), verbose);
			Assertv(unilist.insertAfterValue(4, 3), verbose);
			Assertv(unilist.count() == 5, verbose);
			int counter = 0;
			for(UniList<int>::Iterator it = unilist.first(); it != unilist.end(); ++it)
			{
				Assertv(*it == counter++, verbose);
			}
		}
		{ // removeFirst
			UniList<int> unilist;
			int i;
			for(i = 1; i <= 5; ++i)
				if(!unilist.insertLast(i)) break;;
			Assertv(i == 6, verbose);
			int counter = 0;
			while(!unilist.isEmpty())
			{
				Assertv(++counter == unilist.removeFirst(), verbose);
				Assertv(unilist.count() == (5 - counter), verbose);
			}
			Assertv(unilist.count() == 0, verbose);
		}
		{ // removeAt
			UniList<int> unilist;
			int i;
			for(i = 1; i <= 5; ++i)
				if(!unilist.insertLast(i)) break;;
			Assertv(i == 6, verbose);
			UniList<int>::Iterator it = unilist.first();
			it += 3;
			Assertv(unilist.removeAt(it), verbose);
			Assertv(unilist.count() == 4, verbose);
			// Assertv(unilist.count() == counter, verbose);
		}
		{ // remove
			UniList<int> unilist;
			int i;
			for(i = 1; i <= 5; ++i)
				if(!unilist.insertLast(i)) break;;
			Assertv(i == 6, verbose);
			for(i = 1; i <= 5; ++i)
			{
				Assertv(unilist.remove(i), verbose);
				Assertv(unilist.count() == (5 - i), verbose);
			}
		}
		{ // removeAll
			UniList<int> unilist;
			int i;
			for(i = 1; i <= 5; ++i)
				if(!unilist.insertLast(i)) break;;
			Assertv(i == 6, verbose);
			Assertv(!unilist.isEmpty(), verbose);
			unilist.removeAll();
			Assertv(unilist.isEmpty(), verbose);
			Assertv(unilist.first().isNull(), verbose);
			Assertv(unilist.last().isNull(), verbose);
		}
		{ // Tracer
			using namespace axl::util::uc;
			Tracer::Reset();
			Assertv(Tracer::Top() == 0, verbose);
			Assertv(Tracer::Active() == 0, verbose);
			{
				UniList<Tracer> unilist;
				Assertv(Tracer::Top() == 0, verbose);
				Assertv(Tracer::Active() == 0, verbose);
				Assertv(unilist.isEmpty(), verbose);
				Assertv(unilist.first().isNull(), verbose);
				Assertv(unilist.last().isNull(), verbose);
				int i;
				for(i = 1; i <= 5; ++i)
					unilist.insertLast(i);
				Assertv(i == 6, verbose);
				Assertv(Tracer::Top() == 5, verbose);
				Assertv(Tracer::Active() == 5, verbose);
				int counter = 0;
				for(UniList<Tracer>::Iterator it = unilist.first(); it != unilist.end() || !it.isNull(); ++it)
				{
					Assertv(it->value == ++counter, verbose);
				}
			}
			Assertv(Tracer::Top() == 5, verbose);
			Assertv(Tracer::Active() == 0, verbose);
			Tracer::Reset();
		}
		{ // count
			UniList<int> unilist;
			for(int i = 0; i < 5; ++i)
			{
				Assertv(unilist.count() == i, verbose);
				Assertv(unilist.insertLast(i), verbose);
				Assertv(unilist.count() == (i+1), verbose);
				Assertv(!unilist.last().isNull() && *unilist.last() == i, verbose);
			}
		}
	}
	if(assert::_num_failed_tests > 0 || verbose) puts("----------------------------------------");
	printf("# %d Failed!\n", assert::_num_failed_tests);
	return assert::_num_failed_tests;
}