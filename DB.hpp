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

		void Exec(std::string query);

		template <typename... Args>
		SQLite3x::Query* Query(const char* fmt, Args... args);
};

template <typename... Args>
SQLite3x::Query* DB::Query(const char* fmt, Args... args)
{
	char buffer[1024];

	sprintf(buffer, fmt, args...);

	return new SQLite3x::Query(buffer, m_DB);
}

}