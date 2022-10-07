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

#include "map.hpp"
#include "vector.hpp"
#include "iterator.hpp"
#include "stack.hpp"

int vector_test();
int stack_test();

namespace ft
{
    template< class T, class Alloc = T>
    class vector;
    // class map;
    template <class T, class Container = std::vector<T> >
    class stack;
}

#endif