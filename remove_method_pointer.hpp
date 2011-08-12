#pragma once

namespace SQLite3x
{
	namespace utilities
	{

template <typename Method>
struct remove_method_pointer;

template <typename R, typename C, typename... Args>
struct remove_method_pointer<R (C::*)(Args...)>
{
	typedef R (type)(Args...);
};

template <typename R, typename C, typename... Args>
struct remove_method_pointer<R (C::*)(Args...) const>
{
	typedef R (type)(Args...);
};

	}
}