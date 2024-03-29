#ifndef _FT_PAIR_H
# define _FT_PAIR_H

#include <deque>

namespace ft
{
	template<typename _T1, typename _T2>
	class pair
	{
	public:
		typedef ft::pair<_T1, _T2> self;
		typedef _T1 first_type;    ///< The type of the `first` member
		typedef _T2 second_type;   ///< The type of the `second` member

		_T1 first;                 ///< The first member
		_T2 second;                ///< The second member

		pair() : first(_T1()), second(_T2()) { }

		pair(const _T1& __a, const _T2& __b)
		: first(__a), second(__b) { }

		template<typename _U1, typename _U2>
		pair(const pair<_U1, _U2>& __p)
		: first(__p.first), second(__p.second) { }
		
		template<typename _U1, typename _U2>
		pair(const std::pair<_U1, _U2>& __p)
		: first(__p.first), second(__p.second) { }

		~pair() { }
		// ~pair() { std::cout << "pair destructor" << std::endl; }

		self&	operator=(const self& pr)
		{
			if (*this == pr)
				return (*this);
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}

		template<class U, class V>
		ft::pair<U, V>&	operator=(const std::pair<U, V>& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}

		// template<class U, class V>
		// operator pair<U, V>() const
		// {
		// 	return (const_cast<pair< U, V> >(first, second));
		// }

		// template<class U, class V>
		// operator pair<const U, const V>() const
		// {
		// 	return (const_cast<pair<const U, const V> >(first, second));
		// }

		// template<class U, class V>
		// operator pair<const U, V>() const
		// {
		// 	return (const_cast<pair<const U, V> >(first, second));
		// }


		// template<class U, class V>
		// operator pair<U, const V>() const
		// {
		// 	return (const_cast<pair<U, const V> >(first, second));
		// }
	};

	template<typename _T1, typename _T2>
	inline bool	operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{ return __x.first == __y.first && __x.second == __y.second; }

	template<typename _T1, typename _T2>
	inline bool
	operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{ return __x.first < __y.first
		|| (!(__y.first < __x.first) && __x.second < __y.second); }

	template<typename _T1, typename _T2>
	inline bool
	operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{ return !(__x == __y); }

	template<typename _T1, typename _T2>
	inline bool
	operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{ return __y < __x; }

	template<typename _T1, typename _T2>
	inline bool
	operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{ return !(__y < __x); }

	template<typename _T1, typename _T2>
	inline bool
	operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{ return !(__x < __y); }

	template<typename _T1, typename _T2>
	inline pair<_T1, _T2>	make_pair(_T1 __x, _T2 __y)
	{ return pair<_T1, _T2>(__x, __y); }

	// template<typename _Arg, typename _Result>
	// struct unary_function
	// {
	// 	typedef _Arg 	argument_type;   
	// 	typedef _Result 	result_type;  
	// };

	template<typename _Pair>
	struct _Select1st
	//: public unary_function<_Pair, typename _Pair::first_type>
	{
		typename _Pair::first_type&
		operator()(_Pair& __x) const
		{ return __x.first; }

		const typename _Pair::first_type&
		operator()(const _Pair& __x) const
		{ return __x.first; }
	};

	template<typename _Pair>
	struct _Select2nd
	//: public unary_function<_Pair, typename _Pair::second_type>
	{
		typename _Pair::second_type&
		operator()(_Pair& __x) const
		{ return __x.second; }

		const typename _Pair::second_type&
		operator()(const _Pair& __x) const
		{ return __x.second; }
	};
} // namespace ft

#endif /* _FT_PAIR_H */
