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
				_start = _alloc.allocate(count + 1);
				_end = _start;
				_capacity = _start + count + 1;
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
			template <class InputIt>
			vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last, const Allocator& alloc = Allocator())
				: _alloc(alloc)
			{
				size_type	dist = ft::distance(first, last);

				_start = _alloc.allocate(dist + 1);
				_end = _start;
				_capacity = _start + dist + 1;
				while (first != last)
				{
					_alloc.construct(_end, *first);
					first++;
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
				
				_start = _alloc.allocate(x.capacity());
				_end = _start;
				_capacity = _start + dist;
				for (size_type i = 0; i < dist; i++)
				{
					_alloc.construct(_end, x[i]);
					_end++;
				}
			}
			
			vector& operator=(const vector& other)
			{
				if (*this == other)
					return (*this);
				clear();
				insert(this->begin(), other.begin(), other.end());
				return (*this);
			}

			void assign(size_type count, const T& value)
			{
				if (!empty())
					clear();
				_start = _alloc.allocate(count);
				_end = _start;
				_capacity = _start + count;
				for (size_type i = 0; i < count; i++)
				{
					_alloc.construct(_end, value);
					_end++;
				}
				// insert(begin(), count, value);
			};

			template< class InputIt >
			void assign(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			{
				if (!empty())
					clear();
				size_type dist = ft::distance(first, last);
				_start = _alloc.allocate(dist);
				_end = _start;
				_capacity = _start + dist;
				for (size_type i = 0; i < dist; i++)
				{
					_alloc.construct(_end, *first);
					first++;
					_end++;
				}
				// insert(begin(), first, last);
			};

			allocator_type get_allocator() const
				{ return (_alloc); }

			iterator	begin(void)
				{ return (_start); }

			const_iterator begin() const
				{ return (_start); }

			iterator	end(void)
				{ return (_end); }

			const_iterator end() const
				{ return (_end); }

			reverse_iterator	rbegin(void)
				{ return (reverse_iterator(end())); }

			const_reverse_iterator	rbegin(void) const
				{ return (reverse_iterator(end())); }
			
			reverse_iterator	rend(void)
				{ return (reverse_iterator(begin())); }

			const_reverse_iterator	rend(void) const
				{ return (reverse_iterator(begin())); }

			// 23.2.4.2 capacity:
			size_type size() const
				{ return (_end - _start); }

			size_type max_size() const
				{ return (_alloc.max_size()); }

			void resize(size_type count, T value = T())
			{
				if (count > this->max_size())
					throw (std::length_error("vector::resize"));
				std::cout << "size = " << size() << " | count = " <<  count << std::endl;
				if (count > size())
				{
					insert(end(), count, value);
				}
				else
				{
					while (count < size())
					{
						_end--;
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

			iterator insert(const_iterator pos, const T& value)
			{
				size_type	len = pos - begin();
				size_type	i = 0;
				iterator	ret = pos;

				if (size() + 1 > this->max_size())
					throw (std::length_error("vector::insert (one))"));
				if (capacity() < size() + 1)
				{
					pointer		old_start = _start;
					size_type	old_size = size();
					size_type	old_cap = capacity();
					size_type	new_cap = (capacity() > 0 ? capacity() * 2 : 1);

					_start = _alloc.allocate(new_cap);
					_end = _start;
					_capacity = _start + new_cap;
					while (size() < old_size + 1)
					{
						if (i == len && ret == pos)
						{
							ret = _end;
							_alloc.construct(_end++, value);
						}
						if (i < old_size)
							_alloc.construct(_end++, *(old_start + i++));
					}
					_alloc.deallocate(old_start, old_cap);
				}
				else
				{
					i = len;
					while (i++ < size())
						_alloc.construct(_start + i + 1, *(_start + i));
					i = len;
					_end++;
					_alloc.construct(_start + i, value);
					ret = _start + i;
				}
				return (ret);
			}

			iterator insert(const_iterator pos, size_type count, const T& value)
			{
				size_type	len = pos - begin();
				size_type	i = 0;
				iterator	ret = pos;

				if (count == 0)
					return (pos);
				if (count + size() > this->max_size())
					throw (std::length_error("vector::insert (fill)"));
				if (capacity() < size() + count)
				{
					pointer		old_start = _start;
					size_type	old_size = size();
					size_type	old_cap = capacity();
					size_type	new_cap = (capacity() > 0 ?
						(capacity() * 2 < count + size() ?
						capacity() + count : capacity() * 2)
						: count + 1);

					_start = _alloc.allocate(new_cap);
					_end = _start;
					_capacity = _start + new_cap;
					while (size() < old_size + count)
					{
						if (i == len && ret == pos)
						{
							ret = _end;
							while (count--)
								_alloc.construct(_end++, value);
						}
						else if (i < old_size)
							_alloc.construct(_end++, *(old_start + i++));
					}
					_alloc.deallocate(old_start, old_cap);
				}
				else
				{
					_end += count;
					i = size() - 1;
					ret = _start + len;
					while (i >= len)
					{
						if (i < len + count)
							_alloc.construct(_start + i, value);
						else
							_alloc.construct(_start + i, *(_start + i - count));
						i--;
					}
				}
				return (ret);
			}

			template<class InputIt>
			iterator insert(const_iterator pos, InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			{
				size_type	len = pos - begin();
				size_type	dist = ft::distance(first, last);
				size_type	i = 0;
				iterator	ret = pos;

				if (first == last)
					return (pos);
				if (dist + size() > this->max_size())
					throw (std::length_error("vector::insert (fill)"));
				if (capacity() < size() + dist)
				{
					pointer		old_start = _start;
					size_type	old_size = size();
					size_type	old_cap = capacity();
					size_type	new_cap = (capacity() > 0 ?
						(capacity() * 2 < dist + size() ?
						capacity() + dist : capacity() * 2)
						: dist + 1);

					// std::cout << "allocate" << std::endl;
					_start = _alloc.allocate(new_cap);
					_end = _start;
					_capacity = _start + new_cap;
					while (size() < old_size + dist)
					{
						// std::cout << "construct :" << (i == len ? *first : *(old_start + i)) << std::endl;
						if (i == len && ret == pos)
						{
							ret = _end;
							while (first != last)
								_alloc.construct(_end++, *(first++));
						}
						// if (i < old_size)
							_alloc.construct(_end++, *(old_start + i++));
					}
					// std::cout << "deallocate" << std::endl;
					_alloc.deallocate(old_start, old_cap);
				}
				else
				{
					_end = _end + dist;
					while (i++ < len)
						_alloc.construct(_end - i, *(_end - i - dist));
					ret = _end - dist - i;
					while (dist--)
						_alloc.construct(_end - dist - i, *(first++));
				}
				return (ret);
			}

			iterator erase(iterator position)
			{
				if (position == end())
					return (end());
				size_type dist = position - begin();
				while (dist < size())
				{
					*(_start + dist) = *(_start + dist + 1);
					dist++;
				}
				_end--;
				_alloc.destroy(_end);
				return (position);
			}

			iterator erase(iterator first, iterator last)
			{
				if (first == last)
					return (last);
				size_type dist = ft::distance(first, last);
				size_type pos = first - begin();
				for (size_type i = 0; i < size() - dist; i++)
					*(_start + pos + i) = *(_start + pos + dist + i);
				while (dist--)
					_alloc.destroy(_end--);
				if (last == end())
					return (end());
				return (first);
			}

			void swap(vector& other)
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