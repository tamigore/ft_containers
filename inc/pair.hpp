#ifndef _PAIR_HPP_
# define _PAIR_HPP_

namespace ft
{
	// Pair<x, y> 
	template <class T1, class T2>
	struct pair
	{
		public :
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;
			
			pair() : first(), second() {}

			template<class U, class V>
			pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

			pair(const first_type& a, const second_type& b) : first(a), second(b) {}

			pair&	operator=(const pair& pr)
			{
				if (*this == pr)
					return (*this);
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			}
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
	bool	operator==(const ft::pair<T1,T2> &x, const ft::pair<T1,T2> &y)
	{
		return (x.first == y.first && x.second == y.second);
	}

	template <class T1, class T2>
	bool	operator!=(const ft::pair<T1,T2> &x, const ft::pair<T1,T2> &y)
	{
		return !(x == y);
	}
	
	template <class T1, class T2>
	bool	operator<(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
	{
		return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
	}

	template <class T1, class T2>
	bool	operator>(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
	{
		return (x.first > y.first || (!(y.first > x.first) && x.second > y.second));
	}

	template <class T1, class T2>
	bool	operator>=(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
	{
		return !(x < y);
	}

	template <class T1, class T2>
	bool	operator<=(const ft::pair<T1,T2>& x, const ft::pair<T1,T2>& y)
	{
		return !(y > x);
	}
}

#endif