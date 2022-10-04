/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:11:22 by tamigore          #+#    #+#             */
/*   Updated: 2022/08/14 16:11:37 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ITERATOR_HPP_
# define _ITERATOR_HPP_

#include <iterator>

namespace ft
{
	template<typename _Iterator>
	struct iterator_traits
	{
	  typedef typename _Iterator::iterator_category	iterator_category;
	  typedef typename _Iterator::value_type		value_type;
	  typedef typename _Iterator::difference_type	difference_type;
	  typedef typename _Iterator::pointer			pointer;
	  typedef typename _Iterator::reference			reference;
	};

  /// Partial specialization for pointer types.
  template<typename _Tp>
	struct iterator_traits<_Tp*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef _Tp								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef _Tp*							pointer;
		typedef _Tp&							reference;
	};

  /// Partial specialization for const pointer types.
  template<typename _Tp>
	struct iterator_traits<const _Tp*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef _Tp								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const _Tp*						pointer;
		typedef const _Tp&						reference;
	};
}
 #endif