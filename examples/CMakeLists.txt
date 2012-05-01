project (examples)

include_directories (${sqlite3x_SOURCE_DIR}/include)

file (GLOB sub-dir *)
foreach (dir ${sub-dir})
	if (IS_DIRECTORY ${dir})
		add_subdirectory(${dir})
	endif ()
endforeach ()