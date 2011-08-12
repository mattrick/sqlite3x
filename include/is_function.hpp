#pragma once

#include <type_traits>

namespace SQLite3x
{
	namespace type_traits
	{

template <class T>
struct is_function
{
	typedef typename std::remove_pointer<T>::type type;

	static const bool value = std::is_function<type>::value;
};

	}
}