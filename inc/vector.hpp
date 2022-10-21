#ifndef _VECTOR_HPP_
# define _VECTOR_HPP_

// # include <memory>
# include <algorithm>
# include <stdexcept>
# include <string>

# include "iterator.hpp"

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
			typedef ft::random_access_iterator<T>				iterator;
			typedef ft::random_access_iterator<T>				const_iterator;
			typedef ft::reverse_iterator<iterator> 				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_capacity;

		public:
			// constructor
			vector() : _alloc(), _start(ft_nullptr), _end(ft_nullptr), _capacity(ft_nullptr) {}

			explicit vector( const Allocator& alloc )
				: _alloc(alloc), _start(ft_nullptr), _end(ft_nullptr), _capacity(ft_nullptr) {}

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
				: _alloc(alloc)
			{
				_start = _alloc.allocate(count);
				_end = _start;
				_capacity = _start + count;
				while (count--)
				{
					_alloc.construct(_end, value);
					_end++;
				}
			}

			// Strong guarantee: no effects in case an exception is thrown.
			// If allocator_traits::construct is not supported with the
			// appropthrowriate arguments for the element constructions, or if
			// the range specified by [first,last) is not valid, it causes
			// undefined behavior.
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& alloc = Allocator())
				: _alloc(alloc)
			{
				size_type dist = ft::distance(first - last);
				_start = _alloc.allocate(dist);
				_end = _start;
				_capacity = _start + dist;
				for (size_type i = 0; i < dist; i++)
				{
					_alloc.construct(_end, first[i]);
					_end++;
				}
			}

			// destructor
			~vector()
			{
				clear();
				_alloc.deallocate(this->_start, this->capacity());
			}

			// copy
			vector(const vector<T,Allocator>& x)
				: _alloc(x._alloc), _start(ft_nullptr), _end(ft_nullptr), _capacity(ft_nullptr)
			{
				size_type dist = x.size();
				_start = _alloc.allocate(dist);
				_end = _start;
				_capacity = _start + dist;
				for (size_type i = 0; i < dist; i++)
				{
					_alloc.construct(_end, x[i]);
					_end++;
				}
			}
			
			vector& operator=( const vector& other )
			{
				if (*this == other)
					return (*this);
				clear();
				insert(this->begin(), other.begin(), other.end());
				return (*this);
			}

			void assign( size_type count, const T& value )
			{
				if (!empty())
					clear();
				insert(begin(), count, value);
			};

			template< class InputIt >
			void assign( InputIt first, InputIt last )
			{
				if (!empty())
					clear();
				insert(begin(), first, last);
			};

			allocator_type get_allocator() const
				{ return (_alloc); }

			iterator	begin(void)
				{ return (_start); }

			iterator	end(void)
				{ return (_end); }

			iterator	rbegin(void)
				{ return (_end - 1); }
			
			iterator	rend(void)
				{ return (begin - 1); }

			// 23.2.4.2 capacity:
			size_type size() const
				{ return (_end - _start); }

			size_type max_size() const
				{ return (_alloc.max_size()); }

			void resize(size_type count, T value = T())
			{
				if (count > this->max_size())
					throw (std::length_error("vector::resize"));
				else if (count > size())
					insert(_end, count, value);
				else
				{
					while (count < size())
					{
						end--;
						_alloc.destroy(_end);
					}
				}
			}

			size_type capacity() const
				{ return (_capacity - _start); }

			bool empty() const
				{ return (size() == 0 ? true : false); }

			void reserve(size_type new_cap)
			{
				if (new_cap > this->max_size())
					throw (std::length_error("vector::reserve"));
				else if (new_cap > this->capacity())
				{
					pointer		old_start = _start;
					pointer		old_end = _end;
					size_type	old_size = size();
					size_type	old_cap = capacity();

					_start = _alloc.allocate(new_cap);
					_end = _start;
					_capacity = _start + new_cap;
					while (old_start != old_end)
					{
						_alloc.construct(_end, *old_start);
						_end++;
						old_start++;
					}
					_alloc.deallocate(old_start - old_size, old_cap);
				}
			}

			// element access:
			reference operator[](size_type n)
				{ return (*(_start + n)); }

			const_reference operator[](size_type n) const
				{ return (*(_start + n)); }

			reference at(size_type n)
			{
				if (!(n < size()))
					throw (std::out_of_range("pos >= size()"));
				return (*(_start + n));
			}

			const_reference at(size_type n) const
			{
				if (!(n < size()))
					throw (std::out_of_range("pos >= size()"));
				return (*(_start + n));
			}

			reference front()
				{ return (*_start); }

			const_reference front() const
				{ return (*_start); }

			reference back()
				{ return (*(_end - 1)); }

			const_reference back() const
				{ return (*(_end - 1)); }

			// 23.2.4.3 modifiers:
			void push_back(const T& x)
			{
				if (_end == _capacity)
				{
					size_type cap = (capacity() > 0 ? capacity() * 2 : 2);
					this->reserve(cap);
				}
				_alloc.construct(_end, x);
				_end++;
			}

			void pop_back()
			{
				_alloc.destroy(_end - 1);
				_end--;
			}

			iterator insert( const_iterator pos, const T& value )
			{
				size_type len = pos - _start;
				size_type i = 0;

				if (size() + 1 > this->max_size())
					throw (std::length_error("vector::insert (one))"));
				if (capacity() <= size() + 1)
				{
					pointer		old_start = _start;
					pointer		old_end = _end;
					size_type	old_size = size();
					size_type	old_cap = capacity();
					size_type	new_cap = (capacity() > 0 ? capacity() * 2 : 2);

					_start = _alloc.allocate(new_cap);
					_end = _start;
					_capacity = _start + new_cap;
					while (old_start != old_end)
					{
						if (i == len)
							_alloc.construct(_end, value);
						else
						{
							_alloc.construct(_end, *old_start);
							old_start++;
						}
						_end++;
						i++;
					}
					_alloc.deallocate(old_start - old_size, old_cap);
				}
				else
				{
					while (i++ < len)
						_alloc.construct(_end - i, *(_end - i - 1));
					_alloc.construct(_end - i, value);
					_end++;
				}
			}

			iterator insert( const_iterator pos, size_type count, const T& value )
			{
				size_type len = pos - _start;
				size_type i = 0;

				if (count == 0)
					return (end());
				if (count + size() > this->max_size())
					throw (std::length_error("vector::insert (fill)"));
				if (capacity() <= size() + count)
				{
					pointer		old_start = _start;
					pointer		old_end = _end;
					size_type	old_size = size();
					size_type	old_cap = capacity();
					size_type	new_cap = (capacity() > 0 ?
						(capacity() * 2 < count + size() ?
						capacity() + count + size() : capacity() * 2)
						: count + 1);

					_start = _alloc.allocate(new_cap);
					_end = _start;
					_capacity = _start + new_cap;
					while (old_start != old_end)
					{
						if (i == len)
							_alloc.construct(_end, value);
						else
						{
							_alloc.construct(_end, *old_start);
							old_start++;
						}
						_end++;
						i++;
					}
					_alloc.deallocate(old_start - old_size, old_cap);
				}
				else
				{
					_end = _end + count;
					while (i++ < len)
						_alloc.construct(_end - i, *(_end - i - count));
					while (count--)
						_alloc.construct(_end - i++, value);
				}
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last)
			{
				size_type len = position - begin();
				size_type i = 0;
				size_type dist = ft::distance(first, last);


				// if (dist == 0)
				// 	insert(position, *first);
				if (dist + size() > this->max_size())
					throw (std::length_error("vector::insert (fill)"));
				if (capacity() <= size() + dist)
				{
					pointer		old_start = _start;
					pointer		old_end = _end;
					size_type	old_size = size();
					size_type	old_cap = capacity();
					size_type	new_cap = (capacity() > 0 ?
						(capacity() * 2 < dist + size() ?
						capacity() + dist + size() : capacity() * 2)
						: dist + 1);

					_start = _alloc.allocate(new_cap);
					_end = _start;
					_capacity = _start + new_cap;
					while (old_start != old_end)
					{
						if (i == len)
						{
							while (i - len < dist)
							{
								_alloc.construct(_end++, first[0]);
								first++;
								i++;
							}
						}
						else
						{
							_alloc.construct(_end, *old_start);
							old_start++;
						}
						_end++;
						i++;
					}
					_alloc.deallocate(old_start - old_size, old_cap);
				}
				else
				{
					_end = _end + dist;
					while (i++ < len)
						_alloc.construct(_end - i, *(_end - i - dist));
					while (dist--)
					{
						_alloc.construct(_end - dist - i, first[0]);
						first++;
					}
				}
			}

			iterator erase(iterator position)
			{
				if (position == end())
					return (end());
				clear();
			}

			iterator erase(iterator first, iterator last)
			{
				if (first == last)
					return (last);
				clear();
			}

			void swap( vector& other )
			{
				vector tmp(*this);
				*this = other;
				other = tmp;
			}

			void clear()
			{
				size_type tmp = this->size();

				while (tmp--)
				{
					_end--;
					_alloc.destroy(_end);
				}
			}
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		typedef typename Alloc::size_type size;
	
		if (x.size() != y.size())
			return (false);
		for (size i = 0; i < x.size(); i++)
		{
			if (x[i] != y[i])
				return (false);
		}
		return (true);
	};

	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		typedef typename Alloc::size_type size;

		if (x.size() >= y.size())
			return (false);
		for (size i = 0; i < x.size(); i++)
		{
			if (x[i] >= y[i])
				return (false);
		}
		return (true);
	};

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		if (x.size() == y.size())
			return (false);
		// for (Alloc::size_type i = 0; i < x.size(); i++)
		// {
		// 	if (x[i] != y[i])
		// 		return (true);
		// }
		return (true);
	};

	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		typedef typename Alloc::size_type size;
	
		if (x.size() <= y.size())
			return (false);
		for (size i = 0; i < x.size(); i++)
		{
			if (x[i] <= y[i])
				return (false);
		}
		return (true);
	};

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		typedef typename Alloc::size_type size;
	
		if (x.size() < y.size())
			return (false);
		for (size i = 0; i < x.size(); i++)
		{
			if (x[i] < y[i])
				return (false);
		}
		return (true);
	};

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		typedef typename Alloc::size_type size;

		if (x.size() > y.size())
			return (false);
		for (size i = 0; i < x.size(); i++)
		{
			if (x[i] > y[i])
				return (false);
		}
		return (true);
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