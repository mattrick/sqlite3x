#include <sqlite3.h>

#include "Query.hpp"

namespace SQLite3x
{

Query::Query(std::string query, sqlite3* db)
	: m_Query(query), m_DB(db)
{
	if (sqlite3_prepare_v2(m_DB, m_Query.c_str(), m_Query.size() * sizeof(std::string::value_type), &m_SQL, nullptr) != SQLITE_OK)
		std::cout << sqlite3_errmsg(m_DB);
}

Query::~Query()
{
	sqlite3_finalize(m_SQL);
}

void Query::Execute()
{
	Execute([](){});
}

}