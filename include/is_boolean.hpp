#pragma once

namespace SQLite3x
{
	namespace type_traits
	{

template <typename T>
struct is_boolean
{
    enum { value = false };
};

template <>
struct is_boolean<bool>
{
    enum { value = true };
};

	}
}
