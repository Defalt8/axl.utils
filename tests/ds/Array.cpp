#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../Assert.hpp"
#include "../lib.hpp"
#include <axl.util/ds/Array.hpp>
#include <axl.util/uc/Tracer.hpp>

#ifdef AXUTIL_BUILD
#	error("AXUTIL_BUILD defined!")
#endif

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u --- [Array] test\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	{
		using namespace axl::util::ds;
		// Malloc
		{
			{
				typedef int T;
				bool b;
				Array<T, Allocators::Malloc<T>> array;
				Assertv(array.count() == 0U, verbose);
				Assertv(array.array() == (T*)0, verbose);
				Assertv((b = array.resize(3)), verbose);
				if(b)
				{
					Assertv(array.count() == 3U, verbose);
					Assertv(array.array() != (T*)0, verbose);
					Assertv(array.set(36), verbose);
					Assertv(array[0] == T(36), verbose);
					Assertv(array[1] == T(36), verbose);
					Assertv(array[2] == T(36), verbose);
				}
			}
			{
				typedef int T;
				Array<T, Allocators::Malloc<T>> array = {1,2,3,4,5};
				Assertv(array.count() == 5U, verbose);
				Assertv(array.array() != (T*)0, verbose);
				Assertv(array[0] == T(1), verbose);
				Assertv(array[1] == T(2), verbose);
				Assertv(array[2] == T(3), verbose);
				Assertv(array[3] == T(4), verbose);
				Assertv(array[4] == T(5), verbose);
			}
		}
		// New
		{
			{
				typedef int T;
				bool b;
				Array<T, Allocators::New<T>> array;
				Assertv(array.count() == 0U, verbose);
				Assertv(array.array() == (T*)0, verbose);
				Assertv((b = array.resize(3)), verbose);
				if(b)
				{
					Assertv(array.count() == 3U, verbose);
					Assertv(array.array() != (T*)0, verbose);
					Assertv(array.set(36), verbose);
					Assertv(array[0] == T(36), verbose);
					Assertv(array[1] == T(36), verbose);
					Assertv(array[2] == T(36), verbose);
				}
			}
			{
				typedef int T;
				Array<T, Allocators::New<T>> array = {1,2,3,4,5};
				Assertv(array.count() == 5U, verbose);
				Assertv(array.array() != (T*)0, verbose);
				Assertv(array[0] == T(1), verbose);
				Assertv(array[1] == T(2), verbose);
				Assertv(array[2] == T(3), verbose);
				Assertv(array[3] == T(4), verbose);
				Assertv(array[4] == T(5), verbose);
			}
			{ // Tracer
				using namespace axl::util::uc;
				typedef Tracer T;
				{
					Assertv(Tracer::Top() == 0, verbose);
					Assertv(Tracer::Active() == 0, verbose);
					Array<T, Allocators::New<T>> array;
					Assertv(Tracer::Top() == 0, verbose);
					Assertv(Tracer::Active() == 0, verbose);
					Tracer::Reset();
					Assertv(Tracer::Top() == 0, verbose);
					Assertv(Tracer::Active() == 0, verbose);
				}
				{
					Tracer::Reset();
					Assertv(Tracer::Top() == 0, verbose);
					Assertv(Tracer::Active() == 0, verbose);
					{
						Array<T, Allocators::New<T>> array = { 1,2,3,4,5 };
						Assertv(Tracer::Top() == 10, verbose);
						Assertv(Tracer::Active() == 5, verbose);
						Assertv(array.count() == 5U, verbose);
						Assertv(array.array() != (T*)0, verbose);
						Assertv(array[0].value == Tracer::value_t(1), verbose);
						Assertv(array[1].value == Tracer::value_t(2), verbose);
						Assertv(array[2].value == Tracer::value_t(3), verbose);
						Assertv(array[3].value == Tracer::value_t(4), verbose);
						Assertv(array[4].value == Tracer::value_t(5), verbose);
					}
					Assertv(Tracer::Top() == 10, verbose);
					Assertv(Tracer::Active() == 0, verbose);
					Tracer::Reset();
				}
				{
					Tracer::Reset();
					Assertv(Tracer::Top() == 0, verbose);
					Assertv(Tracer::Active() == 0, verbose);
					{
						Array<T, Allocators::New<T>> array;
						Assertv(Tracer::Top() == 0, verbose);
						Assertv(Tracer::Active() == 0, verbose);
						array = { 1,2,3,4,5 };
						Assertv(Tracer::Top() == 10, verbose);
						Assertv(Tracer::Active() == 5, verbose);
						Assertv(array.count() == 5U, verbose);
						Assertv(array.array() != (T*)0, verbose);
						Assertv(array[0].value == Tracer::value_t(1), verbose);
						Assertv(array[1].value == Tracer::value_t(2), verbose);
						Assertv(array[2].value == Tracer::value_t(3), verbose);
						Assertv(array[3].value == Tracer::value_t(4), verbose);
						Assertv(array[4].value == Tracer::value_t(5), verbose);
						array.resize(3);
						Assertv(Tracer::Top() == 13, verbose);
						Assertv(Tracer::Active() == 3, verbose);
						Assertv(array.count() == 3U, verbose);
						Assertv(array.array() != (T*)0, verbose);
						Assertv(array[0].value == Tracer::value_t(1), verbose);
						Assertv(array[1].value == Tracer::value_t(2), verbose);
						Assertv(array[2].value == Tracer::value_t(3), verbose);
						array.resize(6);
						Assertv(Tracer::Top() == 19, verbose);
						Assertv(Tracer::Active() == 6, verbose);
						Assertv(array.count() == 6U, verbose);
						Assertv(array.array() != (T*)0, verbose);
						Assertv(array[0].value == Tracer::value_t(1), verbose);
						Assertv(array[1].value == Tracer::value_t(2), verbose);
						Assertv(array[2].value == Tracer::value_t(3), verbose);
						Assertv(array[3].value == Tracer::value_t(), verbose);
						Assertv(array[4].value == Tracer::value_t(), verbose);
						Assertv(array[5].value == Tracer::value_t(), verbose);
						array.resize(2, 36);
						Assertv(Tracer::Top() == 21, verbose);
						Assertv(Tracer::Active() == 2, verbose);
						Assertv(array.count() == 2U, verbose);
						Assertv(array.array() != (T*)0, verbose);
						Assertv(array[0].value == Tracer::value_t(1), verbose);
						Assertv(array[1].value == Tracer::value_t(2), verbose);
						array.resize(5, 36);
						Assertv(Tracer::Top() == 26, verbose);
						Assertv(Tracer::Active() == 5, verbose);
						Assertv(array.count() == 5U, verbose);
						Assertv(array.array() != (T*)0, verbose);
						Assertv(array[0].value == Tracer::value_t(1), verbose);
						Assertv(array[1].value == Tracer::value_t(2), verbose);
						Assertv(array[2].value == Tracer::value_t(36), verbose);
						Assertv(array[3].value == Tracer::value_t(36), verbose);
						Assertv(array[4].value == Tracer::value_t(36), verbose);
					}
					Assertv(Tracer::Top() == 26, verbose);
					Assertv(Tracer::Active() == 0, verbose);
					Tracer::Reset();
				}
			}
		}
	}
	if(assert::_num_failed_tests > 0 || verbose) puts("----------------------------------------");
	printf("# %d Failed!\n", assert::_num_failed_tests);
	return assert::_num_failed_tests;
}