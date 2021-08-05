#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Assert.hpp"
#include "lib.hpp"
#include <axl.util/everything.hpp>

class Person : public axl::util::Serial
{
	public:
		Person(const axl::util::String& p_name = axl::util::String(), axl::util::uint8 p_age = 0, float p_height = 0.0f, float p_weight = 0.0f) :
			axl::util::Serial(),
			name(p_name),
			age(p_age),
			height(p_height),
			weight(p_weight)
		{
			axl::util::Serial::Register(name.str(), 0, name.length()+1, 1);
			axl::util::Serial::Register(&age, 0, sizeof(age), 2);
			axl::util::Serial::Register(&height, 0, sizeof(height), 3);
			axl::util::Serial::Register(&weight, 0, sizeof(weight), 4);
		}
		bool onSerialize(axl::util::SerialObjectInfo& object_info)
		{
			switch(object_info.object_id)
			{
				case 1:
					object_info.mem_ptr = this->name.str();
					object_info.size = this->name.length()+1;
					return true;
				default:
					return true; 
			}
		}
		bool onDeserialize(axl::util::SerialObjectInfo object_info)
		{
			switch(object_info.object_id)
			{
				case 1:
					if(this->name.resize(object_info.size-1))
					{
						return axl::util::Serial::setSize(1, object_info.size);
					}
					return false;
				default:
					return true; 
			}
		}
	public:
		axl::util::String name;
		axl::util::uint8 age;
		float height;
		float weight;
};

int main(int argc, char *argv[])
{
	bool verbose = argc > 1 && (0 == strcmp(argv[1], "-v") || 0 == strcmp(argv[1], "--verbose"));
	using namespace axl;
	using namespace axl::util;
	printf("axl.util %s library - version %u.%u.%u --- [Serial] test\n", buildType(lib::BUILD), lib::VERSION.major, lib::VERSION.minor, lib::VERSION.patch);
	puts("----------------------------------------");
	{
		axl::util::protocol::V0 protocol;
		Person person("Axel Eshetu", 23, 1.83f, 52.2f);
		{
			using namespace axl::util;
			Assertv(person.name == "Axel Eshetu", verbose);
			Assertv(person.age == 23, verbose);
			Assertv(person.height == 1.83f, verbose);
			Assertv(person.weight == 52.2f, verbose);
		}
		axl::util::ds::Array<axl::util::byte, axl::util::ds::Allocators::Malloc<axl::util::byte>> data = protocol.serialize(person);
		{
			Person p;
			protocol.deserialize(p, data);
			{
				using namespace axl::util;
				Assertv(person.name == "Axel Eshetu", verbose);
				Assertv(p.age == 23, verbose);
				Assertv(p.height == 1.83f, verbose);
				Assertv(p.weight == 52.2f, verbose);
			}
		}
		int x = 0;
	}
	if(axl::assert::_num_failed_tests > 0 || verbose) puts("----------------------------------------");
	printf("# %d Failed!\n", axl::assert::_num_failed_tests);
	return axl::assert::_num_failed_tests;
}