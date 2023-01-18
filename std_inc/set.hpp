#ifndef _FT_SET_H
# define _FT_SET_H

# include <iostream>
# include <utility>
# include "RBTree.hpp"

namespace ft
{
	template < class T, class Compare = less<T>, class Alloc = std::allocator<T> >
	class set
	{
	private:
		typedef _Rb_tree<T, T, Compare, Alloc>	RBTree;
		RBTree	_RBT;
	public:
		typedef T				key_type;
		typedef T				value_type;
		typedef Compare			value_type;
		typedef Compare			key_compare;
		typedef Alloc			allocator_type;
		typedef std::ptrdiff_t	difference_type;

		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename RBTree::iterator					iterator;
		typedef typename RBTree::const_iterator			const_iterator;
		typedef typename RBTree::size_type				size_type;
		typedef typename RBTree::difference_type			difference_type;
		typedef typename RBTree::reverse_iterator			reverse_iterator;
		typedef typename RBTree::const_reverse_iterator	const_reverse_iterator;

		// empty
		explicit	set(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _RBT(comp) {}
		
		// range
		template <class InputIterator>	set(InputIterator first,
			InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _RBT()
		{ _RBT._M_insert_range_unique(__first, __last); }
		
		// copy
		set (const set& x) : _RBT(__x._RBT) {}

		~set() {}

		set&	operator=(const set& __x)
		{
			_RBT = __x._RBT;
			return *this;
		}

		/// Get a copy of the memory allocation object.
		allocator_type	get_allocator() const 
		{ return allocator_type(_RBT.get_allocator()); }

		// iterators
		iterator	begin() 
		{ return _RBT.begin(); }

		const_iterator	begin() const 
		{ return _RBT.begin(); }

		iterator	end() 
		{ return _RBT.end(); }

		const_iterator	end() const 
		{ return _RBT.end(); }

		reverse_iterator	rbegin() 
		{ return _RBT.rbegin(); }

		const_reverse_iterator	rbegin() const 
		{ return _RBT.rbegin(); }

		reverse_iterator	rend() 
		{ return _RBT.rend(); }

		const_reverse_iterator	rend() const 
		{ return _RBT.rend(); }

		bool	empty() const 
		{ return _RBT.empty(); }

		size_type	size() const 
		{ return _RBT.size(); }

		size_type	max_size() const 
		{ return _RBT.max_size(); }

		setped_type&	operator[](const key_type& __k)
		{
			iterator __i = lower_bound(__k);
			if (__i == end() || key_comp()(__k, (*__i).first))
				__i = insert(__i, value_type(__k, setped_type()));
			return (*__i).second;
		}

		setped_type&	at(const key_type& __k)
		{
			iterator __i = lower_bound(__k);
			if (__i == end() || key_comp()(__k, (*__i).first))
				std::__throw_out_of_range(__N("set::at"));
			return (*__i).second;
		}

		const setped_type&	at(const key_type& __k) const
		{
			const_iterator __i = lower_bound(__k);
			if (__i == end() || key_comp()(__k, (*__i).first))
				std::__throw_out_of_range(__N("set::at"));
			return (*__i).second;
		}

		ft::pair<iterator, bool>	insert(const value_type& __x)
		{ return _RBT._M_insert_unique(__x); }

		iterator	insert(iterator __position, const value_type& __x)
		{ return _RBT._M_insert_unique_(__position, __x); }

		template<typename _InputIterator>
		void	insert(_InputIterator __first, _InputIterator __last)
		{ _RBT._M_insert_range_unique(__first, __last); }

		void	erase(iterator __position)
		{ _RBT.erase(__position); }

		size_type	erase(const key_type& __x)
		{ return _RBT.erase(__x); }

		void	erase(iterator __first, iterator __last)
		{ _RBT.erase(__first, __last); }

		void	swap(set& __x)
		{ _RBT.swap(__x._RBT); }

		void	clear()
		{ _RBT.clear(); }

		key_compare	key_comp() const
		{ return _RBT.key_comp(); }

		value_compare	value_comp() const
		{ return value_compare(_RBT.key_comp()); }

		iterator	find(const key_type& __x)
		{ return _RBT.find(__x); }

		const_iterator	find(const key_type& __x) const
		{ return _RBT.find(__x); }

		size_type	count(const key_type& __x) const
		{ return _RBT.find(__x) == _RBT.end() ? 0 : 1; }

		iterator	lower_bound(const key_type& __x)
		{ return _RBT.lower_bound(__x); }

		const_iterator	lower_bound(const key_type& __x) const
		{ return _RBT.lower_bound(__x); }

		iterator	upper_bound(const key_type& __x)
		{ return _RBT.upper_bound(__x); }

		const_iterator	upper_bound(const key_type& __x) const
		{ return _RBT.upper_bound(__x); }

		ft::pair<iterator, iterator>	equal_range(const key_type& __x)
		{ return _RBT.equal_range(__x); }

		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& __x) const
		{ return _RBT.equal_range(__x); }

		template<typename _K1, typename _C1, typename _A1>
		friend bool	operator==(const set<_K1, _C1, _A1>&,
			const set<_K1, _C1, _A1>&);

		template<typename _K1, typename _C1, typename _A1>
		friend bool	operator<(const set<_K1, _C1, _A1>&,
			const set<_K1, _C1, _A1>&);
	};

	template<typename _Key, typename _Compare, typename _Alloc>
	inline bool	operator==(const set<_Key, _Compare, _Alloc>& __x,
		const set<_Key, _Compare, _Alloc>& __y)
	{ return __x._RBT == __y._RBT; }

	template<typename _Key, typename _Compare, typename _Alloc>
	inline bool	operator<(const set<_Key, _Compare, _Alloc>& __x,
		const set<_Key, _Compare, _Alloc>& __y)
	{ return __x._RBT < __y._RBT; }

	template<typename _Key, typename _Compare, typename _Alloc>
	inline bool	operator!=(const set<_Key, _Compare, _Alloc>& __x,
		const set<_Key, _Compare, _Alloc>& __y)
	{ return !(__x == __y); }

	template<typename _Key, typename _Compare, typename _Alloc>
	inline bool	operator>(const set<_Key, _Compare, _Alloc>& __x,
		const set<_Key, _Compare, _Alloc>& __y)
	{ return __y < __x; }

	template<typename _Key, typename _Compare, typename _Alloc>
	inline bool	operator<=(const set<_Key, _Compare, _Alloc>& __x,
		const set<_Key, _Compare, _Alloc>& __y)
	{ return !(__y < __x); }

	template<typename _Key, typename _Compare, typename _Alloc>
	inline bool	operator>=(const set<_Key, _Compare, _Alloc>& __x,
		const set<_Key, _Compare, _Alloc>& __y)
	{ return !(__x < __y); }

	template<typename _Key, typename _Compare, typename _Alloc>
	inline void	swap(set<_Key, _Compare, _Alloc>& __x,
		set<_Key, _Compare, _Alloc>& __y)
	{ __x.swap(__y); }

} // namespace ft

#endif /* _FT_SET_H */