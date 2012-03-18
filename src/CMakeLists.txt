include_directories(${sqlite3x_SOURCE_DIR}/include)
set(LIBRARY_OUTPUT_PATH ${sqlite3x_SOURCE_DIR}/lib)

add_library(sqlite3x STATIC DB.cpp Cell.cpp Query.cpp)

target_link_libraries(sqlite3x sqlite3 dl pthread)