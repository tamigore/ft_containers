#ifndef _FT_TREE_H
# define _FT_TREE_H

// #pragma GCC system_header

// #include <bits/stl_algobase.h>
// #include <bits/allocator.h>
// #include <bits/stl_function.h>
// #include <bits/cpp_type_traits.h>
// #include <ext/alloc_traits.h>

# include <iostream>
# include <utility>
#include "pair.hpp"

namespace ft
{
	// Red-black tree class, designed for use in implementing STL
	// associative containers (set, multiset, map, and multimap). The
	// insertion and deletion algorithms are based on those in Cormen,
	// Leiserson, and Rivest, Introduction to Algorithms (MIT Press,
	// 1990), except that
	//
	// (1) the header cell is maintained with links not only to the root
	// but also to the leftmost node of the tree, to enable constant
	// time begin(), and to the rightmost node of the tree, to enable
	// linear time performance when used with the generic set algorithms
	// (set_union, etc.)
	//
	// (2) when a node being deleted has two children its successor node
	// is relinked into its place, rather than copied, so that the only
	// iterators invalidated are those referring to the deleted node.

	enum RBT_color { RED = false, BLACK = true };

	struct Node_base
	{
		typedef Node_base*		N_ptr;
		typedef const Node_base*	N_Const_ptr;

		RBT_color	_M_color;
		N_ptr		_M_parent;
		N_ptr		_M_left;
		N_ptr		_M_right;

		static N_ptr	_S_minimum(N_ptr __x) _GLIBCXX_NOEXCEPT
		{
			while (__x->_M_left != 0)
				__x = __x->_M_left;
			return __x;
		}

		static N_Const_ptr	_S_minimum(N_Const_ptr __x) _GLIBCXX_NOEXCEPT
		{
			while (__x->_M_left != 0)
				__x = __x->_M_left;
			return __x;
		}

		static N_ptr	_S_maximum(N_ptr __x) _GLIBCXX_NOEXCEPT
		{
			while (__x->_M_right != 0)
				__x = __x->_M_right;
			return __x;
		}

		static N_Const_ptr	_S_maximum(N_Const_ptr __x) _GLIBCXX_NOEXCEPT
		{
			while (__x->_M_right != 0)
				__x = __x->_M_right;
			return __x;
		}
	};

	ft::Node_base*			RBT_increment(ft::Node_base* __x) throw ();
	const ft::Node_base*	RBT_increment(const ft::Node_base* __x) throw ();

	ft::Node_base*			RBT_decrement(ft::Node_base* __x) throw ();
	const ft::Node_base*	RBT_decrement(const ft::Node_base* __x) throw ();

	unsigned int	RBT_black_count(const ft::Node_base* __node, const ft::Node_base* __root) throw ();

	void	RBT_rotate_left(ft::Node_base* const __x, ft::Node_base*& __root);
	void	RBT_rotate_right(ft::Node_base* const __x, ft::Node_base*& __root);

	void			RBT_insert_rebalance(const bool __insert_left, ft::Node_base* __x, ft::Node_base* __p, ft::Node_base& __header) throw ();
	ft::Node_base*	RBT_erase_rebalance(ft::Node_base* const __z, ft::Node_base& __header) throw ();

	// Helper type offering value initialization guarantee on the compare functor.
	template<typename _Key_compare>
	struct RBT_key_compare
	{
		_Key_compare	_M_key_compare;

		RBT_key_compare()
		_GLIBCXX_NOEXCEPT_IF(
		is_nothrow_default_constructible<_Key_compare>::value)
		: _M_key_compare()
		{ }

		RBT_key_compare(const _Key_compare& __comp)
		: _M_key_compare(__comp)
		{ }

	};

	// Helper type to manage default initialization of node count and header.
	struct RBT_header
	{
		Node_base	_M_header;
		std::size_t	_M_node_count; // Keeps track of size of tree.

		RBT_header() _GLIBCXX_NOEXCEPT
		{
			_M_header._M_color = RED;
			_M_reset();
		}

		void	_M_move_data(RBT_header& __from)
		{
			_M_header._M_color = __from._M_header._M_color;
			_M_header._M_parent = __from._M_header._M_parent;
			_M_header._M_left = __from._M_header._M_left;
			_M_header._M_right = __from._M_header._M_right;
			_M_header._M_parent->_M_parent = &_M_header;
			_M_node_count = __from._M_node_count;

			__from._M_reset();
		}

		void	_M_reset()
		{
			_M_header._M_parent = 0;
			_M_header._M_left = &_M_header;
			_M_header._M_right = &_M_header;
			_M_node_count = 0;
		}
	};

	template<typename _Val>
	struct RBT_Node : public Node_base
	{
		typedef RBT_Node<_Val>* _Link_type;

		_Val _M_value_field;

		_Val*	_M_valptr()
		{ return std::__addressof(_M_value_field); }

		const _Val*	_M_valptr() const
		{ return std::__addressof(_M_value_field); }
	};

	template<typename _Tp>
	struct RBT_iterator
	{
		typedef _Tp  value_type;
		typedef _Tp& reference;
		typedef _Tp* pointer;

		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t			 		difference_type;

		typedef RBT_iterator<_Tp>	_Self;
		typedef Node_base::N_ptr	N_ptr;
		typedef RBT_Node<_Tp>*		_Link_type;

		RBT_iterator() _GLIBCXX_NOEXCEPT
		: _M_node() { }

		explicit	RBT_iterator(N_ptr __x) _GLIBCXX_NOEXCEPT
		: _M_node(__x) { }

		reference	operator*() const _GLIBCXX_NOEXCEPT
		{ return *static_cast<_Link_type>(_M_node)->_M_valptr(); }

		pointer	operator->() const _GLIBCXX_NOEXCEPT
		{ return static_cast<_Link_type> (_M_node)->_M_valptr(); }

		_Self&	operator++() _GLIBCXX_NOEXCEPT
		{
			_M_node = RBT_increment(_M_node);
			return *this;
		}

		_Self	operator++(int) _GLIBCXX_NOEXCEPT
		{
			_Self __tmp = *this;
			_M_node = RBT_increment(_M_node);
			return __tmp;
		}

		_Self&	operator--() _GLIBCXX_NOEXCEPT
		{
			_M_node = RBT_decrement(_M_node);
			return *this;
		}

		_Self	operator--(int) _GLIBCXX_NOEXCEPT
		{
			_Self __tmp = *this;
			_M_node = RBT_decrement(_M_node);
			return __tmp;
		}

		friend bool	operator==(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
		{ return __x._M_node == __y._M_node; }

		friend bool
		operator!=(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
		{ return __x._M_node != __y._M_node; }

		N_ptr _M_node;
	};

	template<typename _Tp>
	struct RBT_const_iterator
	{
		typedef _Tp	 value_type;
		typedef const _Tp& reference;
		typedef const _Tp* pointer;

		typedef RBT_iterator<_Tp> iterator;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t			 difference_type;

		typedef RBT_const_iterator<_Tp>		_Self;
		typedef Node_base::N_Const_ptr	N_ptr;
		typedef const RBT_Node<_Tp>*			_Link_type;

		RBT_const_iterator() _GLIBCXX_NOEXCEPT
		: _M_node() { }

		explicit	RBT_const_iterator(N_ptr __x) _GLIBCXX_NOEXCEPT
		: _M_node(__x) { }

		RBT_const_iterator(const iterator& __it) _GLIBCXX_NOEXCEPT
		: _M_node(__it._M_node) { }

		iterator	_M_const_cast() const _GLIBCXX_NOEXCEPT
		{ return iterator(const_cast<typename iterator::N_ptr>(_M_node)); }

		reference	operator*() const _GLIBCXX_NOEXCEPT
		{ return *static_cast<_Link_type>(_M_node)->_M_valptr(); }

		pointer	operator->() const _GLIBCXX_NOEXCEPT
		{ return static_cast<_Link_type>(_M_node)->_M_valptr(); }

		_Self&	operator++() _GLIBCXX_NOEXCEPT
		{
			_M_node = RBT_increment(_M_node);
			return *this;
		}

		_Self	operator++(int) _GLIBCXX_NOEXCEPT
		{
			_Self __tmp = *this;
			_M_node = RBT_increment(_M_node);
			return __tmp;
		}

		_Self&	operator--() _GLIBCXX_NOEXCEPT
		{
			_M_node = RBT_decrement(_M_node);
			return *this;
		}

		_Self	operator--(int) _GLIBCXX_NOEXCEPT
		{
			_Self __tmp = *this;
			_M_node = RBT_decrement(_M_node);
			return __tmp;
		}

		friend bool	operator==(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
		{ return __x._M_node == __y._M_node; }

		friend bool
		operator!=(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
		{ return __x._M_node != __y._M_node; }

		N_ptr _M_node;
	};

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc = std::allocator<_Val> >
	class _Rb_tree
	{
		typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
		rebind<RBT_Node<_Val> >::other _Node_allocator;

		typedef __gnu_cxx::__alloc_traits<_Node_allocator> _Alloc_traits;

		protected:
		typedef Node_base* 		N_ptr;
		typedef const Node_base* 	N_Const_ptr;
		typedef RBT_Node<_Val>* 		_Link_type;
		typedef const RBT_Node<_Val>*	_Const_Link_type;

	private:
		// Functor recycling a pool of nodes and using allocation once the pool
		// is empty.
		struct ReuseAlloc_node
		{
			ReuseAlloc_node(_Rb_tree& __t)
			: _M_root(__t._M_root()), _M_nodes(__t._M_rightmost()), _M_t(__t)
			{
				if (_M_root)
				{
					_M_root->_M_parent = 0;

					if (_M_nodes->_M_left)
						_M_nodes = _M_nodes->_M_left;
				}
				else
					_M_nodes = 0;
			}

			~ReuseAlloc_node()
			{ _M_t._M_erase(static_cast<_Link_type>(_M_root)); }

			template<typename _Arg>
			_Link_type	operator()(const _Arg& __arg)
			{
				_Link_type __node = static_cast<_Link_type>(_M_extract());
				if (__node)
				{
					_M_t._M_destroy_node(__node);
					_M_t._M_construct_node(__node, _GLIBCXX_FORWARD(_Arg, __arg));
					return __node;
				}
				return _M_t._M_create_node(_GLIBCXX_FORWARD(_Arg, __arg));
			}

		private:
			N_ptr	_M_extract()
			{
				if (!_M_nodes)
					return _M_nodes;
				N_ptr __node = _M_nodes;
				_M_nodes = _M_nodes->_M_parent;
				if (_M_nodes)
				{
					if (_M_nodes->_M_right == __node)
					{
						_M_nodes->_M_right = 0;

						if (_M_nodes->_M_left)
						{
							_M_nodes = _M_nodes->_M_left;

							while (_M_nodes->_M_right)
							_M_nodes = _M_nodes->_M_right;

							if (_M_nodes->_M_left)
							_M_nodes = _M_nodes->_M_left;
						}
					}
					else // __node is on the left.
						_M_nodes->_M_left = 0;
				}
				else
					_M_root = 0;
				return __node;
			}

			N_ptr _M_root;
			N_ptr _M_nodes;
			_Rb_tree& _M_t;
		};

		// Functor similar to the previous one but without any pool of nodes to
		// recycle.
		struct Alloc_node
		{
			Alloc_node(_Rb_tree& __t) : _M_t(__t) { }

			template<typename _Arg>
			_Link_type	operator()(const _Arg& __arg) const
			{ return _M_t._M_create_node(_GLIBCXX_FORWARD(_Arg, __arg)); }

			private:
			_Rb_tree&	_M_t;
		};

	public:
		typedef _Key 				key_type;
		typedef _Val 				value_type;
		typedef value_type* 		pointer;
		typedef const value_type* 	const_pointer;
		typedef value_type& 		reference;
		typedef const value_type& 	const_reference;
		typedef size_t 				size_type;
		typedef std::ptrdiff_t 			difference_type;
		typedef _Alloc 				allocator_type;

		_Node_allocator&	_M_get_Node_allocator() _GLIBCXX_NOEXCEPT
		{ return this->_M_impl; }

		const _Node_allocator&	_M_get_Node_allocator() const _GLIBCXX_NOEXCEPT
		{ return this->_M_impl; }

		allocator_type	get_allocator() const _GLIBCXX_NOEXCEPT
		{ return allocator_type(_M_get_Node_allocator()); }

	protected:
		_Link_type	_M_get_node()
		{ return _Alloc_traits::allocate(_M_get_Node_allocator(), 1); }

		void	_M_put_node(_Link_type __p) _GLIBCXX_NOEXCEPT
		{ _Alloc_traits::deallocate(_M_get_Node_allocator(), __p, 1); }

		void	_M_construct_node(_Link_type __node, const value_type& __x)
		{
			__try
				{ get_allocator().construct(__node->_M_valptr(), __x); }
			__catch(...)
			{
				_M_put_node(__node);
				__throw_exception_again;
			}
		}

		_Link_type	_M_create_node(const value_type& __x)
		{
			_Link_type __tmp = _M_get_node();
			_M_construct_node(__tmp, __x);
			return __tmp;
		}
		
		void	_M_destroy_node(_Link_type __p) _GLIBCXX_NOEXCEPT
		{
			get_allocator().destroy(__p->_M_valptr());
		}

		void	_M_drop_node(_Link_type __p) _GLIBCXX_NOEXCEPT
		{
			_M_destroy_node(__p);
			_M_put_node(__p);
		}

		template<typename _NodeGen>
		_Link_type	_M_clone_node(_Const_Link_type __x, _NodeGen& __node_gen)
		{
			_Link_type __tmp = __node_gen(*__x->_M_valptr());
			__tmp->_M_color = __x->_M_color;
			__tmp->_M_left = 0;
			__tmp->_M_right = 0;
			return __tmp;
		}

	protected:
		// Unused _Is_pod_comparator is kept as it is part of mangled name.
		template<typename _Key_compare>
		struct RBT_impl : public _Node_allocator
			, public RBT_key_compare<_Key_compare>, public RBT_header
		{
			typedef RBT_key_compare<_Key_compare> _Base_key_compare;

			RBT_impl()
				_GLIBCXX_NOEXCEPT_IF(
				is_nothrow_default_constructible<_Node_allocator>::value
				&& is_nothrow_default_constructible<_Base_key_compare>::value )
			: _Node_allocator()
			{ }

			RBT_impl(const RBT_impl& __x)
			: _Node_allocator(_Alloc_traits::_S_select_on_copy(__x))
			, _Base_key_compare(__x._M_key_compare)
			{ }

			RBT_impl(const _Key_compare& __comp, const _Node_allocator& __a)
			: _Node_allocator(__a), _Base_key_compare(__comp)
			{ }
		};

		RBT_impl<_Compare> _M_impl;

	protected:
		N_ptr&	_M_root() _GLIBCXX_NOEXCEPT
		{ return this->_M_impl._M_header._M_parent; }

		N_Const_ptr	_M_root() const _GLIBCXX_NOEXCEPT
		{ return this->_M_impl._M_header._M_parent; }

		N_ptr&	_M_leftmost() _GLIBCXX_NOEXCEPT
		{ return this->_M_impl._M_header._M_left; }

		N_Const_ptr	_M_leftmost() const _GLIBCXX_NOEXCEPT
		{ return this->_M_impl._M_header._M_left; }

		N_ptr&	_M_rightmost() _GLIBCXX_NOEXCEPT
		{ return this->_M_impl._M_header._M_right; }

		N_Const_ptr	_M_rightmost() const _GLIBCXX_NOEXCEPT
		{ return this->_M_impl._M_header._M_right; }

		_Link_type	_M_begin() _GLIBCXX_NOEXCEPT
		{ return static_cast<_Link_type>(this->_M_impl._M_header._M_parent); }

		_Const_Link_type	_M_begin() const _GLIBCXX_NOEXCEPT
		{ return static_cast<_Const_Link_type>(this->_M_impl._M_header._M_parent); }

		N_ptr	_M_end() _GLIBCXX_NOEXCEPT
		{ return &this->_M_impl._M_header; }

		N_Const_ptr	_M_end() const _GLIBCXX_NOEXCEPT
		{ return &this->_M_impl._M_header; }

		static const _Key&	_S_key(_Const_Link_type __x)
		{ return _KeyOfValue()(*__x->_M_valptr()); }

		static _Link_type	_S_left(N_ptr __x) _GLIBCXX_NOEXCEPT
		{ return static_cast<_Link_type>(__x->_M_left); }

		static _Const_Link_type	_S_left(N_Const_ptr __x) _GLIBCXX_NOEXCEPT
		{ return static_cast<_Const_Link_type>(__x->_M_left); }

		static _Link_type	_S_right(N_ptr __x) _GLIBCXX_NOEXCEPT
		{ return static_cast<_Link_type>(__x->_M_right); }

		static _Const_Link_type	_S_right(N_Const_ptr __x) _GLIBCXX_NOEXCEPT
		{ return static_cast<_Const_Link_type>(__x->_M_right); }

		static const _Key&	_S_key(N_Const_ptr __x)
		{ return _S_key(static_cast<_Const_Link_type>(__x)); }

		static N_ptr	_S_minimum(N_ptr __x) _GLIBCXX_NOEXCEPT
		{ return Node_base::_S_minimum(__x); }

		static N_Const_ptr	_S_minimum(N_Const_ptr __x) _GLIBCXX_NOEXCEPT
		{ return Node_base::_S_minimum(__x); }

		static N_ptr	_S_maximum(N_ptr __x) _GLIBCXX_NOEXCEPT
		{ return Node_base::_S_maximum(__x); }

		static N_Const_ptr	_S_maximum(N_Const_ptr __x) _GLIBCXX_NOEXCEPT
		{ return Node_base::_S_maximum(__x); }

	public:
		typedef RBT_iterator<value_type>       iterator;
		typedef RBT_const_iterator<value_type> const_iterator;

		typedef std::reverse_iterator<iterator>       reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		pair<N_ptr, N_ptr>	_M_get_insert_unique_pos(const key_type& __k);

		pair<N_ptr, N_ptr>	_M_get_insert_equal_pos(const key_type& __k);

		pair<N_ptr, N_ptr>	_M_get_insert_hint_unique_pos(
			const_iterator __pos,
			const key_type& __k);

		pair<N_ptr, N_ptr>	_M_get_insert_hint_equal_pos(
			const_iterator __pos,
			const key_type& __k);

	private:
		template<typename _NodeGen>
		iterator	_M_insert_(N_ptr __x, N_ptr __y,
			const value_type& __v, _NodeGen&);

		// _GLIBCXX_RESOLVE_LIB_DEFECTS
		// 233. Insertion hints in associative containers.
		iterator	_M_insert_lower(N_ptr __y, const value_type& __v);

		iterator	_M_insert_equal_lower(const value_type& __x);

		template<typename _NodeGen>
		_Link_type	_M_copy(_Const_Link_type __x, N_ptr __p, _NodeGen&);

		template<typename _NodeGen>
		_Link_type	_M_copy(const _Rb_tree& __x, _NodeGen& __gen)
		{
			_Link_type __root = _M_copy(__x._M_begin(), _M_end(), __gen);
			_M_leftmost() = _S_minimum(__root);
			_M_rightmost() = _S_maximum(__root);
			_M_impl._M_node_count = __x._M_impl._M_node_count;
			return __root;
		}

		_Link_type	_M_copy(const _Rb_tree& __x)
		{
			Alloc_node __an(*this);
			return _M_copy(__x, __an);
		}

		void	_M_erase(_Link_type __x);

		iterator	_M_lower_bound(_Link_type __x, N_ptr __y,
			const _Key& __k);

		const_iterator	_M_lower_bound(_Const_Link_type __x, N_Const_ptr __y,
			const _Key& __k) const;

		iterator	_M_upper_bound(_Link_type __x, N_ptr __y,
			const _Key& __k);

		const_iterator	_M_upper_bound(_Const_Link_type __x, N_Const_ptr __y,
			const _Key& __k) const;

	public:
		// allocation/deallocation
		_Rb_tree() { }

		_Rb_tree(const _Compare& __comp,
			const allocator_type& __a = allocator_type())
		: _M_impl(__comp, _Node_allocator(__a)) { }

		_Rb_tree(const _Rb_tree& __x)
		: _M_impl(__x._M_impl)
		{
			if (__x._M_root() != 0)
			_M_root() = _M_copy(__x);
		}

		~_Rb_tree() _GLIBCXX_NOEXCEPT
		{ _M_erase(_M_begin()); }

		_Rb_tree&	operator=(const _Rb_tree& __x);

		// Accessors.
		_Compare	key_comp() const
		{ return _M_impl._M_key_compare; }

		iterator	begin() _GLIBCXX_NOEXCEPT
		{ return iterator(this->_M_impl._M_header._M_left); }

		const_iterator	begin() const _GLIBCXX_NOEXCEPT
		{ return const_iterator(this->_M_impl._M_header._M_left); }

		iterator	end() _GLIBCXX_NOEXCEPT
		{ return iterator(&this->_M_impl._M_header); }

		const_iterator	end() const _GLIBCXX_NOEXCEPT
		{ return const_iterator(&this->_M_impl._M_header); }

		reverse_iterator	rbegin() _GLIBCXX_NOEXCEPT
		{ return reverse_iterator(end()); }

		const_reverse_iterator	rbegin() const _GLIBCXX_NOEXCEPT
		{ return const_reverse_iterator(end()); }

		reverse_iterator	rend() _GLIBCXX_NOEXCEPT
		{ return reverse_iterator(begin()); }

		const_reverse_iterator	rend() const _GLIBCXX_NOEXCEPT
		{ return const_reverse_iterator(begin()); }

		_GLIBCXX_NODISCARD bool	empty() const _GLIBCXX_NOEXCEPT
		{ return _M_impl._M_node_count == 0; }

		size_type	size() const _GLIBCXX_NOEXCEPT
		{ return _M_impl._M_node_count; }

		size_type	max_size() const _GLIBCXX_NOEXCEPT
		{ return _Alloc_traits::max_size(_M_get_Node_allocator()); }

		void	swap(_Rb_tree& __t)
		_GLIBCXX_NOEXCEPT_IF(__is_nothrow_swappable<_Compare>::value);

		// Insert/erase.

		pair<iterator, bool>	_M_insert_unique(const value_type& __x);

		iterator	_M_insert_equal(const value_type& __x);

		template<typename _NodeGen>
		iterator	_M_insert_unique_(const_iterator __pos, const value_type& __x, _NodeGen&);

		iterator	_M_insert_unique_(const_iterator __pos, const value_type& __x)
		{
			Alloc_node __an(*this);
			return _M_insert_unique_(__pos, __x, __an);
		}

		template<typename _NodeGen>
		iterator	_M_insert_equal_(const_iterator __pos, const value_type& __x,
			_NodeGen&);
		
		iterator	_M_insert_equal_(const_iterator __pos, const value_type& __x)
		{
			Alloc_node __an(*this);
			return _M_insert_equal_(__pos, __x, __an);
		}

		template<typename _InputIterator>
		void	_M_insert_range_unique(_InputIterator __first, _InputIterator __last)
		{
			Alloc_node __an(*this);
			for (; __first != __last; ++__first)
				_M_insert_unique_(end(), *__first, __an);
		}

		template<typename _InputIterator>
		void	_M_insert_range_equal(_InputIterator __first, _InputIterator __last)
		{
			Alloc_node __an(*this);
			for (; __first != __last; ++__first)
				_M_insert_equal_(end(), *__first, __an);
		}

	private:
		void	_M_erase_aux(const_iterator __position);

		void	_M_erase_aux(const_iterator __first, const_iterator __last);

	public:
		void	erase(iterator __position)
		{
			__glibcxx_assert(__position != end());
			_M_erase_aux(__position);
		}

		void	erase(const_iterator __position)
		{
			__glibcxx_assert(__position != end());
			_M_erase_aux(__position);
		}

		size_type	erase(const key_type& __x);

		void	erase(iterator __first, iterator __last)
		{ _M_erase_aux(__first, __last); }

		void	erase(const_iterator __first, const_iterator __last)
		{ _M_erase_aux(__first, __last); }

		void	clear() _GLIBCXX_NOEXCEPT
		{
			_M_erase(_M_begin());
			_M_impl._M_reset();
		}

		// Set operations.
		iterator	find(const key_type& __k);

		const_iterator	find(const key_type& __k) const;

		size_type	count(const key_type& __k) const;

		iterator	lower_bound(const key_type& __k)
		{ return _M_lower_bound(_M_begin(), _M_end(), __k); }

		const_iterator	lower_bound(const key_type& __k) const
		{ return _M_lower_bound(_M_begin(), _M_end(), __k); }

		iterator	upper_bound(const key_type& __k)
		{ return _M_upper_bound(_M_begin(), _M_end(), __k); }

		const_iterator	upper_bound(const key_type& __k) const
		{ return _M_upper_bound(_M_begin(), _M_end(), __k); }

		pair<iterator, iterator>	equal_range(const key_type& __k);

		pair<const_iterator, const_iterator>	equal_range(const key_type& __k) const;

		// Debugging.
		bool	__rb_verify() const;

		friend bool	operator==(const _Rb_tree& __x, const _Rb_tree& __y)
		{
			return (__x.size() == __y.size()
			&& std::equal(__x.begin(), __x.end(), __y.begin()));
		}

		friend bool
		operator<(const _Rb_tree& __x, const _Rb_tree& __y)
		{
			return std::lexicographical_compare(__x.begin(), __x.end(),
								__y.begin(), __y.end());
		}

		friend bool _GLIBCXX_DEPRECATED	operator!=(const _Rb_tree& __x, const _Rb_tree& __y)
		{ return !(__x == __y); }

		friend bool _GLIBCXX_DEPRECATED
		operator>(const _Rb_tree& __x, const _Rb_tree& __y)
		{ return __y < __x; }

		friend bool _GLIBCXX_DEPRECATED
		operator<=(const _Rb_tree& __x, const _Rb_tree& __y)
		{ return !(__y < __x); }

		friend bool _GLIBCXX_DEPRECATED
		operator>=(const _Rb_tree& __x, const _Rb_tree& __y)
		{ return !(__x < __y); }
	};

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	inline void	swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
	{ __x.swap(__y); }

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>&
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	operator=(const _Rb_tree& __x)
	{
		if (this != &__x)
		{
			// Note that _Key may be a constant type.
			ReuseAlloc_node __roan(*this);
			_M_impl._M_reset();
			_M_impl._M_key_compare = __x._M_impl._M_key_compare;
			if (__x._M_root() != 0)
				_M_root() = _M_copy(__x, __roan);
		}
		return *this;
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	template<typename _NodeGen>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_insert_(N_ptr __x, N_ptr __p, const _Val& __v, _NodeGen& __node_gen)
	{
		bool __insert_left = (__x != 0 || __p == _M_end()
			|| _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__p)));

		_Link_type __z = __node_gen(_GLIBCXX_FORWARD(_Arg, __v));

		RBT_insert_rebalance(__insert_left, __z, __p,
			this->_M_impl._M_header);
		++_M_impl._M_node_count;
		return iterator(__z);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_insert_lower(N_ptr __p, const _Val& __v)
	{
		bool __insert_left = (__p == _M_end()
			|| !_M_impl._M_key_compare(_S_key(__p), _KeyOfValue()(__v)));

		_Link_type __z = _M_create_node(_GLIBCXX_FORWARD(_Arg, __v));

		RBT_insert_rebalance(__insert_left, __z, __p,
			this->_M_impl._M_header);
		++_M_impl._M_node_count;
		return iterator(__z);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_insert_equal_lower(const _Val& __v)
	{
		_Link_type __x = _M_begin();
		N_ptr __y = _M_end();
		while (__x != 0)
		{
			__y = __x;
			__x = !_M_impl._M_key_compare(_S_key(__x), _KeyOfValue()(__v)) ?
				_S_left(__x) : _S_right(__x);
		}
		return _M_insert_lower(__y, _GLIBCXX_FORWARD(_Arg, __v));
	}

	template<typename _Key, typename _Val, typename _KoV,
	typename _Compare, typename _Alloc>
	template<typename _NodeGen>
	typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::_Link_type
	_Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::
	_M_copy(_Const_Link_type __x, N_ptr __p, _NodeGen& __node_gen)
	{
	// Structural copy. __x and __p must be non-null.
		_Link_type __top = _M_clone_node(__x, __node_gen);
		__top->_M_parent = __p;

		__try
		{
			if (__x->_M_right)
			__top->_M_right = _M_copy(_S_right(__x), __top, __node_gen);
			__p = __top;
			__x = _S_left(__x);

			while (__x != 0)
			{
			_Link_type __y = _M_clone_node(__x, __node_gen);
			__p->_M_left = __y;
			__y->_M_parent = __p;
			if (__x->_M_right)
			__y->_M_right = _M_copy(_S_right(__x), __y, __node_gen);
			__p = __y;
			__x = _S_left(__x);
			}
		}
		__catch(...)
		{
			_M_erase(__top);
			__throw_exception_again;
		}
		return __top;
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	void	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_erase(_Link_type __x)
	{
		// Erase without rebalancing.
		while (__x != 0)
		{
			_M_erase(_S_right(__x));
			_Link_type __y = _S_left(__x);
			_M_drop_node(__x);
			__x = __y;
		}
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_lower_bound(_Link_type __x, N_ptr __y, const _Key& __k)
	{
		while (__x != 0)
		{
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);
		}
		return iterator(__y);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_lower_bound(_Const_Link_type __x, N_Const_ptr __y,
		const _Key& __k) const
	{
		while (__x != 0)
		{
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
			{
				__y = __x;
				__x = _S_left(__x);
			}
			else
				__x = _S_right(__x);
		}
		return const_iterator(__y);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_upper_bound(_Link_type __x, N_ptr __y,
		const _Key& __k)
	{
		while (__x != 0)
		{
			if (_M_impl._M_key_compare(__k, _S_key(__x)))
			{
				__y = __x;
				__x = _S_left(__x);
			}
			else
				__x = _S_right(__x);
		}
		return iterator(__y);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_upper_bound(_Const_Link_type __x, N_Const_ptr __y,
		const _Key& __k) const
	{
		while (__x != 0)
		{
			if (_M_impl._M_key_compare(__k, _S_key(__x)))
			{
				__y = __x;
				__x = _S_left(__x);
			}
			else
				__x = _S_right(__x);
		}
		return const_iterator(__y);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator,
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	equal_range(const _Key& __k)
	{
		_Link_type __x = _M_begin();
		N_ptr __y = _M_end();
		while (__x != 0)
		{
			if (_M_impl._M_key_compare(_S_key(__x), __k))
				__x = _S_right(__x);
			else if (_M_impl._M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
			{
				_Link_type __xu(__x);
				N_ptr __yu(__y);
				__y = __x, __x = _S_left(__x);
				__xu = _S_right(__xu);
				return (pair<iterator, iterator>(_M_lower_bound(__x, __y, __k),
					_M_upper_bound(__xu, __yu, __k)));
			}
		}
		return pair<iterator, iterator>(iterator(__y), iterator(__y));
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator,
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	equal_range(const _Key& __k) const
	{
		_Const_Link_type __x = _M_begin();
		N_Const_ptr __y = _M_end();
		while (__x != 0)
		{
		if (_M_impl._M_key_compare(_S_key(__x), __k))
			__x = _S_right(__x);
		else if (_M_impl._M_key_compare(__k, _S_key(__x)))
			__y = __x, __x = _S_left(__x);
		else
			{
			_Const_Link_type __xu(__x);
			N_Const_ptr __yu(__y);
			__y = __x, __x = _S_left(__x);
			__xu = _S_right(__xu);
			return pair<const_iterator,
				const_iterator>(_M_lower_bound(__x, __y, __k),
						_M_upper_bound(__xu, __yu, __k));
			}
		}
		return pair<const_iterator, const_iterator>(const_iterator(__y),
							const_iterator(__y));
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	void	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	swap(_Rb_tree& __t) _GLIBCXX_NOEXCEPT_IF(__is_nothrow_swappable<_Compare>::value)
	{
		if (_M_root() == 0)
		{
			if (__t._M_root() != 0)
				_M_impl._M_move_data(__t._M_impl);
		}
		else if (__t._M_root() == 0)
			__t._M_impl._M_move_data(_M_impl);
		else
		{
			std::swap(_M_root(),__t._M_root());
			std::swap(_M_leftmost(),__t._M_leftmost());
			std::swap(_M_rightmost(),__t._M_rightmost());
			_M_root()->_M_parent = _M_end();
			__t._M_root()->_M_parent = __t._M_end();
			std::swap(this->_M_impl._M_node_count, __t._M_impl._M_node_count);
		}
		// No need to swap header's color as it does not change.
		std::swap(this->_M_impl._M_key_compare, __t._M_impl._M_key_compare);
		_Alloc_traits::_S_on_swap(_M_get_Node_allocator(), __t._M_get_Node_allocator());
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::N_ptr,
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::N_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_get_insert_unique_pos(const key_type& __k)
	{
		typedef pair<N_ptr, N_ptr> _Res;
		_Link_type __x = _M_begin();
		N_ptr __y = _M_end();
		bool __comp = true;
		while (__x != 0)
		{
			__y = __x;
			__comp = _M_impl._M_key_compare(__k, _S_key(__x));
			__x = __comp ? _S_left(__x) : _S_right(__x);
		}
		iterator __j = iterator(__y);
		if (__comp)
		{
			if (__j == begin())
				return _Res(__x, __y);
			else
				--__j;
		}
		if (_M_impl._M_key_compare(_S_key(__j._M_node), __k))
			return _Res(__x, __y);
		return _Res(__j._M_node, 0);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::N_ptr,
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::N_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_get_insert_equal_pos(const key_type& __k)
	{
		typedef pair<N_ptr, N_ptr> _Res;
		_Link_type __x = _M_begin();
		N_ptr __y = _M_end();
		while (__x != 0)
		{
			__y = __x;
			__x = _M_impl._M_key_compare(__k, _S_key(__x)) ?
				_S_left(__x) : _S_right(__x);
		}
		return _Res(__x, __y);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator, bool>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_insert_unique(const _Val& __v)
	{
		typedef pair<iterator, bool> _Res;
		pair<N_ptr, N_ptr> __res
			= _M_get_insert_unique_pos(_KeyOfValue()(__v));
		if (__res.second)
		{
			Alloc_node __an(*this);
			return _Res(_M_insert_(__res.first, __res.second,
				_GLIBCXX_FORWARD(_Arg, __v), __an), true);
		}
		return _Res(iterator(__res.first), false);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_insert_equal(const _Val& __v)
	{
		pair<N_ptr, N_ptr> __res = _M_get_insert_equal_pos(_KeyOfValue()(__v));
		Alloc_node __an(*this);
		return _M_insert_(__res.first, __res.second, _GLIBCXX_FORWARD(_Arg, __v), __an);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::N_ptr,
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::N_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_get_insert_hint_unique_pos(const_iterator __position, const key_type& __k)
	{
		iterator __pos = __position._M_const_cast();
		typedef pair<N_ptr, N_ptr> _Res;
		// end()
		if (__pos._M_node == _M_end())
		{
			if (size() > 0 && _M_impl._M_key_compare(_S_key(_M_rightmost()), __k))
				return _Res(0, _M_rightmost());
			else
				return _M_get_insert_unique_pos(__k);
		}
		else if (_M_impl._M_key_compare(__k, _S_key(__pos._M_node)))
		{
			// First, try before...
			iterator __before = __pos;
			if (__pos._M_node == _M_leftmost()) // begin()
				return _Res(_M_leftmost(), _M_leftmost());
			else if (_M_impl._M_key_compare(_S_key((--__before)._M_node), __k))
			{
				if (_S_right(__before._M_node) == 0)
					return _Res(0, __before._M_node);
				else
					return _Res(__pos._M_node, __pos._M_node);
			}
			else
				return _M_get_insert_unique_pos(__k);
		}
		else if (_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
		{
			// ... then try after.
			iterator __after = __pos;
			if (__pos._M_node == _M_rightmost())
				return _Res(0, _M_rightmost());
			else if (_M_impl._M_key_compare(__k, _S_key((++__after)._M_node)))
			{
				if (_S_right(__pos._M_node) == 0)
					return _Res(0, __pos._M_node);
				else
					return _Res(__after._M_node, __after._M_node);
			}
			else
				return _M_get_insert_unique_pos(__k);
		}
		else
			return _Res(__pos._M_node, 0);
		// Equivalent keys.
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	template<typename _NodeGen>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_insert_unique_(const_iterator __position, const _Val& __v, _NodeGen& __node_gen)
	{
		pair<N_ptr, N_ptr> __res
			= _M_get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));
		if (__res.second)
			return _M_insert_(__res.first, __res.second, __v, __node_gen);
		return iterator(__res.first);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::N_ptr,
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::N_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_get_insert_hint_equal_pos(const_iterator __position, const key_type& __k)
	{
		iterator __pos = __position._M_const_cast();
		typedef pair<N_ptr, N_ptr> _Res;

		// end()
		if (__pos._M_node == _M_end())
		{
			if (size() > 0 && !_M_impl._M_key_compare(__k, _S_key(_M_rightmost())))
				return _Res(0, _M_rightmost());
			else
				return _M_get_insert_equal_pos(__k);
		}
		else if (!_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
		{
		// First, try before...
			iterator __before = __pos;
			if (__pos._M_node == _M_leftmost()) // begin()
				return _Res(_M_leftmost(), _M_leftmost());
			else if (!_M_impl._M_key_compare(__k, _S_key((--__before)._M_node)))
			{
				if (_S_right(__before._M_node) == 0)
					return _Res(0, __before._M_node);
				else
					return _Res(__pos._M_node, __pos._M_node);
			}
			else
				return _M_get_insert_equal_pos(__k);
		}
		else
		{
			// ... then try after.
			iterator __after = __pos;
			if (__pos._M_node == _M_rightmost())
				return _Res(0, _M_rightmost());
			else if (!_M_impl._M_key_compare(_S_key((++__after)._M_node), __k))
			{
				if (_S_right(__pos._M_node) == 0)
					return _Res(0, __pos._M_node);
				else
					return _Res(__after._M_node, __after._M_node);
			}
			else
				return _Res(0, 0);
		}
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	template<typename _NodeGen>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_insert_equal_(const_iterator __position, const _Val& __v, _NodeGen& __node_gen)
	{
		pair<N_ptr, N_ptr> __res = _M_get_insert_hint_equal_pos(__position, _KeyOfValue()(__v));
		if (__res.second)
			return _M_insert_(__res.first, __res.second, __v, __node_gen);
		return _M_insert_equal_lower(__v);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	void	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_erase_aux(const_iterator __position)
	{
		_Link_type __y = static_cast<_Link_type>(RBT_erase_rebalance(const_cast<N_ptr>(__position._M_node), this->_M_impl._M_header));
		_M_drop_node(__y);
		--_M_impl._M_node_count;
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	void	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	_M_erase_aux(const_iterator __first, const_iterator __last)
	{
		if (__first == begin() && __last == end())
			clear();
		else
			while (__first != __last)
				_M_erase_aux(__first++);
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	erase(const _Key& __x)
	{
		pair<iterator, iterator> __p = equal_range(__x);
		const size_type __old_size = size();
		_M_erase_aux(__p.first, __p.second);
		return __old_size - size();
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	find(const _Key& __k)
	{
		iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
		return (__j == end()
			|| _M_impl._M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	find(const _Key& __k) const
	{
		const_iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
		return (__j == end()
			|| _M_impl._M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	count(const _Key& __k) const
	{
		pair<const_iterator, const_iterator> __p = equal_range(__k);
		const size_type __n = std::distance(__p.first, __p.second);
		return __n;
	}

	template<typename _Key, typename _Val, typename _KeyOfValue,
	typename _Compare, typename _Alloc>
	bool	_Rb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::__rb_verify() const
	{
		if (_M_impl._M_node_count == 0 || begin() == end())
			return (_M_impl._M_node_count == 0 && begin() == end()
				&& this->_M_impl._M_header._M_left == _M_end()
				&& this->_M_impl._M_header._M_right == _M_end());
		unsigned int __len = RBT_black_count(_M_leftmost(), _M_root());
		for (const_iterator __it = begin(); __it != end(); ++__it)
		{
			_Const_Link_type __x = static_cast<_Const_Link_type>(__it._M_node);
			_Const_Link_type __L = _S_left(__x);
			_Const_Link_type __R = _S_right(__x);
			if (__x->_M_color == RED)
				if ((__L && __L->_M_color == RED) || (__R && __R->_M_color == RED))
					return false;
			if (__L && _M_impl._M_key_compare(_S_key(__x), _S_key(__L)))
				return false;
			if (__R && _M_impl._M_key_compare(_S_key(__R), _S_key(__x)))
				return false;
			if (!__L && !__R && RBT_black_count(__x, _M_root()) != __len)
				return false;
		}
		if (_M_leftmost() != Node_base::_S_minimum(_M_root()))
			return false;
		if (_M_rightmost() != Node_base::_S_maximum(_M_root()))
			return false;
		return true;
	}

} // namespace

#endif