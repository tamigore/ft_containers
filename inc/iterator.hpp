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

// #include <iterator>
# include <cstddef>

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
		typedef *T								pointer;
		typedef &T								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};
			
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const *T						pointer;
		typedef const &T						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template< class Iter >
	class reverse_iterator { };

	// struct input_iterator_tag { };
	// struct output_iterator_tag { };
	// struct forward_iterator_tag : public input_iterator_tag { };
	// struct bidirectional_iterator_tag : public forward_iterator_tag { };
	// struct random_access_iterator_tag : public bidirectional_iterator_tag { };
}

// namespace ft
// {
// 	template< class T, class Alloc = std::allocator<T> >
// 	class iterator
// 	{
// 		public:
// 			typedef typename Alloc::difference_type difference_type;
// 			typedef typename Alloc::value_type value_type;
// 			typedef typename Alloc::reference reference;
// 			typedef typename Alloc::pointer pointer;
// 			typedef std::random_access_iterator_tag iterator_category; //or another tag

// 			iterator();
// 			iterator(const iterator&);
// 			~iterator();

// 			iterator& operator=(const iterator&);
// 			bool operator==(const iterator&) const;
// 			bool operator!=(const iterator&) const;
// 			bool operator<(const iterator&) const; //optional
// 			bool operator>(const iterator&) const; //optional
// 			bool operator<=(const iterator&) const; //optional
// 			bool operator>=(const iterator&) const; //optional

// 			iterator& operator++();
// 			iterator operator++(int); //optional
// 			iterator& operator--(); //optional
// 			iterator operator--(int); //optional
// 			iterator& operator+=(size_type); //optional
// 			iterator operator+(size_type) const; //optional
// 			friend iterator operator+(size_type, const iterator&); //optional
// 			iterator& operator-=(size_type); //optional            
// 			iterator operator-(size_type) const; //optional
// 			difference_type operator-(iterator) const; //optional

// 			reference operator*() const;
// 			pointer operator->() const;
// 			reference operator[](size_type) const; //optional
		
// 		typedef std::reverse_iterator<iterator> reverse_iterator; //optional
// 	};

// 	template< class T, class Alloc = std::allocator<T> >
// 	class const_iterator
// 	{
// 		public:
// 			typedef typename Alloc::difference_type difference_type;
// 			typedef typename Alloc::value_type value_type;
// 			typedef typename const Alloc::reference reference;
// 			typedef typename const Alloc::pointer pointer;
// 			typedef std::random_access_iterator_tag iterator_category; //or another tag

// 			const_iterator();
// 			const_iterator(const const_iterator&);
// 			const_iterator(const iterator&);
// 			~const_iterator();

// 			const_iterator	&operator=(const const_iterator&);
// 			bool			operator==(const const_iterator&) const;
// 			bool			operator!=(const const_iterator&) const;
// 			bool			operator<(const const_iterator&) const; //optional
// 			bool			operator>(const const_iterator&) const; //optional
// 			bool			operator<=(const const_iterator&) const; //optional
// 			bool			operator>=(const const_iterator&) const; //optional

// 			const_iterator			&operator++();
// 			const_iterator			operator++(int); //optional
// 			const_iterator			&operator--(); //optional
// 			const_iterator			operator--(int); //optional
// 			const_iterator			&operator+=(size_type); //optional
// 			const_iterator			operator+(size_type) const; //optional
// 			friend const_iterator	operator+(size_type, const const_iterator&); //optional
// 			const_iterator			&operator-=(size_type); //optional            
// 			const_iterator			operator-(size_type) const; //optional
// 			difference_type			operator-(const_iterator) const; //optional

// 			reference	operator*() const;
// 			pointer		operator->() const;
// 			reference	operator[](size_type) const; //optional
// 	};

// 	typedef std::reverse_iterator<class const_iterator> const_reverse_iterator; //optional
// }

#endif