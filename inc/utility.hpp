#ifndef _USEFULL_HPP_
# define _USEFULL_HPP_

# include <iostream>

namespace ft
{
	template<typename Alloc, typename = typename Alloc::value_type>
	struct alloc_traits
	{
		typedef typename Alloc::pointer                pointer;
		typedef typename Alloc::const_pointer          const_pointer;
		typedef typename Alloc::value_type             value_type;
		typedef typename Alloc::reference              reference;
		typedef typename Alloc::const_reference        const_reference;
		typedef typename Alloc::size_type              size_type;
		typedef typename Alloc::difference_type        difference_type;

		static pointer	allocate(Alloc& all, size_type size)
		{ return all.allocate(size); }

		template<typename Hint>
		static pointer	allocate(Alloc& all, size_type size, Hint __hint)
		{ return all.allocate(size, __hint); }

		static void deallocate(Alloc& all, pointer ptr, size_type size)
		{ all.deallocate(ptr, size); }

		template<typename _Tp>
		static void construct(Alloc& all, pointer ptr, const _Tp& allrg)
		{ all.construct(ptr, allrg); }

		static void destroy(Alloc& all, pointer ptr)
		{ all.destroy(ptr); }

		static size_type max_size(const Alloc& all)
		{ return all.max_size(); }

		static const Alloc& _S_select_on_copy(const Alloc& all) { return all; }

		static void _S_on_swap(Alloc& all, Alloc& __b)
		{	std::__alloc_swap<Alloc>::_S_do_it(all, __b); }

		template<typename _Tp>
		struct rebind
		{ typedef typename Alloc::template rebind<_Tp>::other other; };
	};

	template<typename T>
	struct Identity
	{
		T&		operator()(T& __x) const
		{ return __x; }

		const T&	operator()(const T& __x) const
		{ return __x; }
	};

	template<class T>
	void	swap(T &x, T &y)
	{
		T	tmp = x;
		x = y;
		y = tmp;
	}

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
			// if (comp(*first2, *first1))
			else
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

	// template <class Arg1, class Arg2, class Result>
	// struct unary_function
	// {
	// 	typedef Arg1	argument_type;
	// 	typedef Result	result_type;
	// };
	
	// // binary_function https://cplusplus.com/reference/functional/binary_function/?kw=binary_function
	// template <class Arg1, class Arg2, class Result>
	// struct binary_function
	// {
	// 	typedef Arg1	first_argument_type;
	// 	typedef Arg2	second_argument_type;
	// 	typedef Result	result_type;
	// };

	template <class T>
	struct less //: binary_function<T, T, bool> // less(a, b) a < b
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