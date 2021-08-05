#pragma once
#include <axl.util/lib.hpp>

const char* buildType(axl::util::lib::Build type)
{
	switch (type)
	{
		default:
		case axl::util::lib::Build::STATIC: return "Static";
		case axl::util::lib::Build::SHARED: return "Shared";
	}
}
