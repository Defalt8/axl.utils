#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../Assert.hpp"
#include "../lib.hpp"
#include <axl.util/ds/Node.hpp>

#ifdef AXUTIL_BUILD
#	error("AXUTIL_BUILD defined!")
#endif

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u --- [Node] test\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	{
		using namespace axl::util::ds;
		// UniNode
		{
			{
				typedef int T;
				UniNode<T> uninode;
				Assertv(uninode.value == T(), verbose);
				Assertv(uninode.next == nullptr, verbose);
				uninode = T(5678);
				Assertv(uninode.value == T(5678), verbose);
			}
			{
				typedef int T;
				UniNode<T> uninode[3] = { UniNode<T>(44, &uninode[1]), UniNode<T>(55, &uninode[2]), UniNode<T>(66) };
				Assertv(uninode[0].value == 44, verbose);
				Assertv(uninode[0].next == &uninode[1], verbose);
				Assertv(uninode[1].value == 55, verbose);
				Assertv(uninode[1].next == &uninode[2], verbose);
				Assertv(uninode[2].value == 66, verbose);
				Assertv(uninode[2].next == nullptr, verbose);
			}
		}
		// BiNode
		{
			{
				typedef int T;
				BiNode<T> binode;
				Assertv(binode.value == T(), verbose);
				Assertv(binode.previous == nullptr, verbose);
				Assertv(binode.next == nullptr, verbose);
				binode = T(5678);
				Assertv(binode.value == T(5678), verbose);
			}
			{
				typedef int T;
				BiNode<T> binode[3] = { BiNode<T>(44, nullptr, &binode[1]), BiNode<T>(55, &binode[0], &binode[2]), BiNode<T>(66, &binode[1]) };
				Assertv(binode[0].value == 44, verbose);
				Assertv(binode[0].previous == nullptr, verbose);
				Assertv(binode[0].next == &binode[1], verbose);
				Assertv(binode[1].value == 55, verbose);
				Assertv(binode[1].previous == &binode[0], verbose);
				Assertv(binode[1].next == &binode[2], verbose);
				Assertv(binode[2].value == 66, verbose);
				Assertv(binode[2].previous == &binode[1], verbose);
				Assertv(binode[2].next == nullptr, verbose);
			}
		}
		// PolyNode
		{
			{
				typedef int T;
				PolyNode<T> polynode;
				Assertv(polynode.value == T(), verbose);
				Assertv(polynode.children.count() == 0U, verbose);
				Assertv(polynode.children.array() == nullptr, verbose);
				polynode = T(5678);
				Assertv(polynode.value == T(5678), verbose);
			}
			{
				typedef int T;
				PolyNode<T> polynode[] = {
					PolyNode<T>(11, { &polynode[1], &polynode[2], &polynode[3] }),
					PolyNode<T>(22, { &polynode[4], &polynode[5], &polynode[6] }),
					PolyNode<T>(33),
					PolyNode<T>(44),
					PolyNode<T>(55),
					PolyNode<T>(66),
					PolyNode<T>(77)
				};
				Assertv(polynode[0].value == 11, verbose);
				Assertv(polynode[0].children.count() == 3U, verbose);
				Assertv(polynode[0].children == Array<PolyNode<T>*>({ &polynode[1], &polynode[2], &polynode[3] }), verbose);
				Assertv(polynode[1].value == 22, verbose);
				Assertv(polynode[1].children.count() == 3U, verbose);
				Assertv(polynode[1].children == Array<PolyNode<T>*>({ &polynode[4], &polynode[5], &polynode[6] }), verbose);
				Assertv(polynode[2].value == 33, verbose);
				Assertv(polynode[2].children.count() == 0U, verbose);
				Assertv(polynode[3].value == 44, verbose);
				Assertv(polynode[3].children.count() == 0U, verbose);
				Assertv(polynode[4].value == 55, verbose);
				Assertv(polynode[4].children.count() == 0U, verbose);
				Assertv(polynode[5].value == 66, verbose);
				Assertv(polynode[5].children.count() == 0U, verbose);
				Assertv(polynode[6].value == 77, verbose);
				Assertv(polynode[6].children.count() == 0U, verbose);
				
			}
		}
	}
	if(assert::_num_failed_tests > 0 || verbose) puts("----------------------------------------");
	printf("# %d Failed!\n", assert::_num_failed_tests);
	return assert::_num_failed_tests;
}