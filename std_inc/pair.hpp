#ifndef _FT_PAIR_H
# define _FT_PAIR_H

namespace ft
{
	template<typename _T1, typename _T2>
	struct pair
	{
		typedef _T1 first_type;    ///< The type of the `first` member
		typedef _T2 second_type;   ///< The type of the `second` member

		_T1 first;                 ///< The first member
		_T2 second;                ///< The second member

		pair() : first(), second() { }

		pair(const _T1& __a, const _T2& __b)
		: first(__a), second(__b) { }

		template<typename _U1, typename _U2>
		pair(const pair<_U1, _U2>& __p)
		: first(__p.first), second(__p.second) { }
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
