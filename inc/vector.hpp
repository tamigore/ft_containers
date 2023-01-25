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
			size_type		_size;
			size_type		_capacity;

		public:
			// constructor
			explicit vector( const Allocator& alloc = Allocator())
				: _alloc(alloc), _start(NULL), _size(0), _capacity(0) {}

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
				: _alloc(alloc), _start(NULL), _size(0), _capacity(0)
			{
				if (count <= 0)
					return ;
				if (count > max_size())
					count = max_size();
				_start = _alloc.allocate(count);
				_capacity = count;
				while (_size < count)
					_alloc.construct(&_start[_size++], value);
			}

			template <class InputIt>
			vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last,
				const Allocator& alloc = Allocator()) : _alloc(alloc), _start(NULL), _size(0), _capacity(0)
			{
				size_type	dist = std::distance(first, last);

				if (dist <= 0)
					return ;
				if (dist > max_size())
					dist = max_size();
				_start = _alloc.allocate(dist);
				_capacity = dist;
				while (first != last && _size < dist)
				{
					_alloc.construct(&_start[_size++], *first);
					first++;
				}
			}

			// destructor
			~vector()
			{
				clear();
				if (_start)
				{
					_alloc.deallocate(_start, capacity());
					_start = NULL;
				}
			}

			// copy
			vector(const vector<T,Allocator>& x)
				: _alloc(x._alloc), _start(NULL), _size(0), _capacity(x.size())
			{
				_start = _alloc.allocate(_capacity);
				while (_size < _capacity)
				{
					_alloc.construct(&_start[_size], x[_size]);
					_size++;
				}
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
				clear();
				reserve(count);
				insert(begin(), count, value);
			}

			template< class InputIt >
			void assign(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			{
				clear();
				reserve(std::distance(first, last));
				insert(begin(), first, last);
			}

			allocator_type get_allocator() const
			{ return (_alloc); }

			iterator	begin(void)
			{ return (iterator(_start)); }

			const_iterator begin() const
			{ return (const_iterator(_start)); }

			iterator	end(void)
			{ return (iterator(&_start[_size])); }

			const_iterator end() const
			{ return (const_iterator(&_start[_size])); }

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
			{ return (_size); }

			size_type max_size() const
			{ return (_alloc.max_size()); }

			void resize(size_type count, T value = T())
			{
				if (count > max_size())
					return ;
				else if (count > _size)
					insert(end(), count - _size, value);
				else if (count < _size)
				{
					while (count < _size)
						_alloc.destroy(&_start[--_size]);
				}
			}

			size_type capacity() const
			{ return (_capacity); }

			bool empty() const
			{ return (!_size ? true : false); }

			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				else if (n > _capacity)
				{
					vector tmp = *this;
					size_type old_size = _size;
					size_type old_capacity = _capacity;
					pointer old_start = _start;
					clear();
					_alloc.deallocate(old_start, old_capacity);
					_capacity = n;
					if (_capacity)
						_start = _alloc.allocate(_capacity);
					_size = 0;
					for (;_size < old_size; _size++)
						_alloc.construct(&_start[_size], tmp[_size]);
				}
			}

			// element access:
			reference operator[](size_type n)
			{ return (_start[n]); }

			const_reference operator[](size_type n) const
			{ return (_start[n]); }

			reference at(size_type n)
			{
				if (!(n < _size))
					throw (std::out_of_range("pos >= size()"));
				return (_start[n]);
			}

			const_reference at(size_type n) const
			{
				if (!(n < _size))
					throw (std::out_of_range("pos >= size()"));
				return (_start[n]);
			}

			reference front()
			{ return (*_start); }

			const_reference front() const
			{ return (*_start); }

			reference back()
			{ return (_start[_size - 1]); }

			const_reference back() const
			{ return (_start[_size - 1]); }

			// 23.2.4.3 modifiers:
			void push_back(const T& x)
			{
				if (_capacity < _size + 1)
					reserve(std::max(size() * 2, (size_type)1));
				_alloc.construct(&_start[_size++], x);
			}

			void pop_back()
			{
				if (_start && _size)
					_alloc.destroy(&_start[--_size]);
			}

			iterator insert(iterator pos, const value_type& val)
			{
				try
				{
					ft::vector<value_type>	tmp_v = *this;
					iterator tmp_it = tmp_v.begin() + std::distance(begin(), pos);
					size_type tmp_s = std::distance(begin(), pos);

					if (_size + 1 > _capacity)
						reserve(_size * 2);
					clear();
					for (iterator it2 = tmp_v.begin(); it2 != tmp_it; it2++)
						push_back(*it2);
					push_back(val);
					for (iterator it2 = tmp_it; it2 != tmp_v.end(); it2++)
						push_back(*it2);
					return (&_start[tmp_s]);
				}
				catch(const std::exception &e)
				{
					throw std::length_error("cannot create std::vector larger than max_size()");
				}
			}
			
			// fill
			void insert(iterator pos, size_type n, const value_type& val)
			{
				try
				{
					size_type s = _size + n; 
					size_type i = 0;
				
					ft::vector<value_type>	tmp_v = *this;
					iterator tmp_it = tmp_v.begin() + std::distance(begin(), pos);

					if (n == 0)
						return;
					if (s > _capacity)
						reserve(std::max(s, _size * 2));
					clear();
					for (iterator it2 = tmp_v.begin(); it2 != tmp_it; it2++)
						push_back(*it2);
					while (i != n)
					{
						push_back(val);
						i++;
					}
					for (iterator it2 = tmp_it; it2 != tmp_v.end(); it2++)
						push_back(*it2);
				}
				catch(const std::exception &e)
				{
					throw std::length_error("vector::_M_fill_insert");
				}
			}

			template <class _Iter>
			void insert(iterator pos, _Iter first, typename enable_if<!is_integral<_Iter>::value, _Iter>::type last)
			{
				try
				{
					size_type tmp2 = std::distance(first, last);
					size_type s = _size + tmp2;

					ft::vector<value_type>	tmp_v = *this;
					iterator tmp_it = tmp_v.begin() + std::distance(begin(), pos);
				
					if (s > _capacity){
						reserve(std::max(s, _size * 2));
					}
					clear();

					for (iterator it2 = tmp_v.begin(); it2 != tmp_it; it2++)
						push_back(*it2);

					for (size_type i = 0; first != last; i++)
						push_back(*first++);
					for (iterator it2 = tmp_it; it2< tmp_v.end(); it2++)
						push_back(*it2);
				}
				catch(const std::exception &e)
				{
					throw std::length_error("vector::_M_fill_insert"); 
				}
			}
			// iterator insert(const_iterator pos, const T& value)
			// {
			// 	size_type	len = pos - begin();
			// 	size_type	i = 0;
			// 	iterator	ret = _start + len;

			// 	if (_size + 1 > max_size())
			// 		throw (std::length_error("vector::insert (one))"));
			// 	if (_capacity < _size + 1)
			// 	{
			// 		pointer		old_start = _start;
			// 		size_type	old_size = _size;
			// 		size_type	old_cap = _capacity;
			// 		size_type	new_cap = std::max(_size * 2, (size_type)1);

			// 		_start = _alloc.allocate(new_cap);
			// 		_size = 0;
			// 		_capacity = new_cap;
			// 		while (_size < old_size + 1)
			// 		{
			// 			if (i == len && ret == pos)
			// 			{
			// 				ret = &_start[_size];
			// 				_alloc.construct(&_start[_size++], value);
			// 			}
			// 			if (i < old_size)
			// 				_alloc.construct(&_start[_size++], old_start[i++]);
			// 		}
			// 		_alloc.deallocate(old_start, old_cap);
			// 	}
			// 	else
			// 	{
			// 		i = _size;
			// 		while (i-- > len)
			// 			_alloc.construct(&_start[i + 1], _start[i]);
			// 		i = len;
			// 		_size++;
			// 		_alloc.construct(&_start[i], value);
			// 		ret = &_start[i];
			// 	}
			// 	return (ret);
			// }

			// iterator	insert(const_iterator pos, size_type count, const T& value)
			// {
			// 	size_type	len = pos - begin();
			// 	size_type	i = 0;
			// 	iterator	ret = _start + len;

			// 	if (count <= 0)
			// 		return (ret);
			// 	if (count + _size > max_size())
			// 		throw (std::length_error("vector::insert (fill)"));
			// 	if (_capacity < _size + count)
			// 	{
			// 		pointer		old_start = _start;
			// 		size_type	old_size = _size;
			// 		size_type	old_cap = _capacity;
			// 		size_type	new_cap = std::max(_size + count, _size * 2);

			// 		_start = _alloc.allocate(new_cap);
			// 		_size = 0;
			// 		_capacity = new_cap;
			// 		while (_size < old_size + count)
			// 		{
			// 			if (i == len && ret == pos)
			// 			{
			// 				ret = &_start[_size];
			// 				for (size_type i = count; i > 0; i--)
			// 					_alloc.construct(&_start[_size++], value);
			// 			}
			// 			else if (i < old_size)
			// 				_alloc.construct(&_start[_size++], old_start[i++]);
			// 		}
			// 		_alloc.deallocate(old_start, old_cap);
			// 	}
			// 	else
			// 	{
			// 		_size += count;
			// 		i = _size - 1;
			// 		ret = _start + len;
			// 		while (i > len)
			// 		{
			// 			if (i < len + count)
			// 				_alloc.construct(&_start[i], value);
			// 			else
			// 				_alloc.construct(&_start[i], _start[i - count]);
			// 			i--;
			// 		}
			// 		if (i < len + count)
			// 			_alloc.construct(&_start[i], value);
			// 		else
			// 			_alloc.construct(&_start[i], _start[i - count]);
			// 	}
			// 	return (ret);
			// }

			// template<class InputIt>
			// iterator	insert(const_iterator pos, InputIt first,
			// 	typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			// {
			// 	size_type	len = pos - begin();
			// 	size_type	dist = std::distance(first, last);
			// 	size_type	i = 0;
			// 	iterator	ret = _start + len;

			// 	if (dist <= 0)
			// 		return (ret);
			// 	if (dist + _size > max_size())
			// 		throw (std::length_error("vector::insert (fill)"));
			// 	if (_capacity < _size + dist)
			// 	{
			// 		pointer		old_start = _start;
			// 		size_type	old_size = _size;
			// 		size_type	old_cap = _capacity;
			// 		size_type	new_cap = std::max(_size + dist, _size * 2);

			// 		_start = _alloc.allocate(new_cap);
			// 		_size = 0;
			// 		_capacity = new_cap;
			// 		while (_size < old_size + dist)	
			// 		{
			// 			if (i == len && ret == pos)
			// 			{
			// 				ret = &_start[_size];
			// 				while (first != last)
			// 					_alloc.construct(&_start[_size++], *(first++));
			// 			}
			// 			else
			// 				_alloc.construct(&_start[_size++], old_start[i++]);
			// 		}
			// 		_alloc.deallocate(old_start, old_cap);
			// 	}
			// 	else
			// 	{
			// 		_size += dist;
			// 		while (i++ < len)
			// 			_alloc.construct(&_start[_size - i], _start[_size - i - dist]);
			// 		ret = &_start[_size - dist - i];
			// 		while (dist--)
			// 			_alloc.construct(&_start[_size - dist - i], *(first++));
			// 	}
			// 	return (ret);
			// }

			iterator	erase(iterator position)
			{
				if (position == end())
					return (end());
				if (_start)
				{
					size_type dist = position - begin();
					for (size_type i = dist; i < _size - 1; i++)
						_start[i] = _start[i + 1];
					_alloc.destroy(&_start[--_size]);
					return (_start + dist);
				}
				return (iterator());
			}

			iterator	erase(iterator first, iterator last)
			{
				if (first == last)
					return (last);
				if (_start)
				{
					size_type dist = std::distance(first, last);
					size_type pos = first - begin();
					for (size_type i = 0; pos + dist + i < _size; i++)
						_start[pos + i] = _start[pos + dist + i];
					while (dist--)
						_alloc.destroy(&_start[--_size]);
					if (last == end())
						return (end());
					return (iterator(_start + pos));
				}
				return (iterator());
			}

			void	swap(vector &other)
			{
				ft::swap((other._alloc), (_alloc));
				ft::swap((other._start), (_start));
				ft::swap((other._size), (_size));
				ft::swap((other._capacity), (_capacity));
			}

			void	clear()
			{
				if (_start)
					erase(begin(), end());
			}
	};
	
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{ return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end())); }

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{ return (!(x < y) && !(y < x)); };

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{ return (!(x == y)); }

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{ return (!(x > y)); }

	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{ return (ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end())); }

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& x, const vector<T,Alloc>& y)
	{ return (!(x < y)); }

	// specialized algorithms:
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{ x.swap(y); }
}

#endif