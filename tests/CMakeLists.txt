
add_compile_definitions( AXLUTIL_SOURCE_DIR="${PROJECT_SOURCE_DIR}" )
link_libraries( axl.util )

add_executable( "axl.util.lib" "lib.cpp" )
add_executable( "axl.util.string" "String.cpp" )
add_executable( "axl.util.wstring" "WString.cpp" )
add_executable( "axl.util.file" "File.cpp" )
add_executable( "axl.util.directory" "Directory.cpp" )
add_executable( "axl.util.array" "ds/Array.cpp" )
add_executable( "axl.util.list" "ds/List.cpp" )
add_executable( "axl.util.map" "ds/Map.cpp" )
add_executable( "axl.util.node" "ds/Node.cpp" )
add_executable( "axl.util.serial" "Serial.cpp" )

set_target_properties(
	"axl.util.lib"
	"axl.util.string"
	"axl.util.wstring"
	"axl.util.file"
	"axl.util.directory"
	"axl.util.array"
	"axl.util.list"
	"axl.util.map"
	"axl.util.node"
	"axl.util.serial"
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${AXLUTIL_RUNTIME_DIR}"
)

target_compile_definitions( axl.util.directory
	PRIVATE AXLUTIL_TEST_DIR=L"${PROJECT_SOURCE_DIR}/tests"
)
