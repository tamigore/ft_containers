#ifndef _PAIR_HPP_
# define _PAIR_HPP_

#include <iostream>

namespace ft
{
	// Pair<x, y> 
	template <class T1, class T2>
	class pair
	{
		public :
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;
			
			pair() : first(first_type()), second(second_type()) {}

			template<class U, class V>
			pair(const ft::pair<U, V> &pr) : first(pr.first), second(pr.second) {}

			template<class U, class V>
			pair(const std::pair<U, V> &pr) : first(pr.first), second(pr.second) {}

			pair(const first_type& a, const second_type& b) : first(a), second(b) {}

			pair&	operator=(const pair& pr)
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

			template<class U, class V>
			operator pair<U, const V>() const 
			{ return pair<U, const V>(first, second); }
	};
	
	template <class T1, class T2>
	ft::pair<T1, T2>	make_pair(const T1 &x, const T2 &y)
	{
		ft::pair<T1, T2>	pr;
		pr.first = x;
		pr.second = y;
		return (pr);
	}

	template <class T1, class T2>
	std::ostream	&operator<<(std::ostream &os, const ft::pair<T1,T2> &x)
	{
		os << "[" << x.first << "," << x.second << "]";
		return (os);
	}

	template <class T1, class T2>
	bool	operator==(const ft::pair<T1,T2> &x, const ft::pair<T1,T2> &y)
	{ return (x.first == y.first && x.second == y.second); }

	template <class T1, class T2>
	bool	operator==(const ft::pair<T1,T2> &x, const std::pair<T1,T2> &y)
	{ return (x.first == y.first && x.second == y.second); }

	template <class T1, class T2>
	bool	operator!=(const ft::pair<T1,T2> &x, const ft::pair<T1,T2> &y)
	{ return !(x == y); }

	template <class T1, class T2>
	bool	operator!=(const ft::pair<T1,T2> &x, const std::pair<T1,T2> &y)
	{ return !(x == y); }
	
	template <class T1, class T2>
	bool	operator<(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
	{ return (x.first < y.first || (!(y.first < x.first) && x.second < y.second)); }

	template <class T1, class T2>
	bool	operator<(const ft::pair<T1,T2>& x, const std::pair<T1,T2>& y)
	{ return (x.first < y.first || (!(y.first < x.first) && x.second < y.second)); }

	template <class T1, class T2>
	bool	operator>(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
	{ return (x.first > y.first || (!(y.first > x.first) && x.second > y.second)); }

	template <class T1, class T2>
	bool	operator>(const ft::pair<T1,T2>& x, const std::pair<T1,T2>& y)
	{ return (x.first > y.first || (!(y.first > x.first) && x.second > y.second)); }

	template <class T1, class T2>
	bool	operator>=(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
	{ return !(x < y); }

	template <class T1, class T2>
	bool	operator>=(const ft::pair<T1,T2>& x, const std::pair<T1,T2>& y)
	{ return !(x < y); }

	template <class T1, class T2>
	bool	operator<=(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
	{ return !(y > x); }

	template <class T1, class T2>
	bool	operator<=(const ft::pair<T1,T2>& x, const std::pair<T1,T2>& y)
	{ return !(y > x); }
}

#endif