#ifndef _FT_MAP_H
# define _FT_MAP_H

# include <iostream>
# include <utility>
# include "RBTree.hpp"

namespace ft
{
	template <typename Key, typename T, typename Compare = std::less<Key>,
	typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef Compare					key_compare;
		typedef Alloc					allocator_type;

		class value_compare
		{
			friend class map<Key, T, Compare, Alloc>;
		
		protected:
			Compare comp;

			value_compare(Compare __c) : comp(__c) { }

		public:
			bool operator()(const value_type& __x, const value_type& __y) const
			{ return comp(__x.first, __y.first); }
		};

	private:
		typedef _Rb_tree<key_type, value_type, _Select1st<value_type>, key_compare, allocator_type> RBTree;
		/// The actual tree structure.
		RBTree _RBT;

	public:
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename RBTree::iterator					iterator;
		typedef typename RBTree::const_iterator				const_iterator;
		typedef typename RBTree::size_type					size_type;
		typedef typename RBTree::difference_type			difference_type;
		typedef typename RBTree::reverse_iterator			reverse_iterator;
		typedef typename RBTree::const_reverse_iterator		const_reverse_iterator;

		explicit	map(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: _RBT(comp, alloc) { }

		map(const map& x)
		: _RBT(x._RBT) { }

		template<typename _InputIterator>
		map(_InputIterator __first, _InputIterator __last,
			const key_compare& __comp = key_compare(),
			const allocator_type& __a = allocator_type()) : _RBT(__comp, __a)
		{ _RBT.Insert_range_unique(__first, __last); }

		~map() { }

		map&	operator=(const map& __x)
		{
			_RBT = __x._RBT;
			return *this;
		}

		allocator_type	getAllocator() const 
		{ return allocator_type(_RBT.getAllocator()); }

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

		mapped_type&	operator[](const key_type& __k)
		{
			iterator __i = lower_bound(__k);
			if (__i == end() || key_comp()(__k, (*__i).first))
				__i = insert(__i, value_type(__k, mapped_type()));
			return (*__i).second;
		}

		mapped_type&	at(const key_type& __k)
		{
			iterator __i = lower_bound(__k);
			if (__i == end() || key_comp()(__k, (*__i).first))
				std::__throw_out_of_range(__N("map::at"));
			return (*__i).second;
		}

		const mapped_type&	at(const key_type& __k) const
		{
			const_iterator __i = lower_bound(__k);
			if (__i == end() || key_comp()(__k, (*__i).first))
				std::__throw_out_of_range(__N("map::at"));
			return (*__i).second;
		}

		ft::pair<iterator, bool>	insert(const value_type& __x)
		{ return _RBT.Insert_unique(__x); }

		iterator	insert(iterator __position, const value_type& __x)
		{ return _RBT.Insert_unique_(__position, __x); }

		template<typename _InputIterator>
		void	insert(_InputIterator __first, _InputIterator __last)
		{ _RBT.Insert_range_unique(__first, __last); }

		void	erase(iterator __position)
		{ _RBT.erase(__position); }

		size_type	erase(const key_type& __x)
		{ return _RBT.erase(__x); }

		void	erase(iterator __first, iterator __last)
		{ _RBT.erase(__first, __last); }

		void	swap(map& __x)
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

		template<typename _K1, typename _T1, typename _C1, typename _A1>
		friend bool	operator==(const map<_K1, _T1, _C1, _A1>&,
			const map<_K1, _T1, _C1, _A1>&);

		template<typename _K1, typename _T1, typename _C1, typename _A1>
		friend bool	operator<(const map<_K1, _T1, _C1, _A1>&,
			const map<_K1, _T1, _C1, _A1>&);
	};

	template<typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator==(const map<Key, T, Compare, Alloc>& __x,
		const map<Key, T, Compare, Alloc>& __y)
	{ return __x._RBT == __y._RBT; }

	template<typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator<(const map<Key, T, Compare, Alloc>& __x,
		const map<Key, T, Compare, Alloc>& __y)
	{ return __x._RBT < __y._RBT; }

	template<typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator!=(const map<Key, T, Compare, Alloc>& __x,
		const map<Key, T, Compare, Alloc>& __y)
	{ return !(__x == __y); }

	template<typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator>(const map<Key, T, Compare, Alloc>& __x,
		const map<Key, T, Compare, Alloc>& __y)
	{ return __y < __x; }

	template<typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator<=(const map<Key, T, Compare, Alloc>& __x,
		const map<Key, T, Compare, Alloc>& __y)
	{ return !(__y < __x); }

	template<typename Key, typename T, typename Compare, typename Alloc>
	inline bool	operator>=(const map<Key, T, Compare, Alloc>& __x,
		const map<Key, T, Compare, Alloc>& __y)
	{ return !(__x < __y); }

	template<typename Key, typename T, typename Compare, typename Alloc>
	inline void	swap(map<Key, T, Compare, Alloc>& __x,
		map<Key, T, Compare, Alloc>& __y)
	{ __x.swap(__y); }

} // namespace ft

#endif /* _FT_MAP_H */