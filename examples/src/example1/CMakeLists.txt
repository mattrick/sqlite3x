set(EXECUTABLE_OUTPUT_PATH ${examples_SOURCE_DIR}/bin)

add_executable(example1 main.cpp)

target_link_libraries(example1 sqlite3x)