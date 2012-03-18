#include "sqlite3x/Cell.hpp"

namespace SQLite3x
{

void
	Cell::_bind(sqlite3_stmt* sql, int col, std::string value)
{
	char* memory = static_cast<char*>(malloc(value.size() + 1));
	memcpy(memory, value.c_str(), value.size() + 1);
	sqlite3_bind_text(sql, col, memory, value.size(), free);
}

}