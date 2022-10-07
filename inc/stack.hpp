/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:26:34 by user42            #+#    #+#             */
/*   Updated: 2022/08/13 14:26:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STACK_HPP_
# define _STACK_HPP_

#include <vector>

namespace ft
{
	template <class T, class Container = std::vector<T> >
	class stack
	{	
		public:

			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;
			typedef Container						container_type;
	
		protected:

			container_type c;
		
		public:

			explicit stack(const container_type &cont = container_type()) : c(cont) {}

			stack(const stack &copy) : c(copy.c) {}

			stack	&operator=(const stack& copy){ c = copy.c; return (*this); }

			bool empty() const { return c.empty(); }

			size_type size() const { return c.size(); }

			value_type& top() { return c.back(); }

			const value_type& top() const { return c.back(); }

			void push(const value_type& x) { c.push_back(x); }

			void pop() { c.pop_back(); }

		friend bool	operator==(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			if (x.c == y.c)
				return (true);
			return (false);
		};

		friend bool	operator<(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			if (x.c < y.c)
				return (true);
			return (false);
		};

		friend bool	operator<=(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			if (x.c <= y.c)
				return (true);
			return (false);
		};

		friend bool	operator!=(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			if (x.c != y.c)
				return (true);
			return (false);
		};

		friend bool	operator>(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			if (x.c > y.c)
				return (true);
			return (false);
		};

		friend bool	operator>=(const stack<T, Container> &x, const stack<T, Container> &y)
		{
			if (x.c >= y.c)
				return (true);
			return (false);
		};
	};
}

#endif