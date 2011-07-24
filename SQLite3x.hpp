#pragma once

#include <sqlite3.h>

#include <string>
#include <cstdio>
#include <cstdarg>

#include "Query.hpp"

class SQLite3x
{
	private:

	protected:
		sqlite3* m_DB;

	public:
		SQLite3x()
		{
			if (sqlite3_open("sqlite.db", &m_DB))
			{
				fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_DB));
				sqlite3_close(m_DB);
			}
		}

		~SQLite3x()
		{
			sqlite3_close(m_DB);
		}

		void Exec(std::string query)
		{
			char* error = nullptr;

			if (sqlite3_exec(m_DB, query.c_str(), nullptr, 0, &error) != SQLITE_OK)
			{
				fprintf(stderr, "SQL error: %s\n", error);
				sqlite3_free(error);
			}
		}

		template <typename... Args>
		Query* _Query(const char* fmt, Args... args)
		{
			char buffer[1024];

			sprintf(buffer, fmt, args...);

			return new Query(buffer, m_DB);
		}
};