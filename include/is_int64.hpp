#pragma once

#if defined(_MSC_VER) || defined(__BORLANDC__)
  typedef __int64 int64;
  typedef unsigned __int64 int64;
#else
  typedef long long int int64;
  typedef unsigned long long int uint64;
#endif

namespace SQLite3x
{
	namespace type_traits
	{

template <typename T>
struct is_int64
{
    enum { value = false };
};

template <>
struct is_int64<int64>
{
    enum { value = true };
};

	}
}
