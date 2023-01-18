#ifndef _FT_TREE_H
#define _FT_TREE_H

#include <iostream>
#include "utility.hpp"
#include "pair.hpp"

namespace ft
{
	enum RBT_color
	{
		RED = false,
		BLACK = true
	};

	class Node_base
	{
	public:
		typedef Node_base *Nb_ptr;
		typedef const Node_base *Nb_Const_ptr;

		RBT_color _color;
		Nb_ptr _parent;
		Nb_ptr _left;
		Nb_ptr _right;

		static Nb_ptr _S_minimum(Nb_ptr __x)
		{
			while (__x->_left != 0)
				__x = __x->_left;
			return __x;
		}

		static Nb_Const_ptr _S_minimum(Nb_Const_ptr __x)
		{
			while (__x->_left != 0)
				__x = __x->_left;
			return __x;
		}

		static Nb_ptr _S_maximum(Nb_ptr __x)
		{
			while (__x->_right != 0)
				__x = __x->_right;
			return __x;
		}

		static Nb_Const_ptr _S_maximum(Nb_Const_ptr __x)
		{
			while (__x->_right != 0)
				__x = __x->_right;
			return __x;
		}
	};

	ft::Node_base *RBT_increment(ft::Node_base *__x) throw();
	const ft::Node_base *RBT_increment(const ft::Node_base *__x) throw();

	ft::Node_base *RBT_decrement(ft::Node_base *__x) throw();
	const ft::Node_base *RBT_decrement(const ft::Node_base *__x) throw();

	unsigned int RBT_black_count(const ft::Node_base *__node, const ft::Node_base *__root) throw();

	void RBT_rotate_left(ft::Node_base *const __x, ft::Node_base *&__root);
	void RBT_rotate_right(ft::Node_base *const __x, ft::Node_base *&__root);

	void RBT_insert_rebalance(const bool __insert_left, ft::Node_base *__x, ft::Node_base *__p, ft::Node_base &__header) throw();
	ft::Node_base *RBT_erase_rebalance(ft::Node_base *const __z, ft::Node_base &__header) throw();

	// Helper type offering value initialization guarantee on the compare functor.
	template <typename _Key_compare>
	class RBT_key_compare
	{
	public:
		_Key_compare key_comp;

		RBT_key_compare() : key_comp() {}

		RBT_key_compare(const _Key_compare &__comp)
			: key_comp(__comp) {}
	};

	// Helper type to manage default initialization of node count and header.
	class RBT_header
	{
	public:
		Node_base _header;
		std::size_t _node_count; // Keeps track of size of tree.

		RBT_header()
		{
			_header._color = RED;
			_M_reset();
		}

		void _M_move_data(RBT_header &__from)
		{
			_header._color = __from._header._color;
			_header._parent = __from._header._parent;
			_header._left = __from._header._left;
			_header._right = __from._header._right;
			_header._parent->_parent = &_header;
			_node_count = __from._node_count;

			__from._M_reset();
		}

		void _M_reset()
		{
			_header._parent = 0;
			_header._left = &_header;
			_header._right = &_header;
			_node_count = 0;
		}
	};

	template <typename _Val>
	struct RBT_Node : public Node_base
	{
		typedef RBT_Node<_Val> *Node_ptr;

		_Val value;

		_Val *_M_valptr()
		{
			return std::__addressof(value);
		}

		const _Val *_M_valptr() const
		{
			return std::__addressof(value);
		}
	};

	template <typename _Tp>
	class RBT_iterator
	{
	public:
		typedef _Tp value_type;
		typedef _Tp &reference;
		typedef _Tp *pointer;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef RBT_iterator<_Tp> _Self;
		typedef Node_base::Nb_ptr Nb_ptr;
		typedef RBT_Node<_Tp> *Node_ptr;

		RBT_iterator()
			: _Node() {}

		explicit RBT_iterator(Nb_ptr __x)
			: _Node(__x) {}

		reference operator*() const
		{
			return *static_cast<Node_ptr>(_Node)->_M_valptr();
		}

		pointer operator->() const
		{
			return static_cast<Node_ptr>(_Node)->_M_valptr();
		}

		_Self &operator++()
		{
			_Node = RBT_increment(_Node);
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_Node = RBT_increment(_Node);
			return __tmp;
		}

		_Self &operator--()
		{
			_Node = RBT_decrement(_Node);
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			_Node = RBT_decrement(_Node);
			return __tmp;
		}

		friend bool operator==(const _Self &__x, const _Self &__y)
		{
			return __x._Node == __y._Node;
		}

		friend bool
		operator!=(const _Self &__x, const _Self &__y)
		{
			return __x._Node != __y._Node;
		}

		Nb_ptr _Node;
	};

	template <typename _Tp>
	class RBT_const_iterator
	{
	public:
		typedef _Tp value_type;
		typedef const _Tp &reference;
		typedef const _Tp *pointer;

		typedef RBT_iterator<_Tp> iterator;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef RBT_const_iterator<_Tp> _Self;
		typedef Node_base::Nb_Const_ptr Nb_ptr;
		typedef const RBT_Node<_Tp> *Node_ptr;

		RBT_const_iterator()
			: _Node() {}

		explicit RBT_const_iterator(Nb_ptr __x)
			: _Node(__x) {}

		RBT_const_iterator(const iterator &__it)
			: _Node(__it._Node) {}

		iterator _M_const_cast() const
		{
			return iterator(const_cast<typename iterator::Nb_ptr>(_Node));
		}

		reference operator*() const
		{
			return *static_cast<Node_ptr>(_Node)->_M_valptr();
		}

		pointer operator->() const
		{
			return static_cast<Node_ptr>(_Node)->_M_valptr();
		}

		_Self &operator++()
		{
			_Node = RBT_increment(_Node);
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_Node = RBT_increment(_Node);
			return __tmp;
		}

		_Self &operator--()
		{
			_Node = RBT_decrement(_Node);
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			_Node = RBT_decrement(_Node);
			return __tmp;
		}

		friend bool operator==(const _Self &__x, const _Self &__y)
		{
			return __x._Node == __y._Node;
		}

		friend bool
		operator!=(const _Self &__x, const _Self &__y)
		{
			return __x._Node != __y._Node;
		}

		Nb_ptr _Node;
	};

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc = std::allocator<_Val> >
	class _Rb_tree
	{
	private:
		typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template rebind<RBT_Node<_Val> >::other _Node_allocator;

		typedef __gnu_cxx::__alloc_traits<_Node_allocator> _Alloc_traits;

	protected:
		typedef Node_base *Nb_ptr;
		typedef const Node_base *Nb_Const_ptr;
		typedef RBT_Node<_Val> *Node_ptr;
		typedef const RBT_Node<_Val> *Const_Node_ptr;

		// Functor recycling a pool of nodes and using allocation once the pool
		// is empty.
		struct ReuseAlloc_node
		{
			ReuseAlloc_node(_Rb_tree &__t)
				: _M_root(__t._M_root()), _Nodes(__t._rightmost()), _M_t(__t)
			{
				if (_M_root)
				{
					_M_root->_parent = 0;

					if (_Nodes->_left)
						_Nodes = _Nodes->_left;
				}
				else
					_Nodes = 0;
			}

			~ReuseAlloc_node()
			{
				_M_t._M_erase(static_cast<Node_ptr>(_M_root));
			}

			template <typename _Arg>
			Node_ptr operator()(const _Arg &__arg)
			{
				Node_ptr __node = static_cast<Node_ptr>(_M_extract());
				if (__node)
				{
					_M_t._M_destroy_node(__node);
					_M_t._M_construct_node(__node, __arg);
					return __node;
				}
				return _M_t._M_create_node(__arg);
			}

			Nb_ptr _M_extract()
			{
				if (!_Nodes)
					return _Nodes;
				Nb_ptr __node = _Nodes;
				_Nodes = _Nodes->_parent;
				if (_Nodes)
				{
					if (_Nodes->_right == __node)
					{
						_Nodes->_right = 0;

						if (_Nodes->_left)
						{
							_Nodes = _Nodes->_left;

							while (_Nodes->_right)
								_Nodes = _Nodes->_right;

							if (_Nodes->_left)
								_Nodes = _Nodes->_left;
						}
					}
					else // __node is on the left.
						_Nodes->_left = 0;
				}
				else
					_M_root = 0;
				return __node;
			}

			Nb_ptr _M_root;
			Nb_ptr _Nodes;
			_Rb_tree &_M_t;
		};

		// Functor similar to the previous one but without any pool of nodes to
		// recycle.
		struct Alloc_node
		{
			Alloc_node(_Rb_tree &__t) : _M_t(__t) {}

			template <typename _Arg>
			Node_ptr operator()(const _Arg &__arg) const
			{
				return _M_t._M_create_node(__arg);
			}

		private:
			_Rb_tree &_M_t;
		};

	public:
		typedef _Key key_type;
		typedef _Val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef _Alloc allocator_type;

		_Node_allocator &Get_Node_allocator()
		{
			return this->_M_impl;
		}

		const _Node_allocator &Get_Node_allocator() const
		{
			return this->_M_impl;
		}

		allocator_type get_allocator() const
		{
			return allocator_type(Get_Node_allocator());
		}

	protected:
		Node_ptr _M_get_node()
		{
			return _Alloc_traits::allocate(Get_Node_allocator(), 1);
		}

		void Put_Node(Node_ptr __p)
		{
			if (__p)
			{
				_Alloc_traits::deallocate(Get_Node_allocator(), __p, 1);
				__p = NULL;
			}
		}

		void _M_construct_node(Node_ptr __node, const value_type &__x)
		{
			try
			{
				get_allocator().construct(__node->_M_valptr(), __x);
			}
			catch (const std::exception &e)
			{
				Put_Node(__node);
				throw ; //__throw_exception_again;
			}
		}

		Node_ptr _M_create_node(const value_type &__x)
		{
			Node_ptr __tmp = _M_get_node();
			_M_construct_node(__tmp, __x);
			return __tmp;
		}

		void _M_destroy_node(Node_ptr __p)
		{
			get_allocator().destroy(__p->_M_valptr());
		}

		void _M_drop_node(Node_ptr __p)
		{
			_M_destroy_node(__p);
			Put_Node(__p);
		}

		template <typename _NodeGen>
		Node_ptr _M_clone_node(Const_Node_ptr __x, _NodeGen &__node_gen)
		{
			Node_ptr __tmp = __node_gen(*__x->_M_valptr());
			__tmp->_color = __x->_color;
			__tmp->_left = 0;
			__tmp->_right = 0;
			return __tmp;
		}

		// Unused _Is_pod_comparator is kept as it is part of mangled name.
		template <typename _Key_compare>
		struct RBT_impl : public _Node_allocator, public RBT_key_compare<_Key_compare>, public RBT_header
		{
			typedef RBT_key_compare<_Key_compare> _Base_key_compare;

			RBT_impl() : _Node_allocator() {}

			RBT_impl(const RBT_impl &__x)
				: _Node_allocator(_Alloc_traits::_S_select_on_copy(__x)),
				_Base_key_compare(__x.key_comp) { }

			RBT_impl(const _Key_compare &__comp, const _Node_allocator &__a)
				: _Node_allocator(__a), _Base_key_compare(__comp) { }
		};

		RBT_impl<_Compare> _M_impl;

		Nb_ptr &_M_root()
		{ return this->_M_impl._header._parent; }

		Nb_Const_ptr _M_root() const
		{ return this->_M_impl._header._parent; }

		Nb_ptr &_leftmost()
		{ return this->_M_impl._header._left; }

		Nb_Const_ptr _leftmost() const
		{ return this->_M_impl._header._left; }

		Nb_ptr &_rightmost()
		{ return this->_M_impl._header._right; }

		Nb_Const_ptr _rightmost() const
		{ return this->_M_impl._header._right; }

		Node_ptr RBT_begin()
		{ return static_cast<Node_ptr>(this->_M_impl._header._parent); }

		Const_Node_ptr RBT_begin() const
		{ return static_cast<Const_Node_ptr>(this->_M_impl._header._parent); }

		Nb_ptr RBT_end()
		{ return &this->_M_impl._header; }

		Nb_Const_ptr RBT_end() const
		{ return &this->_M_impl._header; }

		static const _Key &_S_key(Const_Node_ptr __x)
		{ return _KeyOfValue()(*__x->_M_valptr()); }

		static Node_ptr _S_left(Nb_ptr __x)
		{ return static_cast<Node_ptr>(__x->_left); }

		static Const_Node_ptr _S_left(Nb_Const_ptr __x)
		{ return static_cast<Const_Node_ptr>(__x->_left); }

		static Node_ptr _S_right(Nb_ptr __x)
		{ return static_cast<Node_ptr>(__x->_right); }

		static Const_Node_ptr _S_right(Nb_Const_ptr __x)
		{ return static_cast<Const_Node_ptr>(__x->_right); }

		static const _Key &_S_key(Nb_Const_ptr __x)
		{ return _S_key(static_cast<Const_Node_ptr>(__x)); }

		static Nb_ptr _S_minimum(Nb_ptr __x)
		{ return Node_base::_S_minimum(__x); }

		static Nb_Const_ptr _S_minimum(Nb_Const_ptr __x)
		{ return Node_base::_S_minimum(__x); }

		static Nb_ptr _S_maximum(Nb_ptr __x)
		{ return Node_base::_S_maximum(__x); }

		static Nb_Const_ptr _S_maximum(Nb_Const_ptr __x)
		{ return Node_base::_S_maximum(__x); }

	public:
		typedef RBT_iterator<value_type> iterator;
		typedef RBT_const_iterator<value_type> const_iterator;

		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		pair<Nb_ptr, Nb_ptr> get_insert_unique_pos(const key_type &__k);

		pair<Nb_ptr, Nb_ptr> _M_get_insert_equal_pos(const key_type &__k);

		pair<Nb_ptr, Nb_ptr> _M_get_insert_hint_unique_pos(
			const_iterator __pos,
			const key_type &__k);

		pair<Nb_ptr, Nb_ptr> get_insert_hint_equal_pos(
			const_iterator __pos,
			const key_type &__k);

	private:
		template <typename _NodeGen>
		iterator _M_insert_(Nb_ptr __x, Nb_ptr __y,
			const value_type &__v, _NodeGen &);

		iterator RBT_insert_lower(Nb_ptr __y, const value_type &__v);

		iterator RBT_insert_equal_lower(const value_type &__x);

		template <typename _NodeGen>
		Node_ptr RBT_copy(Const_Node_ptr __x, Nb_ptr __p, _NodeGen &);

		template <typename _NodeGen>
		Node_ptr RBT_copy(const _Rb_tree &__x, _NodeGen &__gen)
		{
			Node_ptr __root = RBT_copy(__x.RBT_begin(), RBT_end(), __gen);
			_leftmost() = _S_minimum(__root);
			_rightmost() = _S_maximum(__root);
			_M_impl._node_count = __x._M_impl._node_count;
			return __root;
		}

		Node_ptr RBT_copy(const _Rb_tree &__x)
		{
			Alloc_node __an(*this);
			return RBT_copy(__x, __an);
		}

		void _M_erase(Node_ptr __x);

		iterator _M_lower_bound(Node_ptr __x, Nb_ptr __y, const _Key &__k);

		const_iterator _M_lower_bound(Const_Node_ptr __x, Nb_Const_ptr __y,
			const _Key &__k) const;

		iterator _M_upper_bound(Node_ptr __x, Nb_ptr __y, const _Key &__k);

		const_iterator _M_upper_bound(Const_Node_ptr __x, Nb_Const_ptr __y,
			const _Key &__k) const;

	public:
		_Rb_tree() {}

		_Rb_tree(const _Compare &__comp,
				 const allocator_type &__a = allocator_type())
			: _M_impl(__comp, _Node_allocator(__a)) {}

		_Rb_tree(const _Rb_tree &__x) : _M_impl(__x._M_impl)
		{
			if (__x._M_root() != 0)
				_M_root() = RBT_copy(__x);
		}

		~_Rb_tree()
		{
			_M_erase(RBT_begin());
		}

		_Rb_tree &operator=(const _Rb_tree &__x);

		_Compare key_comp() const
		{
			return _M_impl.key_comp;
		}

		iterator begin()
		{
			return iterator(this->_M_impl._header._left);
		}

		const_iterator begin() const
		{
			return const_iterator(this->_M_impl._header._left);
		}

		iterator end()
		{
			return iterator(&this->_M_impl._header);
		}

		const_iterator end() const
		{
			return const_iterator(&this->_M_impl._header);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		bool empty() const
		{
			return _M_impl._node_count == 0;
		}

		size_type size() const
		{
			return _M_impl._node_count;
		}

		size_type max_size() const
		{
			return _Alloc_traits::max_size(Get_Node_allocator());
		}

		void swap(_Rb_tree &__t);

		pair<iterator, bool> Insert_unique(const value_type &__x);

		iterator Insert_equal(const value_type &__x);

		template <typename _NodeGen>
		iterator Insert_unique_(const_iterator __pos, const value_type &__x, _NodeGen &);

		iterator Insert_unique_(const_iterator __pos, const value_type &__x)
		{
			Alloc_node __an(*this);
			return Insert_unique_(__pos, __x, __an);
		}

		template <typename _NodeGen>
		iterator Insert_equal_(const_iterator __pos, const value_type &__x, _NodeGen &);

		iterator Insert_equal_(const_iterator __pos, const value_type &__x)
		{
			Alloc_node __an(*this);
			return Insert_equal_(__pos, __x, __an);
		}

		template <typename _InputIterator>
		void Insert_range_unique(_InputIterator __first, _InputIterator __last)
		{
			Alloc_node __an(*this);
			for (; __first != __last; ++__first)
				Insert_unique_(end(), *__first, __an);
		}

		template <typename _InputIterator>
		void Insert_range_equal(_InputIterator __first, _InputIterator __last)
		{
			Alloc_node __an(*this);
			for (; __first != __last; ++__first)
				Insert_equal_(end(), *__first, __an);
		}

	private:
		void Erase_aux(const_iterator __position);

		void Erase_aux(const_iterator __first, const_iterator __last);

	public:
		void erase(iterator __position)
		{
			if (__position != end())
				Erase_aux(__position);
		}

		void erase(const_iterator __position)
		{
			if (__position != end())
				Erase_aux(__position);
		}

		size_type erase(const key_type &__x);

		void erase(iterator __first, iterator __last)
		{
			Erase_aux(__first, __last);
		}

		void erase(const_iterator __first, const_iterator __last)
		{
			Erase_aux(__first, __last);
		}

		void clear()
		{
			_M_erase(RBT_begin());
			_M_impl._M_reset();
		}

		// Set operations.
		iterator find(const key_type &__k);

		const_iterator find(const key_type &__k) const;

		size_type count(const key_type &__k) const;

		iterator lower_bound(const key_type &__k)
		{
			return _M_lower_bound(RBT_begin(), RBT_end(), __k);
		}

		const_iterator lower_bound(const key_type &__k) const
		{
			return _M_lower_bound(RBT_begin(), RBT_end(), __k);
		}

		iterator upper_bound(const key_type &__k)
		{
			return _M_upper_bound(RBT_begin(), RBT_end(), __k);
		}

		const_iterator upper_bound(const key_type &__k) const
		{
			return _M_upper_bound(RBT_begin(), RBT_end(), __k);
		}

		pair<iterator, iterator> equal_range(const key_type &__k);

		pair<const_iterator, const_iterator> equal_range(const key_type &__k) const;

		// Debugging.
		// bool	__rb_verify() const;

		friend bool operator<(const _Rb_tree &__x, const _Rb_tree &__y)
		{
			return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
		}

		friend bool operator==(const _Rb_tree &__x, const _Rb_tree &__y)
		{
			return (__x.size() == __y.size() && !(__x < __y) && !(__y < __x));
		}

		friend bool operator!=(const _Rb_tree &__x, const _Rb_tree &__y)
		{
			return !(__x == __y);
		}

		friend bool
		operator>(const _Rb_tree &__x, const _Rb_tree &__y)
		{
			return __y < __x;
		}

		friend bool
		operator<=(const _Rb_tree &__x, const _Rb_tree &__y)
		{
			return !(__y < __x);
		}

		friend bool
		operator>=(const _Rb_tree &__x, const _Rb_tree &__y)
		{
			return !(__x < __y);
		}
	};

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	inline void swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x,
					 _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
	{
		__x.swap(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
	operator=(const _Rb_tree &__x)
	{
		if (this != &__x)
		{
			// Note that _Key may be a constant type.
			ReuseAlloc_node __roan(*this);
			_M_impl._M_reset();
			_M_impl.key_comp = __x._M_impl.key_comp;
			if (__x._M_root() != 0)
				_M_root() = RBT_copy(__x, __roan);
		}
		return *this;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	template <typename _NodeGen>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_insert_(Nb_ptr __x, Nb_ptr __p, const _Val &__v, _NodeGen &__node_gen)
	{
		bool __insert_left = (__x != 0 || __p == RBT_end() || _M_impl.key_comp(_KeyOfValue()(__v), _S_key(__p)));

		Node_ptr __z = __node_gen(__v);

		RBT_insert_rebalance(__insert_left, __z, __p, this->_M_impl._header);
		++_M_impl._node_count;
		return iterator(__z);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		RBT_insert_lower(Nb_ptr __p, const _Val &__v)
	{
		bool __insert_left = (__p == RBT_end() || !_M_impl.key_comp(_S_key(__p), _KeyOfValue()(__v)));

		Node_ptr __z = _M_create_node(__v);

		RBT_insert_rebalance(__insert_left, __z, __p, this->_M_impl._header);
		++_M_impl._node_count;
		return iterator(__z);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		RBT_insert_equal_lower(const _Val &__v)
	{
		Node_ptr __x = RBT_begin();
		Nb_ptr __y = RBT_end();
		while (__x != 0)
		{
			__y = __x;
			__x = !_M_impl.key_comp(_S_key(__x), _KeyOfValue()(__v)) ? _S_left(__x) : _S_right(__x);
		}
		return RBT_insert_lower(__y, __v);
	}

	template <typename _Key, typename _Val, typename _KoV,
			  typename _Compare, typename _Alloc>
	template <typename _NodeGen>
	typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::Node_ptr
	_Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::
		RBT_copy(Const_Node_ptr __x, Nb_ptr __p, _NodeGen &__node_gen)
	{
		// Structural copy. __x and __p must be non-null.
		Node_ptr __top = _M_clone_node(__x, __node_gen);
		__top->_parent = __p;

		try
		{
			if (__x->_right)
				__top->_right = RBT_copy(_S_right(__x), __top, __node_gen);
			__p = __top;
			__x = _S_left(__x);

			while (__x != 0)
			{
				Node_ptr __y = _M_clone_node(__x, __node_gen);
				__p->_left = __y;
				__y->_parent = __p;
				if (__x->_right)
					__y->_right = RBT_copy(_S_right(__x), __y, __node_gen);
				__p = __y;
				__x = _S_left(__x);
			}
		}
		catch(...)
		{
			_M_erase(__top);
			throw ;
		}
		return __top;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_erase(Node_ptr __x)
	{
		// Erase without rebalancing.
		while (__x != 0)
		{
			if (__x->_right)
				_M_erase(_S_right(__x));
			Node_ptr __y = _S_left(__x);
			_M_drop_node(__x);
			__x = __y;
		}
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_lower_bound(Node_ptr __x, Nb_ptr __y, const _Key &__k)
	{
		while (__x != 0)
		{
			if (!_M_impl.key_comp(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);
		}
		return iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_lower_bound(Const_Node_ptr __x, Nb_Const_ptr __y, const _Key &__k) const
	{
		while (__x != 0)
		{
			if (!_M_impl.key_comp(_S_key(__x), __k))
			{
				__y = __x;
				__x = _S_left(__x);
			}
			else
				__x = _S_right(__x);
		}
		return const_iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_upper_bound(Node_ptr __x, Nb_ptr __y, const _Key &__k)
	{
		while (__x != 0)
		{
			if (_M_impl.key_comp(__k, _S_key(__x)))
			{
				__y = __x;
				__x = _S_left(__x);
			}
			else
				__x = _S_right(__x);
		}
		return iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_upper_bound(Const_Node_ptr __x, Nb_Const_ptr __y, const _Key &__k) const
	{
		while (__x != 0)
		{
			if (_M_impl.key_comp(__k, _S_key(__x)))
			{
				__y = __x;
				__x = _S_left(__x);
			}
			else
				__x = _S_right(__x);
		}
		return const_iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator,
		 typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::equal_range(const _Key &__k)
	{
		Node_ptr __x = RBT_begin();
		Nb_ptr __y = RBT_end();
		while (__x != 0)
		{
			if (_M_impl.key_comp(_S_key(__x), __k))
				__x = _S_right(__x);
			else if (_M_impl.key_comp(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
			{
				Node_ptr __xu(__x);
				Nb_ptr __yu(__y);
				__y = __x, __x = _S_left(__x);
				__xu = _S_right(__xu);
				return (pair<iterator, iterator>(_M_lower_bound(__x, __y, __k),
												 _M_upper_bound(__xu, __yu, __k)));
			}
		}
		return pair<iterator, iterator>(iterator(__y), iterator(__y));
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator,
		 typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		equal_range(const _Key &__k) const
	{
		Const_Node_ptr __x = RBT_begin();
		Nb_Const_ptr __y = RBT_end();
		while (__x != 0)
		{
			if (_M_impl.key_comp(_S_key(__x), __k))
				__x = _S_right(__x);
			else if (_M_impl.key_comp(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
			{
				Const_Node_ptr __xu(__x);
				Nb_Const_ptr __yu(__y);
				__y = __x, __x = _S_left(__x);
				__xu = _S_right(__xu);
				return pair<const_iterator, const_iterator>
					(_M_lower_bound(__x, __y, __k), _M_upper_bound(__xu, __yu, __k));
			}
		}
		return pair<const_iterator, const_iterator>(const_iterator(__y), const_iterator(__y));
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		swap(_Rb_tree &__t)
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
			std::swap(_M_root(), __t._M_root());
			std::swap(_leftmost(), __t._leftmost());
			std::swap(_rightmost(), __t._rightmost());
			_M_root()->_parent = RBT_end();
			__t._M_root()->_parent = __t.RBT_end();
			std::swap(this->_M_impl._node_count, __t._M_impl._node_count);
		}
		// No need to swap header's color as it does not change.
		std::swap(this->_M_impl.key_comp, __t._M_impl.key_comp);
		_Alloc_traits::_S_on_swap(Get_Node_allocator(), __t.Get_Node_allocator());
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr,
		 typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		get_insert_unique_pos(const key_type &__k)
	{
		typedef pair<Nb_ptr, Nb_ptr> _Res;
		Node_ptr __x = RBT_begin();
		Nb_ptr __y = RBT_end();
		bool __comp = true;
		while (__x != 0)
		{
			__y = __x;
			__comp = _M_impl.key_comp(__k, _S_key(__x));
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
		if (_M_impl.key_comp(_S_key(__j._Node), __k))
			return _Res(__x, __y);
		return _Res(__j._Node, 0);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr,
		 typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_get_insert_equal_pos(const key_type &__k)
	{
		typedef pair<Nb_ptr, Nb_ptr> _Res;
		Node_ptr __x = RBT_begin();
		Nb_ptr __y = RBT_end();
		while (__x != 0)
		{
			__y = __x;
			__x = _M_impl.key_comp(__k, _S_key(__x)) ? _S_left(__x) : _S_right(__x);
		}
		return _Res(__x, __y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator, bool>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		Insert_unique(const _Val &__v)
	{
		typedef pair<iterator, bool> _Res;
		pair<Nb_ptr, Nb_ptr> __res = get_insert_unique_pos(_KeyOfValue()(__v));
		if (__res.second)
		{
			Alloc_node __an(*this);
			return _Res(_M_insert_(__res.first, __res.second, __v, __an),
						true);
		}
		return _Res(iterator(__res.first), false);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		Insert_equal(const _Val &__v)
	{
		pair<Nb_ptr, Nb_ptr> __res = _M_get_insert_equal_pos(_KeyOfValue()(__v));
		Alloc_node __an(*this);
		return _M_insert_(__res.first, __res.second, __v, __an);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr,
		 typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		_M_get_insert_hint_unique_pos(const_iterator __position, const key_type &__k)
	{
		iterator __pos = __position._M_const_cast();
		typedef pair<Nb_ptr, Nb_ptr> _Res;
		// end()
		if (__pos._Node == RBT_end())
		{
			if (size() > 0 && _M_impl.key_comp(_S_key(_rightmost()), __k))
				return _Res(0, _rightmost());
			else
				return get_insert_unique_pos(__k);
		}
		else if (_M_impl.key_comp(__k, _S_key(__pos._Node)))
		{
			// First, try before...
			iterator __before = __pos;
			if (__pos._Node == _leftmost()) // begin()
				return _Res(_leftmost(), _leftmost());
			else if (_M_impl.key_comp(_S_key((--__before)._Node), __k))
			{
				if (_S_right(__before._Node) == 0)
					return _Res(0, __before._Node);
				else
					return _Res(__pos._Node, __pos._Node);
			}
			else
				return get_insert_unique_pos(__k);
		}
		else if (_M_impl.key_comp(_S_key(__pos._Node), __k))
		{
			// ... then try after.
			iterator __after = __pos;
			if (__pos._Node == _rightmost())
				return _Res(0, _rightmost());
			else if (_M_impl.key_comp(__k, _S_key((++__after)._Node)))
			{
				if (_S_right(__pos._Node) == 0)
					return _Res(0, __pos._Node);
				else
					return _Res(__after._Node, __after._Node);
			}
			else
				return get_insert_unique_pos(__k);
		}
		else
			return _Res(__pos._Node, 0);
		// Equivalent keys.
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	template <typename _NodeGen>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		Insert_unique_(const_iterator __position, const _Val &__v, _NodeGen &__node_gen)
	{
		pair<Nb_ptr, Nb_ptr> __res = _M_get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));
		if (__res.second)
			return _M_insert_(__res.first, __res.second, __v, __node_gen);
		return iterator(__res.first);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr,
		 typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		get_insert_hint_equal_pos(const_iterator __position, const key_type &__k)
	{
		iterator __pos = __position._M_const_cast();
		typedef pair<Nb_ptr, Nb_ptr> _Res;

		// end()
		if (__pos._Node == RBT_end())
		{
			if (size() > 0 && !_M_impl.key_comp(__k, _S_key(_rightmost())))
				return _Res(0, _rightmost());
			else
				return _M_get_insert_equal_pos(__k);
		}
		else if (!_M_impl.key_comp(_S_key(__pos._Node), __k))
		{
			// First, try before...
			iterator __before = __pos;
			if (__pos._Node == _leftmost()) // begin()
				return _Res(_leftmost(), _leftmost());
			else if (!_M_impl.key_comp(__k, _S_key((--__before)._Node)))
			{
				if (_S_right(__before._Node) == 0)
					return _Res(0, __before._Node);
				else
					return _Res(__pos._Node, __pos._Node);
			}
			else
				return _M_get_insert_equal_pos(__k);
		}
		else
		{
			// ... then try after.
			iterator __after = __pos;
			if (__pos._Node == _rightmost())
				return _Res(0, _rightmost());
			else if (!_M_impl.key_comp(_S_key((++__after)._Node), __k))
			{
				if (_S_right(__pos._Node) == 0)
					return _Res(0, __pos._Node);
				else
					return _Res(__after._Node, __after._Node);
			}
			else
				return _Res(0, 0);
		}
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	template <typename _NodeGen>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		Insert_equal_(const_iterator __position, const _Val &__v, _NodeGen &__node_gen)
	{
		pair<Nb_ptr, Nb_ptr> __res = get_insert_hint_equal_pos(__position, _KeyOfValue()(__v));
		if (__res.second)
			return _M_insert_(__res.first, __res.second, __v, __node_gen);
		return RBT_insert_equal_lower(__v);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		Erase_aux(const_iterator __position)
	{
		Node_ptr __y = static_cast<Node_ptr>(RBT_erase_rebalance(const_cast<Nb_ptr>(__position._Node), this->_M_impl._header));
		_M_drop_node(__y);
		--_M_impl._node_count;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		Erase_aux(const_iterator __first, const_iterator __last)
	{
		if (__first == begin() && __last == end())
			clear();
		else
			while (__first != __last)
				Erase_aux(__first++);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		erase(const _Key &__x)
	{
		pair<iterator, iterator> __p = equal_range(__x);
		const size_type __old_size = size();
		Erase_aux(__p.first, __p.second);
		return __old_size - size();
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		find(const _Key &__k)
	{
		iterator __j = _M_lower_bound(RBT_begin(), RBT_end(), __k);
		return (__j == end() || _M_impl.key_comp(__k, _S_key(__j._Node))) ? end() : __j;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		find(const _Key &__k) const
	{
		const_iterator __j = _M_lower_bound(RBT_begin(), RBT_end(), __k);
		return (__j == end() || _M_impl.key_comp(__k, _S_key(__j._Node))) ? end() : __j;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		count(const _Key &__k) const
	{
		pair<const_iterator, const_iterator> __p = equal_range(__k);
		const size_type __n = std::distance(__p.first, __p.second);
		return __n;
	}

	// template<typename _Key, typename _Val, typename _KeyOfValue,
	// typename _Compare, typename _Alloc>
	// bool	_Rb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::__rb_verify() const
	// {
	// 	if (_M_impl._node_count == 0 || begin() == end())
	// 		return (_M_impl._node_count == 0 && begin() == end()
	// 			&& this->_M_impl._header._left == RBT_end()
	// 			&& this->_M_impl._header._right == RBT_end());
	// 	unsigned int __len = RBT_black_count(_leftmost(), _M_root());
	// 	for (const_iterator __it = begin(); __it != end(); ++__it)
	// 	{
	// 		Const_Node_ptr __x = static_cast<Const_Node_ptr>(__it._Node);
	// 		Const_Node_ptr __L = _S_left(__x);
	// 		Const_Node_ptr __R = _S_right(__x);
	// 		if (__x->_color == RED)
	// 			if ((__L && __L->_color == RED) || (__R && __R->_color == RED))
	// 				return false;
	// 		if (__L && _M_impl.key_comp(_S_key(__x), _S_key(__L)))
	// 			return false;
	// 		if (__R && _M_impl.key_comp(_S_key(__R), _S_key(__x)))
	// 			return false;
	// 		if (!__L && !__R && RBT_black_count(__x, _M_root()) != __len)
	// 			return false;
	// 	}
	// 	if (_leftmost() != Node_base::_S_minimum(_M_root()))
	// 		return false;
	// 	if (_rightmost() != Node_base::_S_maximum(_M_root()))
	// 		return false;
	// 	return true;
	// }

} // namespace

#endif