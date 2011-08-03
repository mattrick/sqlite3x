#pragma once

#include <iostream>

#include "remove_method_pointer.hpp"
#include "is_function.hpp"
#include "is_functional.hpp"

#include "tuple_call.hpp"
#include "Cell.hpp"


template <unsigned int N, unsigned int Size, typename... Args>
struct fill_tuple;

template <unsigned int N, unsigned int Size, typename Head, typename... Rest>
struct fill_tuple<N, Size, Head, Rest...>
{
	template <typename... Tuple>
	static void _fill(sqlite3_stmt* sql, std::tuple<Tuple...>& tuple)
	{
		std::get<Size - N>(tuple) = Cell::_read<Head>(sql, Size - N);
		fill_tuple<N-1, Size, Rest...>::_fill(sql, tuple);
	}
};

template <unsigned int Size>
struct fill_tuple<0, Size>
{
	template <typename... Tuple>
	static void _fill(sqlite3_stmt* sql, std::tuple<Tuple...>& tuple)
	{

	}
};

template <typename R, typename... Args>
struct _RowReader
{
	template <typename Callback>
	static void Read(sqlite3_stmt* sql, Callback callback)
	{
		std::tuple<Args...> tuple;

		fill_tuple<sizeof...(Args), sizeof...(Args), Args...>::_fill(sql, tuple);

		tuple_call::Call(callback, tuple);
	}
};

template <typename Signature>
struct RowReader;

template <typename R, typename... Args>
struct RowReader<R (Args...)>
{
	template <typename Callback>
	static void Read(sqlite3_stmt* sql, Callback callback)
	{
		_RowReader<R, Args...>::Read(sql, callback);
	}
};

template <typename R, typename... Args>
struct RowReader<R (*)(Args...)>
{
	template <typename Callback>
	static void Read(sqlite3_stmt* sql, Callback callback)
	{
		_RowReader<R, Args...>::Read(sql, callback);
	}
};