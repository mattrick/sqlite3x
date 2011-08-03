#pragma once

#include <string>
#include <type_traits>
#include <cstdio>
#include <cstdlib>
#include <memory.h>

#include <sqlite3.h>

#include "is_string.hpp"

class Cell
{
	private:

	protected:

	public:
		template <typename Integral>
		static typename std::enable_if<std::is_integral<Integral>::value>::type
			_bind(sqlite3_stmt* sql, int col, Integral value)
		{
			sqlite3_bind_int(sql, col, value);
		}
		
		template <typename FloatingPoint>
		static typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type
			_bind(sqlite3_stmt* sql, int col, FloatingPoint value)
		{
			sqlite3_bind_double(sql, col, value);
		};

		template <typename Blob>
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



		template <typename Integral>
		static typename std::enable_if<std::is_integral<Integral>::value, Integral>::type
			_read(sqlite3_stmt* sql, int col, Integral* value = nullptr)
		{
			if (value != nullptr)
			{
				*value = sqlite3_column_int(sql, col);
				return *value;
			}
			else
				return sqlite3_column_int(sql, col);
		}

		template<typename FloatingPoint>
		static typename std::enable_if<std::is_floating_point<FloatingPoint>::value, FloatingPoint>::type
			_read(sqlite3_stmt* sql, int col, FloatingPoint* value = nullptr)
		{
			if (value != nullptr)
			{
				*value = sqlite3_column_double(sql, col);
				return *value;
			}
			else
				return sqlite3_column_double(sql, col);
		};

		template <typename String>
		static typename std::enable_if<is_string<String>::value, String>::type
			_read(sqlite3_stmt* sql, int col, String* value = nullptr)
		{
			if (value != nullptr)
			{
				*value = (const char*)sqlite3_column_text(sql, col);
				return *value;
			}
			else
				return (const char*)sqlite3_column_text(sql, col);
		}

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