#ifndef _ITERATOR_HPP_
# define _ITERATOR_HPP_

# include <cstddef>

# include "utility.hpp"

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		public:
			/* Type of elements pointed. */
			typedef T			value_type;

			/* Type to represent the difference between two iterators. */
			typedef Distance	difference_type;

			/* Type to represent a pointer to an element pointed */
			typedef Pointer		pointer;

			/* Type to represent a reference to an element pointed */
			typedef Reference	reference;

			/* Category of the iterator. */
			typedef Category	iterator_category;
	};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
			
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
}

#endif