#pragma once

namespace SQLite3x
{
	namespace type_traits
	{

template <typename T>
struct is_string
{
    enum { value = false };
};

template <typename charT, typename traits, typename Alloc>
struct is_string<std::basic_string<charT, traits, Alloc> >
{
    enum { value = true };
};

	}
}