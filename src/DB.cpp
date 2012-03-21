#include <sqlite3.h>

#include "sqlite3x/DB.hpp"
#include "sqlite3x/Query.hpp"

namespace SQLite3x
{

DB::DB(std::string filename)
{
	if (sqlite3_open(filename.c_str(), &m_DB))
	{
		std::string error(sqlite3_errmsg(m_DB));
		sqlite3_close(m_DB);

		throw error;
	}
}

DB::DB()
{
	DB("sqlite3.db");
}

DB::~DB()
{
	sqlite3_close(m_DB);
}

}