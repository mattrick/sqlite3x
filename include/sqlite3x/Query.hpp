#pragma once

#include <iostream>

#include "is_function.hpp"
#include "is_functional.hpp"
#include "remove_method_pointer.hpp"

#include "Cell.hpp"
#include "RowExecuter.hpp"

class sqlite3;
class sqlite3_stmt;

namespace SQLite3x
{

class Query
{
	private:

	protected:
		sqlite3* m_DB;
		std::string m_Query;
		sqlite3_stmt* m_SQL;

		template <unsigned int N, typename Head, typename... Args>
		Query* _bind(int size, Head head, Args... args);

		template <unsigned int N, typename Head>
		Query* _bind(int size, Head head);

		template <typename Type, typename Object>
		void _execute(Object& o);

	public:
		Query(std::string query, sqlite3* db);
		~Query();

		template <typename... Args>
		Query* Bind(Args... args);

		template <typename Object>
			typename std::enable_if<SQLite3x::type_traits::is_function<Object>::value>::type
		Execute(Object&& o);

		template <typename Object>
			typename std::enable_if<SQLite3x::type_traits::is_functional<Object>::value>::type
		Execute(Object&& o);
			
		void Execute();
};

template <unsigned int N, typename Head, typename... Args>
Query* Query::_bind(int size, Head head, Args... args)
{
	Cell::_bind(m_SQL, size - N, head);
	return _bind<N - 1>(size, args...);
}

template <unsigned int N, typename Head>
Query* Query::_bind(int size, Head head)
{
	Cell::_bind(m_SQL, size, head);
	return this;
}

template <typename Type, typename Object>
void Query::_execute(Object& o)
{
	int result = 0;

	while ((result = sqlite3_step(m_SQL)) == SQLITE_ROW)
	{
		RowExecuter<Type>::Read(m_SQL, o);
	}

	if (result != SQLITE_DONE)
		throw std::string(sqlite3_errmsg(m_DB));
}

template <typename... Args>
Query* Query::Bind(Args... args)
{
	return _bind<sizeof...(args) - 1>(sizeof...(args), args...);
}

template <typename Object>
	typename std::enable_if<SQLite3x::type_traits::is_function<Object>::value>::type
Query::Execute(Object&& o)
{
	typedef Object Type;

	_execute<Type, Object>(o);
}

template <typename Object>
	typename std::enable_if<SQLite3x::type_traits::is_functional<Object>::value>::type
Query::Execute(Object&& o)
{
	typedef typename SQLite3x::utilities::remove_method_pointer<decltype(&Object::operator())>::type Type;

	_execute<Type, Object>(o);
}

}

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
