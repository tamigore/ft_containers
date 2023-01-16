#ifndef _VECTOR_HPP_
# define _VECTOR_HPP_

# include <algorithm>
# include <vector>
# include <stdexcept>
# include <string>

# include "random_access_iter.hpp"

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
			typedef ft::random_access_iterator<const T>			const_iterator;
			typedef ft::reverse_random_iterator<iterator> 		reverse_iterator;
			typedef ft::reverse_random_iterator<const_iterator>	const_reverse_iterator;

		private:
			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_capacity;

		public:
			// constructor
			vector() : _alloc(), _start(NULL), _end(NULL), _capacity(NULL) {}

			explicit vector( const Allocator& alloc )
				: _alloc(alloc), _start(NULL), _end(NULL), _capacity(NULL) {}

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
				: _alloc(alloc)
			{
				if (count <= 0)
					return ;
				if (count > max_size())
					count = max_size();
				_start = _alloc.allocate(count);
				_end = _start;
				_capacity = _start + count;
				while (count--)
				{
					_alloc.construct(_end, value);
					_end++;
				}
			}

			template <class InputIt>
			vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last,
				const Allocator& alloc = Allocator()) : _alloc(alloc)
			{
				size_type	dist = ft::distance(first, last);

				if (dist <= 0)
					return ;
				if (dist > max_size())
					dist = max_size();
				_start = _alloc.allocate(dist);
				_end = _start;
				_capacity = _start + dist;
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
				if (_start)
				{
					clear();
					_alloc.deallocate(_start, capacity());
					_start = NULL;
				}
			}

			// copy
			vector(const vector<T,Allocator>& x)
				: _alloc(x._alloc), _start(NULL), _end(NULL), _capacity(NULL)
			{
				size_type dist = x.size();
				
				_start = _alloc.allocate(dist);
				_end = _start;
				_capacity = _start + dist;
				for (size_type i = 0; i < dist; i++)
					_alloc.construct(_end++, x[i]);
			}
			
			vector& operator=(const vector& other)
			{
				if (this == &other)
					return (*this);
				clear();
				insert(begin(), other.begin(), other.end());
				return (*this);
			}

			void assign(size_type count, const T& value)
			{
				if (!empty())
					clear();
				if (count > capacity())
				{
					_alloc.deallocate(_start, capacity());
					_start = _alloc.allocate(count);
				}
				_end = _start;
				_capacity = _start + count;
				for (size_type i = 0; i < count; i++)
				{
					_alloc.destroy(_end);
					_alloc.construct(_end, value);
					_end++;
				}
			}

			template< class InputIt >
			void assign(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			{
				size_type dist = ft::distance(first, last);
				if (!empty())
					clear();
				if (dist > capacity())
				{
					_alloc.deallocate(_start, capacity());
					_start = _alloc.allocate(dist);
				}
				_end = _start;
				_capacity = _start + dist;
				for (size_type i = 0; i < dist; i++)
				{
					_alloc.destroy(_end);
					_alloc.construct(_end, *first);
					first++;
					_end++;
				}
			}

			allocator_type get_allocator() const
			{ return (_alloc); }

			iterator	begin(void)
			{ return (iterator(_start)); }

			const_iterator begin() const
			{ return (const_iterator(_start)); }

			iterator	end(void)
			{ return (iterator(_end)); }

			const_iterator end() const
			{ return (const_iterator(_end)); }

			reverse_iterator	rbegin(void)
			{ return (reverse_iterator(end())); }

			const_reverse_iterator	rbegin(void) const
			{ return (const_reverse_iterator(end())); }
			
			reverse_iterator	rend(void)
			{ return (reverse_iterator(begin())); }

			const_reverse_iterator	rend(void) const
			{ return (const_reverse_iterator(begin())); }

			// 23.2.4.2 capacity:
			size_type size() const
			{ return (_end - _start); }

			size_type max_size() const
			{ return (_alloc.max_size()); }

			void resize(size_type count, T value = T())
			{
				if (count > max_size())
					throw (std::length_error("vector::resize"));
				// std::cout << "size = " << size() << " | count = " <<  count << std::endl;
				if (count > size())
				{
					insert(end(), count - size(), value);
					// std::cout << size() << std::endl;
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
				if (new_cap > max_size())
					throw (std::length_error("vector::reserve"));
				else if (new_cap > capacity())
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
					reserve(cap);
				}
				_alloc.construct(_end, x);
				_end++;
			}

			void pop_back()
			{ _alloc.destroy(--_end); }

			iterator insert(const_iterator pos, const T& value)
			{
				size_type	len = pos - begin();
				size_type	i = 0;
				iterator	ret = _start + len;

				if (size() + 1 > max_size())
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
					i = size();
					while (i-- > len)
						_alloc.construct(_start + i + 1, *(_start + i));
					i = len;
					_end++;
					_alloc.construct(_start + i, value);
					ret = _start + i;
				}
				return (ret);
			}

			iterator	insert(const_iterator pos, size_type count, const T& value)
			{
				size_type	len = pos - begin();
				size_type	i = 0;
				iterator	ret = _start + len;

				if (count <= 0)
					return (ret);
				if (count + size() > max_size())
					throw (std::length_error("vector::insert (fill)"));
				if (capacity() < size() + count)
				{
					pointer		old_start = _start;
					size_type	old_size = size();
					size_type	old_cap = capacity();
					size_type	new_cap = (capacity() > 0 ? size() + count : count);
					// size_type	new_cap = (capacity() > 0 ?
					// 	(capacity() * 2 < count + size() ?
					// 	capacity() + count : capacity() * 2)
					// 	: count);

					_start = _alloc.allocate(new_cap);
					_end = _start;
					_capacity = _start + new_cap;
					while (size() < old_size + count)
					{
						if (i == len && ret == pos)
						{
							ret = _end;
							for (size_type i = count; i > 0; i--)
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
			iterator	insert(const_iterator pos, InputIt first,
				typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			{
				size_type	len = pos - begin();
				size_type	dist = ft::distance(first, last);
				size_type	i = 0;
				iterator	ret = _start + len;

				if (dist <= 0)
					return (ret);
				if (dist + size() > max_size())
					throw (std::length_error("vector::insert (fill)"));
				if (capacity() < size() + dist)
				{
					pointer		old_start = _start;
					size_type	old_size = size();
					size_type	old_cap = capacity();
					size_type	new_cap = (capacity() > 0 ? size() + dist : dist);
					// size_type	new_cap = (capacity() > 0 ?
					// 	(capacity() * 2 < dist + size() ? capacity() + dist : capacity() * 2) : dist);

					// std::cout << new_cap << std::endl;
					_start = _alloc.allocate(new_cap);
					_end = _start;
					_capacity = _start + new_cap;
					while (size() < old_size + dist)
					{
						if (i == len && ret == pos)
						{
							ret = _end;
							while (first != last)
								_alloc.construct(_end++, *(first++));
						}
						else
							_alloc.construct(_end++, *(old_start + i++));
					}
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

			iterator	erase(iterator position)
			{
				if (position == end())
					return (end());
				size_type dist = position - begin();
				for (size_type i = dist; i < size() - 1; i++)
					*(_start + i) = *(_start + i + 1);
				_end--;
				_alloc.destroy(_end);
				return (_start + dist);
			}

			iterator	erase(iterator first, iterator last)
			{
				if (first == last)
					return (last);
				size_type dist = ft::distance(first, last);
				size_type pos = first - begin();
				for (size_type i = 0; pos + dist + i < size(); i++)
					*(_start + pos + i) = *(_start + pos + dist + i);
				while (dist--)
					_alloc.destroy(--_end);
				if (last == end())
					return (end());
				return (iterator(_start + pos));
			}

			void	swap(vector &other)
			{
				ft::swap((other._alloc), (_alloc));
				ft::swap((other._start), (_start));
				ft::swap((other._end), (_end));
				ft::swap((other._capacity), (_capacity));
			}

			void	clear()
			{ erase(begin(), end()); }
	};
	
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		return (!(x < y) && !(y < x));
	};

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		return (!(x == y));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		return (!(x > y));
	}

	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		return (ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end()));
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{
		return (!(x < y));
	}

	// specialized algorithms:
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		vector<T,Alloc> tmp(x);
		x = y;
		y = tmp;
	}
}

#endif