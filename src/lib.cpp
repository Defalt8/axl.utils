#include <axl.util/lib.hpp>

namespace axl {
namespace util {
namespace lib {


const Version VERSION = { AXLUTIL_VERSION_MAJOR, AXLUTIL_VERSION_MINOR, AXLUTIL_VERSION_PATCH };

#if defined(AXLUTIL_SHARED)
const Build BUILD = Build::SHARED;
#elif defined(AXLUTIL_STATIC)
const Build BUILD = Build::STATIC;
#endif


} // namespace axl.util.lib	
} // namespace axl.util	
} // namespace axl
