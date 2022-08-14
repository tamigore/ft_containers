/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:26:28 by user42            #+#    #+#             */
/*   Updated: 2022/08/13 15:17:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VECTOR_HPP_
# define _VECTOR_HPP_

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <iostream>

template< class T, class Alloc = T> class vector
{
	public :

        class T value_type;
        class T* pointer;
        class const T* const_pointer;
        class conts T& reference;
		typedef typename std::container_type::iterator iterator;

		iterator const	begin(void) {return this->c.begin();}
		iterator const	end(void) {return this->c.end();}

};

#endif