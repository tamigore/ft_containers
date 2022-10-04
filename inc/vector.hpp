/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:26:28 by user42            #+#    #+#             */
/*   Updated: 2022/08/14 15:30:58 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VECTOR_HPP_
# define _VECTOR_HPP_

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <iostream>

namespace ft
{
	template< class T, class Alloc = T>
	class vector
	{
		public :

			class T value_type;
			class T* pointer;
			class const T* const_pointer;
			class conts T& reference;
			typedef typename std::container_type::iterator iterator;

			iterator const	begin(void) {return this->c.begin();}
			iterator const	end(void) {return this->c.end();}
			iterator const	rbegin(void);
			iterator const	rend(void);
			iterator const	cbegin(void) {return this->c.begin();}
			iterator const	cend(void) {return this->c.end();}
			iterator const	crbegin(void);
			iterator const	crend(void);

	};
}

#endif