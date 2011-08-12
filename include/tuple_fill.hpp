#pragma once

#include "sqlite3x/Cell.hpp"

namespace SQLite3x
{
	namespace utilities
	{

template <unsigned int N, unsigned int Size, typename... Args>
struct tuple_fill;

template <unsigned int N, unsigned int Size, typename Head, typename... Rest>
struct tuple_fill<N, Size, Head, Rest...>
{
	template <typename... Tuple>
	static void _fill(sqlite3_stmt* sql, std::tuple<Tuple...>& tuple)
	{
		std::get<Size - N>(tuple) = Cell::_read<Head>(sql, Size - N);
		tuple_fill<N-1, Size, Rest...>::_fill(sql, tuple);
	}
};

template <unsigned int Size>
struct tuple_fill<0, Size>
{
	template <typename... Tuple>
	static void _fill(sqlite3_stmt* sql, std::tuple<Tuple...>& tuple)
	{

	}
};

	}
}