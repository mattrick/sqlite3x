project (sqlite3x)
cmake_minimum_required (VERSION 2.6)

# C++ sets
set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -fPIC")
#

# CMake sets
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${sqlite3x_SOURCE_DIR}/cmake/Modules/)
#

# Sqlite3
find_package (Sqlite3 REQUIRED)
#

# Compile options
option (BUILD_EXAMPLES "Build examples" ON)
#

include_directories (${sqlite3x_SOURCE_DIR}/include)

file (GLOB sqlite3x_SOURCES "src/*.cpp")

add_library (sqlite3x STATIC ${sqlite3x_SOURCES})

target_link_libraries (sqlite3x sqlite3 dl pthread)

# Examples
if (BUILD_EXAMPLES)
	add_subdirectory (examples)
endif (BUILD_EXAMPLES)
#