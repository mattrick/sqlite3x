#pragma once

#include <string>
#include <cstdio>
#include <cstdarg>

#include "Query.hpp"

class sqlite3;

namespace SQLite3x
{

class DB
{
	private:

	protected:
		sqlite3* m_DB;

	public:
		DB(std::string filename);
		DB();

		~DB();

		template <typename... Args>
		void Exec(const char* fmt, Args... args);

		template <typename... Args>
		SQLite3x::Query* Query(const char* fmt, Args... args);
};

template <typename... Args>
void DB::Exec(const char* fmt, Args... args)
{
	char* error = nullptr;

	char buffer[1024];

	sprintf(buffer, fmt, args...);

	if (sqlite3_exec(m_DB, buffer, nullptr, 0, &error) != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", error);
		sqlite3_free(error);
	}
}

template <typename... Args>
SQLite3x::Query* DB::Query(const char* fmt, Args... args)
{
	char buffer[1024];

	sprintf(buffer, fmt, args...);

	return new SQLite3x::Query(buffer, m_DB);
}

}