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
	template <class T, class Allocator = std::allocator<T> >
	class vector 
	{
		public:
			
			// types:
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef implementation defined iterator; // See 23.1
			typedef implementation defined const_iterator; // See 23.1
			typedef implementation defined size_type; // See 23.1
			typedef implementation defined difference_type;// See 23.1
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			explicit vector(const Allocator& = Allocator());
			explicit vector(size_type n, const T& value = T(),
			const Allocator& = Allocator());
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
			const Allocator& = Allocator());
			vector(const vector<T,Allocator>& x);
			~vector();
			vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const T& u);
			allocator_type get_allocator() const;

			// iterators:
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			// 23.2.4.2 capacity:
			size_type size() const;
			size_type max_size() const;
			void resize(size_type sz, T c = T());
			size_type capacity() const;
			bool empty() const;
			void reserve(size_type n);

			// element access:
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			const_reference at(size_type n) const;
			reference at(size_type n);
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;

			// 23.2.4.3 modifiers:
			void push_back(const T& x);
			void pop_back();
			iterator insert(iterator position, const T& x);
			void insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void insert(iterator position,
			InputIterator first, InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void swap(vector<T,Allocator>&);
			void clear();
	};

	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	
	// specialized algorithms:
	template <class T, class Allocator>
	void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}

// namespace ft
// {
// 	template< class T, class Alloc = T>
// 	class vector
// 	{
// 		public :

// 			class T value_type;
// 			class T* pointer;
// 			class const T* const_pointer;
// 			class conts T& reference;
// 			typedef typename std::container_type::iterator iterator;

// 			iterator const	begin(void) {return this->c.begin();}
// 			iterator const	end(void) {return this->c.end();}
// 			iterator const	rbegin(void);
// 			iterator const	rend(void);
// 			iterator const	cbegin(void) {return this->c.begin();}
// 			iterator const	cend(void) {return this->c.end();}
// 			iterator const	crbegin(void);
// 			iterator const	crend(void);

// 	};
// }

#endif