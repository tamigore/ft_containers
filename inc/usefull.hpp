#ifndef _USEFULL_HPP_
# define _USEFULL_HPP_

# include <iostream>

namespace ft
{
	template <typename T>
	std::string to_string(T obj)
	{
		// Stream used to convert to string
		std::ostringstream s;
		s << obj;
		return (s.str());
	}

	//binary_function https://cplusplus.com/reference/functional/binary_function/?kw=binary_function
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1	first_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};

	template <class T>
	struct less : binary_function<T, T, bool> // less(a, b) a < b
	{
		bool operator() (const T& x, const T& y) const { return (x < y); }
	};

	//enable_if https://en.cppreference.com/w/cpp/types/enable_if
	template< bool B, class T = void > struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };
}

#endif