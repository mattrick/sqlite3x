#pragma once

#include <string>
#include <type_traits>
#include <cstdio>
#include <cstdlib>
#include <memory.h>

#include <sqlite3.h>

#include "is_string.hpp"

using SQLite3x::type_traits::is_string;

namespace SQLite3x
{

class Cell
{
	private:

	protected:

	public:
		template <typename Integral>
		static typename std::enable_if<std::is_integral<Integral>::value>::type
			_bind(sqlite3_stmt* sql, int col, Integral value);
		
		template <typename FloatingPoint>
		static typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type
			_bind(sqlite3_stmt* sql, int col, FloatingPoint value);

		template <typename Blob>
		static typename std::enable_if<std::is_same<Blob, void*>::value>::type
			_bind(sqlite3_stmt* sql, int col, Blob value, int size);

		static void
			_bind(sqlite3_stmt* sql, int col, std::string value);


		template <typename Integral>
		static typename std::enable_if<std::is_integral<Integral>::value, Integral>::type
			_read(sqlite3_stmt* sql, int col);

		template<typename FloatingPoint>
		static typename std::enable_if<std::is_floating_point<FloatingPoint>::value, FloatingPoint>::type
			_read(sqlite3_stmt* sql, int col);

		template <typename String>
		static typename std::enable_if<is_string<String>::value, String>::type
			_read(sqlite3_stmt* sql, int col);

		/*static std::string _read(sqlite3_stmt* sql, int col, std::string* value = nullptr)
		{
			if (value != nullptr)
			{
				*value = (const char*)sqlite3_column_text(sql, col);
				return *value;
			}
			else
				return (const char*)sqlite3_column_text(sql, col);
		}*/
};

template <typename Integral>
typename std::enable_if<std::is_integral<Integral>::value>::type
	Cell::_bind(sqlite3_stmt* sql, int col, Integral value)
{
	sqlite3_bind_int(sql, col, value);
}
		
template <typename FloatingPoint>
typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type
	Cell::_bind(sqlite3_stmt* sql, int col, FloatingPoint value)
{
	sqlite3_bind_double(sql, col, value);
}

template <typename Blob>
typename std::enable_if<std::is_same<Blob, void*>::value>::type
	Cell::_bind(sqlite3_stmt* sql, int col, Blob value, int size)
{
	void* memory = malloc(size);
	memcpy(memory, value, size);
	sqlite3_bind_blob(sql, col, memory, size, free);
}

template <typename Integral>
typename std::enable_if<std::is_integral<Integral>::value, Integral>::type
	Cell::_read(sqlite3_stmt* sql, int col)
{
	return sqlite3_column_int(sql, col);
}

template<typename FloatingPoint>
typename std::enable_if<std::is_floating_point<FloatingPoint>::value, FloatingPoint>::type
	Cell::_read(sqlite3_stmt* sql, int col)
{
	return sqlite3_column_double(sql, col);
}

template <typename String>
typename std::enable_if<is_string<String>::value, String>::type
	Cell::_read(sqlite3_stmt* sql, int col)
{
	return (const char*)sqlite3_column_text(sql, col);
}

}

/*
template<typename Integral>
static typename std::enable_if<std::is_integral<Integral>::value>::type
	_bind(sqlite3_stmt* sql, int col, Integral value)
{
	sqlite3_bind_int(sql, col, value);
}
		
template<typename FloatingPoint>
static typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type
	_bind(sqlite3_stmt* sql, int col, FloatingPoint value)
{
	sqlite3_bind_double(sql, col, value);
};

template<typename Blob>
static typename std::enable_if<std::is_same<Blob, void*>::value>::type
	_bind(sqlite3_stmt* sql, int col, Blob value, int size)
{
	void* memory = malloc(size);
	memcpy(memory, value, size);
	sqlite3_bind_blob(sql, col, memory, size, free);
}

static void _bind(sqlite3_stmt* sql, int col, std::string value)
{
	char* memory = static_cast<char*>(malloc(value.size() + 1));
	memcpy(memory, value.c_str(), value.size() + 1);
	sqlite3_bind_text(sql, col, memory, value.size(), free);
}
*/