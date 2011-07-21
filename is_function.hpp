#pragma once

#ifndef __IS_FUNCTION__
#define __IS_FUNCTION__

#include <type_traits>

template <class T>
struct is_function
{
	typedef typename std::remove_pointer<T>::type type;

	static const bool value = std::is_function<type>::value;
};

#endif