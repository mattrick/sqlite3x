#pragma once

#ifndef __REMOVE_METHOD_POINTER__
#define __REMOVE_METHOD_POITNER__

template <typename Method>
struct remove_method_pointer;

#ifdef __GNUC__

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

#else

#endif

#endif