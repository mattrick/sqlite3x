#pragma once

#ifndef __IS_FUNCTIONAL__
#define __IS_FUNCTIONAL__

template <typename T>
struct is_functional
{
	typedef char yes[1];
	typedef char no[2];

	template <typename C>
	static yes& test(decltype(&C::operator()) *);
 
	template <typename>
	static no& test(...);

	static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

#endif