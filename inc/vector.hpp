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
	template <class T, class Alloc = std::allocator<T> >
	class vector 
	{
		public:
			// types:
			typedef Alloc							allocator_type;
			typedef typename Alloc::value_type 		value_type; 
			typedef typename Alloc::reference 		reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::difference_type	difference_type;
			typedef typename Alloc::size_type		size_type;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer	const_pointer;
			typedef std::reverse_iterator<std::iterator> reverse_iterator;
			typedef std::reverse_iterator<std::const_iterator> const_reverse_iterator;

			explicit	vector(const Alloc& = Alloc());
			explicit	vector(size_type n, const T& value = T(), const Alloc& = Alloc());
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Alloc& = Alloc());
			vector(const vector<T,Alloc>& x);
			~vector();
			vector<T,Alloc>& operator=(const vector<T,Alloc>& x);
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const T& u);
			allocator_type get_allocator() const;

			// iterators:
			// std::iterator		begin(void) {return this->c.begin();}
			// std::iterator		end(void) {return this->c.end();}
			// std::iterator		rbegin(void);
			// std::iterator		rend(void);
			// std::const_iterator	cbegin(void) {return this->c.begin();}
			// std::const_iterator	cend(void) {return this->c.end();}
			// std::const_iterator	crbegin(void);
			// std::const_iterator	crend(void);

			// iterator begin();
			// const_iterator begin() const;
			// iterator end();
			// const_iterator end() const;
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

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
			void swap(vector<T,Alloc>&);
			void clear();
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& x, const vector<T,Alloc>& y);
	
	// specialized algorithms:
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
}

#endif