cmake_minimum_required( VERSION 3.10 )

project( axl.util VERSION 1.8.19 DESCRIPTION "A simple C++ utilities library." )

if( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}" )
	set( AXLUTIL_STANDALONE TRUE )
else()
	set( AXLUTIL_STANDALONE FALSE )
endif()

set( CMAKE_CXX_STANDARD 11 CACHE STRING "C++ compiler standard.")
set( CMAKE_CXX_STANDARD_REQUIRED TRUE CACHE BOOL "" )
set( CMAKE_BUILD_TYPE Debug CACHE STRING "Build configuration type: ${CMAKE_CONFIGURATION_TYPES}." )
set( AXLUTIL_TYPE STATIC CACHE STRING "Library type." )
set( AXLUTIL_RUNTIME_DIR "${PROJECT_BINARY_DIR}/bin" CACHE PATH "Binary output directory path." )
set( AXLUTIL_LIBRARY_DIR "${PROJECT_BINARY_DIR}/bin" CACHE PATH "Library output directory path." )
set( AXLUTIL_ARCHIVE_DIR "${PROJECT_BINARY_DIR}/lib" CACHE PATH "Archive library output directory path." )
set( AXLUTIL_INSTALL_HEADERS ${AXLUTIL_STANDALONE} CACHE BOOL "" )
set( AXLUTIL_BUILD_TESTS ${AXLUTIL_STANDALONE} CACHE BOOL "" )
set( AXLUTIL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" )
set( AXLUTIL_SOURCE_FILES
	"lib.cpp"
	"String.cpp"
	"WString.cpp"
	"Directory.cpp"
	"File.cpp"
	"Random.cpp"
	"Serial.cpp"
	"Protocol.cpp"
	"protocols/V0.cpp"
	"utils.cpp"
	"uc/Clock.cpp"
	"uc/Time.cpp"
	"uc/Tracer.cpp"
	"uc/Object.cpp"
	"uc/Child.cpp"
	"uc/Parent.cpp"
)
set( AXLUTIL_HEADER_FILES
	"${AXLUTIL_INCLUDE_DIR}/axl.util/everything.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/lib.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/types.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/String.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/WString.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/File.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/Directory.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/Random.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/Serial.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/Protocol.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/protocols/V0.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/utils.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/allocators.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/Array.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/Node.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/List.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/Map.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Tracer.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Clock.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Time.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Object.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Child.hpp"
	"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Parent.hpp"
)

add_subdirectory( src "axl.util" )
if( AXLUTIL_BUILD_TESTS )
	add_subdirectory( tests "axl.util.tests" )
endif()

if( AXLUTIL_INSTALL_HEADERS )
	install( FILES 
		"${AXLUTIL_INCLUDE_DIR}/axl.util/everything.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/lib.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/types.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/String.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/WString.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/File.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/Random.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/Serial.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/Protocol.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/utils.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/allocators.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/allocators.inl"
		DESTINATION "include/axl.util"
	)
	install( FILES
		"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/Array.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/Array.inl"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/Node.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/Node.inl"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/List.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/ds/List.inl"
		DESTINATION "include/axl.util/ds"
	)
	install( FILES
		"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Clock.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Time.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Tracer.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Object.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Child.hpp"
		"${AXLUTIL_INCLUDE_DIR}/axl.util/uc/Parent.hpp"
		DESTINATION "include/axl.util/uc"
	)
	install( FILES
		"${AXLUTIL_INCLUDE_DIR}/axl.util/protocols/V0.hpp"
		DESTINATION "include/axl.util/protocols"
	)
endif()
