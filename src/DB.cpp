#include <sqlite3.h>

#include "DB.hpp"
#include "Query.hpp"

namespace SQLite3x
{

DB::DB(std::string filename)
{
	if (sqlite3_open(filename.c_str(), &m_DB))
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_DB));
		sqlite3_close(m_DB);
	}
}

DB::DB()
{
	if (sqlite3_open("sqlite.db", &m_DB))
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_DB));
		sqlite3_close(m_DB);
	}
}

DB::~DB()
{
	sqlite3_close(m_DB);
}

}