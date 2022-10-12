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

# include <iostream>
# include <iterator>
# include <algorithm>
# include <stdexcept>
# include <string>
# include <iterator>
# include "iterator.hpp"
# include "ft.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector 
	{
		public:
			// types:
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference 			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef std::iterator								iterator;
			typedef std::iterator								const_iterator;
			typedef std::reverse_iterator<iterator> 			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			pointer			_data;
			pointer			_start;
			pointer			_end;
			allocator_type	_alloc;
			size_type		_size;

		public:
			// constructor
			vector() : _data(nullptr_t), _start(nullptr_t), _end(nullptr_t), _alloc(allocator_type), _size(0);

			explicit vector( const Allocator& alloc )
			{
				_alloc = alloc;
				_size = alloc::size_type;
				_start = alloc::pointer;
				_data = _start
				_end = _start + _size;
			};

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
			{
				_data = value;
				_start = value;
				_end = value + count;
				_alloc = alloc;
				_size = count;
			};

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator())
			{
				_data = first;
				_start = first;
				_end = last;
				_alloc = Allocator;
				_size = first - last;
			};

			// destructor
			~vector() {};

			// copy
			vector(const vector<T,Allocator>& x) : _data(x._data), _alloc(x._alloc), _count(x._count) {};
			
			vector& operator=( const vector& other )
			{
				return (vector(x));
			}

			// assign
			void assign( size_type count, const T& value )
			{
				this->_data = value;
				this->_start = value;
				this->_end = value + count;
				this->_size = count;
				this->_alloc = std::allocator<T>;
			};

			template< class InputIt >
			void assign( InputIt first, InputIt last )
			{
				
			};

			allocator_type get_allocator() const {return (this->allocator_type)};

			std::iterator		begin(void) {return this->iterator.begin();}
			std::iterator		end(void) {return this->iterator.end();}
			std::iterator		rbegin(void) {return this->reverse_iterator.end();};
			std::iterator		rend(void) {return this->reverse_iterator.begin();};

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

			void swap( vector& other )
			{
				vector tmp(*this);
				*this = other;
				other = tmp;
			};

			void clear();
		
		template <class T, class Alloc>
		bool operator==(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
		{
			if (x._data == y._data)
				return (true);
			return (false);
		};

		template <class T, class Alloc>
		bool operator< (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
		{
			if (x._data < y._data)
				return (true);
			return (false);
		};

		template <class T, class Alloc>
		bool operator!=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
		{
			if (x._data != y._data)
				return (true);
			return (false);
		};

		template <class T, class Alloc>
		bool operator> (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
		{
			if (x._data > y._data)
				return (true);
			return (false);
		};

		template <class T, class Alloc>
		bool operator>=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
		{
			if (x._data >= y._data)
				return (true);
			return (false);
		};

		template <class T, class Alloc>
		bool operator<=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
		{
			if (x._data <= y._data)
				return (true);
			return (false);
		};
	};

	// specialized algorithms:
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		vector<T,Alloc> tmp(x);
		x = y;
		y = tmp;
	};
}

#endif