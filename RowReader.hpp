#pragma once

#include <iostream>

#include "remove_method_pointer.hpp"
#include "is_function.hpp"
#include "is_functional.hpp"

#include "tuple_call.hpp"

/*template <unsigned int N, typename... Args>
struct fill_tuple
{
	template <typename Head, typename... Rest>
	static void _fill(unsigned int size, std::tuple<Args...>& tuple)
	{
		std::cout << size - N << std::endl;
		//fill_tuple<N-1, Rest...>::_fill<Rest...>(size, tuple);
	}
};

template <typename... Args>
struct fill_tuple<1, Args...>
{
	template <typename Head>
	static void _fill(unsigned int size, std::tuple<Args...>& tuple)
	{
		std::cout << size << std::endl;
	}
};*/

template <unsigned int N, typename... Args>
struct fill_tuple;

template <unsigned int N, typename Head, typename... Rest>
struct fill_tuple<N, Head, Rest...>
{
	template <typename... Tuple>
	static void _fill(unsigned int size, std::tuple<Tuple...>& tuple)
	{
		std::cout << size - N << std::endl;
		fill_tuple<N-1, Rest...>::_fill(size, tuple);
	}
};

template <typename Head, typename... Rest>
struct fill_tuple<1, Head, Rest...>
{
	template <typename... Tuple>
	static void _fill(unsigned int size, std::tuple<Tuple...>& tuple)
	{
		std::cout << size << std::endl;
	}
};



template <typename R, typename... Args>
struct _RowReader
{
	template <typename Callback>
	static void Read(Callback callback)
	{
		std::tuple<Args...> tuple;

		fill_tuple<sizeof...(Args), Args...>::_fill(sizeof...(Args), tuple);

		tuple_call::Call(callback, tuple);
	}
};

template <typename R>
struct _RowReader<R>
{
	template <typename Callback>
	static void Read(Callback callback)
	{
		tuple_call::Call(callback, std::tuple<>());
	}
};

template <typename Signature>
struct RowReader;

template <typename R, typename... Args>
struct RowReader<R (Args...)>
{
	template <typename Callback>
	static void Read(Callback callback)
	{
		_RowReader<R, Args...>::Read(callback);
	}
};

template <typename R, typename... Args>
struct RowReader<R (*)(Args...)>
{
	template <typename Callback>
	static void Read(Callback callback)
	{
		_RowReader<R, Args...>::Read(callback);
	}
};