set( DEBUG_SUFFIX "" )
set( TYPE_SUFFIX "" )

if( "${AXLUTIL_TYPE}" MATCHES "[Ss][Hh][Aa][Rr][Ee][Dd]" OR BUILD_SHARED_LIBS )
	set( AXLUTIL_TYPE SHARED )
else()
	set( AXLUTIL_TYPE STATIC )
	set( TYPE_SUFFIX s )
endif()

if( "${CMAKE_BUILD_TYPE}" MATCHES "[Dd][Ee][Bb][Uu][Gg]" )
	set( DEBUG_SUFFIX d )
endif()

add_library( axl.util ${AXLUTIL_TYPE} ${AXLUTIL_SOURCE_FILES} ${AXLUTIL_HEADER_FILES} )
target_include_directories( axl.util PUBLIC "${AXLUTIL_INCLUDE_DIR}" )
target_compile_definitions( axl.util
	PRIVATE AXLUTIL_BUILD
	PRIVATE AXLUTIL_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PRIVATE AXLUTIL_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PRIVATE AXLUTIL_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)

if( "${AXLUTIL_TYPE}" STREQUAL "SHARED" )
	target_compile_definitions( axl.util PUBLIC AXLUTIL_SHARED )
else()
	target_compile_definitions( axl.util PUBLIC AXLUTIL_STATIC )
endif()

if( "${CMAKE_BUILD_TYPE}" MATCHES "[Dd][Ee][Bb][Uu][Gg]" )
	target_compile_definitions( axl.util PRIVATE DEBUG )
elseif( "${CMAKE_BUILD_TYPE}" MATCHES "[Rr][Ee][Ll]" )
	target_compile_definitions( axl.util PRIVATE NDEBUG )
endif()

set_target_properties( axl.util PROPERTIES
	ARCHIVE_OUTPUT_NAME "axl.util${TYPE_SUFFIX}${DEBUG_SUFFIX}"
	LIBRARY_OUTPUT_NAME "axl.util${TYPE_SUFFIX}${DEBUG_SUFFIX}"
	RUNTIME_OUTPUT_NAME "axl.util${TYPE_SUFFIX}${DEBUG_SUFFIX}"
	ARCHIVE_OUTPUT_DIRECTORY "${AXLUTIL_ARCHIVE_DIR}"
	LIBRARY_OUTPUT_DIRECTORY "${AXLUTIL_LIBRARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${AXLUTIL_RUNTIME_DIR}"
)

install( TARGETS axl.util
	ARCHIVE DESTINATION "lib"
	LIBRARY DESTINATION "bin"
	RUNTIME DESTINATION "bin"
)
