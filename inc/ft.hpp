/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:05:21 by user42            #+#    #+#             */
/*   Updated: 2022/08/14 15:16:03 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_HPP_
# define _FT_HPP_

# include "map.hpp"
# include "vector.hpp"
# include "iterator.hpp"
# include "stack.hpp"
# include "usefull.hpp"

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>

int vector_test();
int stack_test();

static class nullptr_t
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

} ft_nullptr = {};

namespace ft
{
	template< class T, class Alloc = T>
	class vector;

	template< class T, class Alloc = T>
	class map;
	
	template <class T, class Container = std::vector<T> >
	class stack;
}

#endif