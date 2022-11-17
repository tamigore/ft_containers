#ifndef _USEFULL_HPP_
# define _USEFULL_HPP_

# include <iostream>

class nullptr_ft
{
	public:
		// For conversion to any type of null non-member pointer.
		template<class T>
		operator T*() const { return (0); }

		// For conversion to any type of null member pointer.
		template<class C, class T>
		operator T C::*() const { return (0); }

	private:
		// It's imposible to get an address of a nullptr.
		void operator&() const;

}	ft_nullptr = {};

namespace ft
{
	// to_string https://en.cppreference.com/w/cpp/string/basic_string/to_string
	// template <typename T>
	// std::string to_string(T obj)
	// {
	// 	// Stream used to convert to string
	// 	std::ostringstream ss;
	// 	ss << obj;
	// 	return (ss.str());
	// }

	// distance https://en.cppreference.com/w/cpp/iterator/distance

	template<class InputIt1, class InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
	
		return (first1 == last1) && (first2 != last2);
	}

	template<class It>
	typename std::iterator_traits<It>::difference_type	do_distance(It first, It last, std::input_iterator_tag)
	{
		typename std::iterator_traits<It>::difference_type result = 0;
		while (first != last)
		{
			++first;
			++result;
		}
		return result;
	}
	
	template<class It>
	typename std::iterator_traits<It>::difference_type  do_distance(It first, It last, std::random_access_iterator_tag)
	{
		return last - first;
	}
	
	template<class It>
	typename std::iterator_traits<It>::difference_type distance(It first, It last)
	{
		return do_distance(first, last,
			typename std::iterator_traits<It>::iterator_category());
	}

	// binary_function https://cplusplus.com/reference/functional/binary_function/?kw=binary_function
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

	// enable_if https://en.cppreference.com/w/cpp/types/enable_if
	template< bool B, class T = void > struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };


	// is_integral https://en.cppreference.com/w/cpp/types/is_integral
	template <bool is_integral, typename T>
	struct is_integral_res
	{
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename>
	struct is_integral_type : public is_integral_res<false, bool> {};

	template <>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};

	template <>
	struct is_integral_type<char> : public is_integral_res<true, char> {};

	template <>
	struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

	template <>
	struct is_integral_type<short int> : public is_integral_res<true, short int> {};
	
	template <>
	struct is_integral_type<int> : public is_integral_res<true, int> {};

	template <>
	struct is_integral_type<long int> : public is_integral_res<true, long int> {};

	template <>
	struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

	template <>
	struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

	template <>
	struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

	template <>
	struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

	template <>
		struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
	
	template <>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	template <typename T>
	struct is_integral : public is_integral_type<T> {};
	// End of is_integral
}

#endif