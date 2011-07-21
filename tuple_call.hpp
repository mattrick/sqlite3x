#include <tuple>

namespace tuple_call
{
	template <typename Ret, unsigned int N>
	struct _tuplecall_ret
	{
		template <typename Object, typename... TupleArgs, typename... Args>
		static Ret _call(Object object, std::tuple<TupleArgs...> tuple, Args... args)
		{
			return tuple_call::_tuplecall_ret<Ret, N-1>::_call(object, tuple, std::get<N-1>(tuple), std::forward<Args>(args)...);
		}

		template <typename Object, typename... TupleArgs, typename... Args>
		static Ret _callbackwards(Object object, std::tuple<TupleArgs...> tuple, Args... args)
		{
			return tuple_call::_tuplecall_ret<Ret, N-1>::_callbackwards(object, tuple, std::forward<Args>(args)..., std::get<N-1>(tuple));
		}
	};

	template <typename Ret>
	struct _tuplecall_ret<Ret, 0>
	{
		template <typename Object, typename... TupleArgs, typename... Args>
		static Ret _call(Object object, std::tuple<TupleArgs...> tuple, Args... args)
		{
			return object(args...);
		}

		template <typename Object, typename... TupleArgs, typename... Args>
		static Ret _callbackwards(Object object, std::tuple<TupleArgs...> tuple, Args... args)
		{
			return object(args...);
		}
	};

	template <typename Ret, typename Object, typename... TupleArgs>
	Ret Call_ret(Object object, std::tuple<TupleArgs...> tuple)
	{
		return tuple_call::_tuplecall_ret<Ret, sizeof...(TupleArgs)>::_call(object, tuple);
	}

	template <typename Ret, typename Object, typename... TupleArgs>
	Ret CallBackwards_ret(Object object, std::tuple<TupleArgs...> tuple)
	{
		return tuple_call::_tuplecall_ret<Ret, sizeof...(TupleArgs)>::_callbackwards(object, tuple);
	}


	/*
		non returning templates
	*/

	template <unsigned int N>
	struct _tuplecall
	{
		template <typename Object, typename... TupleArgs, typename... Args>
		static void _call(Object object, std::tuple<TupleArgs...> tuple, Args... args)
		{
			tuple_call::_tuplecall<N-1>::_call(object, tuple, std::get<N-1>(tuple), std::forward<Args>(args)...);
		}

		template <typename Object, typename... TupleArgs, typename... Args>
		static void _callbackwards(Object object, std::tuple<TupleArgs...> tuple, Args... args)
		{
			tuple_call::_tuplecall<N-1>::_callbackwards(object, tuple, std::forward<Args>(args)..., std::get<N-1>(tuple));
		}
	};

	template <>
	struct _tuplecall<0>
	{
		template <typename Object, typename... TupleArgs, typename... Args>
		static void _call(Object object, std::tuple<TupleArgs...> tuple, Args... args)
		{
			object(args...);
		}

		template <typename Object, typename... TupleArgs, typename... Args>
		static void _callbackwards(Object object, std::tuple<TupleArgs...> tuple, Args... args)
		{
			object(args...);
		}
	};

	template <typename Object, typename... TupleArgs>
	void Call(Object object, std::tuple<TupleArgs...> tuple)
	{
		tuple_call::_tuplecall<sizeof...(TupleArgs)>::_call(object, tuple);
	}

	template <typename Object, typename... TupleArgs>
	void CallBackwards_ret(Object object, std::tuple<TupleArgs...> tuple)
	{
		tuple_call::_tuplecall<sizeof...(TupleArgs)>::_callbackwards(object, tuple);
	}
}