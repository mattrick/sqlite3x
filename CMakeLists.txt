project (sqlite3x)
cmake_minimum_required (VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x")

add_subdirectory(src)
add_subdirectory(examples)