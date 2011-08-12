#pragma once

#include <iostream>

#include "../tuple_call.hpp"
#include "../tuple_fill.hpp"

#include "Cell.hpp"

class sqlite3_stmt;

namespace SQLite3x
{

template <typename R, typename... Args>
struct _RowExecuter
{
	template <typename Callback>
	static void Read(sqlite3_stmt* sql, Callback callback)
	{
		std::tuple<Args...> tuple;

		SQLite3x::utilities::tuple_fill<sizeof...(Args), sizeof...(Args), Args...>::_fill(sql, tuple);

		SQLite3x::utilities::tuple_call::Call(callback, tuple);
	}
};

template <typename Signature>
struct RowExecuter;

template <typename R, typename... Args>
struct RowExecuter<R (Args...)>
{
	template <typename Callback>
	static void Read(sqlite3_stmt* sql, Callback callback)
	{
		_RowExecuter<R, Args...>::Read(sql, callback);
	}
};

template <typename R, typename... Args>
struct RowExecuter<R (*)(Args...)>
{
	template <typename Callback>
	static void Read(sqlite3_stmt* sql, Callback callback)
	{
		_RowExecuter<R, Args...>::Read(sql, callback);
	}
};

}