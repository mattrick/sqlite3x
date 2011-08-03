#pragma once

#include <sqlite3.h>
#include <iostream>

#include "Cell.hpp"

#include "RowExecuter.hpp"

class Result;

class Query
{
	private:

	protected:
		sqlite3* m_DB;
		std::string m_Query;
		sqlite3_stmt* m_SQL;

	public:
		Query(std::string query, sqlite3* db)
			: m_Query(query), m_DB(db)
		{
			if (sqlite3_prepare_v2(m_DB, m_Query.c_str(), m_Query.size() * sizeof(std::string::value_type), &m_SQL, nullptr) != SQLITE_OK)
				std::cout << sqlite3_errmsg(m_DB);
		}

		template <typename... Args>
		Query* Bind(Args... args)
		{
			return _bind<sizeof...(args) - 1>(sizeof...(args), args...);
		}

		template <unsigned int N, typename Head, typename... Args>
		Query* _bind(int size, Head head, Args... args)
		{
			Cell::_bind(m_SQL, size - N, head);
			return _bind<N - 1>(size, args...);
		}

		template <unsigned int N, typename Head>
		Query* _bind(int size, Head head)
		{
			Cell::_bind(m_SQL, size, head);
			return this;
		}

		template <typename Object>
			typename std::enable_if<is_function<Object>::value>::type
		Execute(Object&& o)
		{
			typedef Object Type;

			_Execute<Type, Object>(o);
		}

		template <typename Object>
			typename std::enable_if<is_functional<Object>::value>::type
		Execute(Object&& o)
		{
			typedef typename remove_method_pointer<decltype(&Object::operator())>::type Type;

			_Execute<Type, Object>(o);
		}
			
		void Execute()
		{
			Execute([](){});
		}

		template <typename Type, typename Object>
		void _Execute(Object& o)
		{
			int result = 0;

			while ((result = sqlite3_step(m_SQL)) == SQLITE_ROW)
			{
				RowExecuter<Type>::Read(m_SQL, o);
			}

			if (result != SQLITE_DONE)
				throw "error";
		}

		/*Result* _Result()
		{
			int result = 0;

			while ((result = sqlite3_step(m_SQL)) == SQLITE_ROW)
			{
				//RowReader::Read(m_SQL);
			}

			if (result != SQLITE_DONE)
				throw "error";
		}*/

		~Query()
		{
			sqlite3_finalize(m_SQL);
		}
};

/*
TODO:
Result():

easily for-eachable and accessible both by col and name, i. e.:

for each (auto row in sql->Result())
//or g++
//for (auto row: sql->Result())
{
	row->Get<std::string>(0);
	row->Get<int>("ID");
}
*/