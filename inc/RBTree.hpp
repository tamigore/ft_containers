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
		typedef const Node_base *Nb_const_ptr;

		RBT_color _color;
		Nb_ptr _parent;
		Nb_ptr _left;
		Nb_ptr _right;

		static Nb_ptr N_minimum(Nb_ptr __x)
		{
			while (__x->_left != 0)
				__x = __x->_left;
			return __x;
		}

		static Nb_const_ptr N_minimum(Nb_const_ptr __x)
		{
			while (__x->_left != 0)
				__x = __x->_left;
			return __x;
		}

		static Nb_ptr N_maximum(Nb_ptr __x)
		{
			while (__x->_right != 0)
				__x = __x->_right;
			return __x;
		}

		static Nb_const_ptr N_maximum(Nb_const_ptr __x)
		{
			while (__x->_right != 0)
				__x = __x->_right;
			return __x;
		}

		Nb_ptr			localRBT_increment(Nb_ptr __x) const
		{
			if (__x->_right != 0) 
			{
				__x = __x->_right;
				while (__x->_left != 0)
					__x = __x->_left;
			}
			else 
			{
				Nb_ptr __y = __x->_parent;
				while (__x == __y->_right) 
				{
					__x = __y;
					__y = __y->_parent;
				}
				if (__x->_right != __y)
					__x = __y;
			}
			return (__x);
		}

		Nb_ptr			RBT_increment()
		{
			return (localRBT_increment(this));
		}

		Nb_const_ptr	RBT_increment() const
		{
			return (localRBT_increment(const_cast<Nb_ptr>(this)));
		}

		Nb_ptr	localRBT_decrement(Nb_ptr __x) const
		{
			if (__x->_color == RED && __x->_parent->_parent == __x)
				__x = __x->_right;
			else if (__x->_left != 0)
			{
				Nb_ptr __y = __x->_left;
				while (__y->_right != 0)
					__y = __y->_right;
				__x = __y;
			}
			else
			{
				Nb_ptr __y = __x->_parent;
				while (__x == __y->_left)
				{
					__x = __y;
					__y = __y->_parent;
				}
				__x = __y;
			}
			return __x;
		}

		Nb_ptr			RBT_decrement()
		{
			return localRBT_decrement(this);
		}

		Nb_const_ptr	RBT_decrement() const
		{
			return localRBT_decrement(const_cast<Nb_ptr>(this));
		}

		void	RBT_rotate_left(Nb_ptr const __x, Nb_ptr& __root)
		{
			Nb_ptr const __y = __x->_right;

			__x->_right = __y->_left;
			if (__y->_left !=0)
				__y->_left->_parent = __x;
			__y->_parent = __x->_parent;

			if (__x == __root)
				__root = __y;
			else if (__x == __x->_parent->_left)
				__x->_parent->_left = __y;
			else
				__x->_parent->_right = __y;
			__y->_left = __x;
			__x->_parent = __y;
		}

		void	RBT_rotate_right(Nb_ptr const __x, Nb_ptr& __root)
		{
			Nb_ptr const __y = __x->_left;

			__x->_left = __y->_right;
			if (__y->_right != 0)
				__y->_right->_parent = __x;
			__y->_parent = __x->_parent;

			if (__x == __root)
				__root = __y;
			else if (__x == __x->_parent->_right)
				__x->_parent->_right = __y;
			else
				__x->_parent->_left = __y;
			__y->_right = __x;
			__x->_parent = __y;
		}

		void	RBT_insert_rebalance(const bool __insert_left, Node_base* __x, Node_base* __p, Node_base& __header) throw ()
		{
			Node_base *& __root = __header._parent;

			// Initialize fields in new node to insert.
			__x->_parent = __p;
			__x->_left = 0;
			__x->_right = 0;
			__x->_color = RED;

			// Insert.
			// Make new node child of parent and maintain root, leftmost and
			// rightmost nodes.
			// N.B. First node is always inserted left.
			if (__insert_left)
			{
				__p->_left = __x; // also makes leftmost = __x when __p == &__header

				if (__p == &__header)
				{
					__header._parent = __x;
					__header._right = __x;
				}
				else if (__p == __header._left)
					__header._left = __x; // maintain leftmost pointing to min node
			}
			else
			{
				__p->_right = __x;

				if (__p == __header._right)
					__header._right = __x; // maintain rightmost pointing to max node
			}
			// Rebalance.
			while (__x != __root && __x->_parent->_color == RED)
			{
				Node_base* const __xpp = __x->_parent->_parent;

				if (__x->_parent == __xpp->_left)
				{
					Node_base* const __y = __xpp->_right;
					if (__y && __y->_color == RED)
					{
						__x->_parent->_color = BLACK;
						__y->_color = BLACK;
						__xpp->_color = RED;
						__x = __xpp;
					}
					else
					{
						if (__x == __x->_parent->_right)
						{
							__x = __x->_parent;
							RBT_rotate_left(__x, __root);
						}
						__x->_parent->_color = BLACK;
						__xpp->_color = RED;
						RBT_rotate_right(__xpp, __root);
					}
				}
				else
				{
					Node_base* const __y = __xpp->_left;
					if (__y && __y->_color == RED)
					{
						__x->_parent->_color = BLACK;
						__y->_color = BLACK;
						__xpp->_color = RED;
						__x = __xpp;
					}
					else
					{
						if (__x == __x->_parent->_left)
						{
							__x = __x->_parent;
							RBT_rotate_right(__x, __root);
						}
						__x->_parent->_color = BLACK;
						__xpp->_color = RED;
						RBT_rotate_left(__xpp, __root);
					}
				}
			}
			__root->_color = BLACK;
		}

		Node_base*	RBT_erase_rebalance(Node_base* const __z, Node_base& __header) throw ()
		{
			Node_base *& __root = __header._parent;
			Node_base *& __leftmost = __header._left;
			Node_base *& __rightmost = __header._right;
			Node_base* __y = __z;
			Node_base* __x = 0;
			Node_base* __x_parent = 0;

			if (__y->_left == 0)     // __z has at most one non-null child. y == z.
				__x = __y->_right;     // __x might be null.
			else
				if (__y->_right == 0)  // __z has exactly one non-null child. y == z.
					__x = __y->_left;    // __x is not null.
			else
			{
				// __z has two non-null children.  Set __y to
				__y = __y->_right;   //   __z's successor.  __x might be null.
				while (__y->_left != 0)
					__y = __y->_left;
				__x = __y->_right;
			}
			if (__y != __z)
			{
				// relink y in place of z.  y is z's successor
				__z->_left->_parent = __y;
				__y->_left = __z->_left;
				if (__y != __z->_right)
				{
					__x_parent = __y->_parent;
					if (__x) __x->_parent = __y->_parent;
						__y->_parent->_left = __x;// __y must be a child of _left
					__y->_right = __z->_right;
					__z->_right->_parent = __y;
				}
				else
					__x_parent = __y;
				if (__root == __z)
					__root = __y;
				else if (__z->_parent->_left == __z)
					__z->_parent->_left = __y;
				else
					__z->_parent->_right = __y;
				__y->_parent = __z->_parent;
				ft::swap(__y->_color, __z->_color);
				__y = __z;// __y now points to node to be actually deleted
			}
			else
			{ // __y == __z
				__x_parent = __y->_parent;
				if (__x)
					__x->_parent = __y->_parent;
				if (__root == __z)
					__root = __x;
				else
					if (__z->_parent->_left == __z)
						__z->_parent->_left = __x;
					else
						__z->_parent->_right = __x;
				if (__leftmost == __z)
				{
					if (__z->_right == 0)// __z->_left must be null also
						__leftmost = __z->_parent;
					// makes __leftmost == _M_header if __z == __root
					else
						__leftmost = N_minimum(__x);
				}
				if (__rightmost == __z)
				{
					if (__z->_left == 0)// __z->_right must be null also
						__rightmost = __z->_parent;
					// makes __rightmost == _M_header if __z == __root
					else                      // __x == __z->_left
						__rightmost = N_maximum(__x);
				}
			}
			if (__y->_color != RED)
			{
				while (__x != __root && (__x == 0 || __x->_color == BLACK))
				{
					if (__x == __x_parent->_left)
					{
						Node_base* __w = __x_parent->_right;
						if (__w->_color == RED)
						{
							__w->_color = BLACK;
							__x_parent->_color = RED;
							RBT_rotate_left(__x_parent, __root);
							__w = __x_parent->_right;
						}
						if ((__w->_left == 0 || __w->_left->_color == BLACK) &&
							(__w->_right == 0 || __w->_right->_color == BLACK))
						{
							__w->_color = RED;
							__x = __x_parent;
							__x_parent = __x_parent->_parent;
						}
						else
						{
							if (__w->_right == 0 || __w->_right->_color == BLACK)
							{
								__w->_left->_color = BLACK;
								__w->_color = RED;
								RBT_rotate_right(__w, __root);
								__w = __x_parent->_right;
							}
							__w->_color = __x_parent->_color;
							__x_parent->_color = BLACK;
							if (__w->_right)
								__w->_right->_color = BLACK;
							RBT_rotate_left(__x_parent, __root);
							break;
						}
					}
					else
					{
						// same as above, with _right <-> _left.
						Node_base* __w = __x_parent->_left;
						if (__w->_color == RED)
						{
							__w->_color = BLACK;
							__x_parent->_color = RED;
							RBT_rotate_right(__x_parent, __root);
							__w = __x_parent->_left;
						}
						if ((__w->_right == 0 || __w->_right->_color == BLACK) &&
							(__w->_left == 0 || __w->_left->_color == BLACK))
						{
							__w->_color = RED;
							__x = __x_parent;
							__x_parent = __x_parent->_parent;
						}
						else
						{
							if (__w->_left == 0 || __w->_left->_color == BLACK)
							{
								__w->_right->_color = BLACK;
								__w->_color = RED;
								RBT_rotate_left(__w, __root);
								__w = __x_parent->_left;
							}
							__w->_color = __x_parent->_color;
							__x_parent->_color = BLACK;
							if (__w->_left)
								__w->_left->_color = BLACK;
							RBT_rotate_right(__x_parent, __root);
							break;
						}
					}
				}
				if (__x)
					__x->_color = BLACK;
			}
			return __y;
		}
	};

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
			_header._parent = NULL;
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

		_Val *Get_ValPtr()
		{ return __builtin_addressof(value); }

		const _Val *Get_ValPtr() const
		{ return __builtin_addressof(value); }
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
			return *static_cast<Node_ptr>(_Node)->Get_ValPtr();
		}

		pointer operator->() const
		{
			return static_cast<Node_ptr>(_Node)->Get_ValPtr();
		}

		_Self &operator++()
		{
			_Node = _Node->RBT_increment();
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_Node = _Node->RBT_increment();
			return __tmp;
		}

		_Self &operator--()
		{
			_Node = _Node->RBT_decrement();
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			_Node = _Node->RBT_decrement();
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
		typedef Node_base::Nb_const_ptr Nb_ptr;
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
			return *static_cast<Node_ptr>(_Node)->Get_ValPtr();
		}

		pointer operator->() const
		{
			return static_cast<Node_ptr>(_Node)->Get_ValPtr();
		}

		_Self &operator++()
		{
			_Node = _Node->RBT_increment();
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_Node = _Node->RBT_increment();
			return __tmp;
		}

		_Self &operator--()
		{
			_Node = _Node->RBT_decrement();
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			_Node = _Node->RBT_decrement();
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
		typedef typename alloc_traits<_Alloc>::template rebind<RBT_Node<_Val> >::other _Node_allocator;

		typedef alloc_traits<_Node_allocator> _Alloc_traits;

	protected:
		typedef Node_base *Nb_ptr;
		typedef const Node_base *Nb_const_ptr;
		typedef RBT_Node<_Val> *Node_ptr;
		typedef const RBT_Node<_Val> *Const_Node_ptr;

		// Functor recycling a pool of nodes and using allocation once the pool
		// is empty.
		struct ReuseAlloc_node
		{
			ReuseAlloc_node(_Rb_tree &__t)
				: _root(__t.RBT_root()), _Nodes(__t.RBT_rightmost()), _RBT(__t)
			{
				if (_root)
				{
					_root->_parent = 0;

					if (_Nodes->_left)
						_Nodes = _Nodes->_left;
				}
				else
					_Nodes = 0;
			}

			~ReuseAlloc_node()
			{
				if (_root)
					_RBT.RBT_erase(static_cast<Node_ptr>(_root));
			}

			template <typename _Arg>
			Node_ptr operator()(const _Arg &__arg)
			{
				Node_ptr __node = static_cast<Node_ptr>(Extract());
				if (__node)
				{
					_RBT.Destroy_Node(__node);
					_RBT.Construct_Node(__node, __arg);
					return __node;
				}
				return _RBT.Create_Node(__arg);
			}

			Nb_ptr Extract()
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
					_root = 0;
				return __node;
			}

			Nb_ptr _root;
			Nb_ptr _Nodes;
			_Rb_tree &_RBT;
		};

		// Functor similar to the previous one but without any pool of nodes to
		// recycle.
		struct Alloc_node
		{
			Alloc_node(_Rb_tree &__t) : _RBT(__t) {}

			template <typename _Arg>
			Node_ptr operator()(const _Arg &__arg) const
			{
				return _RBT.Create_Node(__arg);
			}

		private:
			_Rb_tree &_RBT;
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

		_Node_allocator &Get_Node_Allocator()
		{
			return this->_M_impl;
		}

		const _Node_allocator &Get_Node_Allocator() const
		{
			return this->_M_impl;
		}

		allocator_type Get_Allocator() const
		{
			return allocator_type(Get_Node_Allocator());
		}

	protected:
		Node_ptr Get_Root()
		{ return _Alloc_traits::allocate(Get_Node_Allocator(), 1); }

		void Dealloc_Node(Node_ptr __p)
		{
			if (__p)
			{
				_Alloc_traits::deallocate(Get_Node_Allocator(), __p, 1);
				__p = NULL;
			}
		}

		void Construct_Node(Node_ptr __node, const value_type &__x)
		{
			try
			{
				Get_Allocator().construct(__node->Get_ValPtr(), __x);
			}
			catch (const std::exception &e)
			{
				Dealloc_Node(__node);
				throw ; //__throw_exception_again;
			}
		}

		Node_ptr Create_Node(const value_type &__x)
		{
			Node_ptr __tmp = Get_Root();
			Construct_Node(__tmp, __x);
			return __tmp;
		}

		void Destroy_Node(Node_ptr __p)
		{
			if (__p)
				Get_Allocator().destroy(__p->Get_ValPtr());
		}

		void Drop_Node(Node_ptr __p)
		{
			Destroy_Node(__p);
			Dealloc_Node(__p);
		}

		template <typename _NodeGen>
		Node_ptr Clone_Node(Const_Node_ptr __x, _NodeGen &__node_gen)
		{
			Node_ptr __tmp = __node_gen(*__x->Get_ValPtr());
			__tmp->_color = __x->_color;
			__tmp->_left = 0;
			__tmp->_right = 0;
			return __tmp;
		}

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

		Nb_ptr &RBT_root()
		{ return this->_M_impl._header._parent; }

		Nb_const_ptr RBT_root() const
		{ return this->_M_impl._header._parent; }

		Nb_ptr &RBT_leftmost()
		{ return this->_M_impl._header._left; }

		Nb_const_ptr RBT_leftmost() const
		{ return this->_M_impl._header._left; }

		Nb_ptr &RBT_rightmost()
		{ return this->_M_impl._header._right; }

		Nb_const_ptr RBT_rightmost() const
		{ return this->_M_impl._header._right; }

		Node_ptr RBT_begin()
		{ return static_cast<Node_ptr>(this->_M_impl._header._parent); }

		Const_Node_ptr RBT_begin() const
		{ return static_cast<Const_Node_ptr>(this->_M_impl._header._parent); }

		Nb_ptr RBT_end()
		{ return &this->_M_impl._header; }

		Nb_const_ptr RBT_end() const
		{ return &this->_M_impl._header; }

		static const _Key &N_key(Const_Node_ptr __x)
		{ return _KeyOfValue()(*__x->Get_ValPtr()); }

		static Node_ptr N_left(Nb_ptr __x)
		{ return static_cast<Node_ptr>(__x->_left); }

		static Const_Node_ptr N_left(Nb_const_ptr __x)
		{ return static_cast<Const_Node_ptr>(__x->_left); }

		static Node_ptr N_right(Nb_ptr __x)
		{ return static_cast<Node_ptr>(__x->_right); }

		static Const_Node_ptr N_right(Nb_const_ptr __x)
		{ return static_cast<Const_Node_ptr>(__x->_right); }

		static const _Key &N_key(Nb_const_ptr __x)
		{ return N_key(static_cast<Const_Node_ptr>(__x)); }

		static Nb_ptr N_minimum(Nb_ptr __x)
		{ return Node_base::N_minimum(__x); }

		static Nb_const_ptr N_minimum(Nb_const_ptr __x)
		{ return Node_base::N_minimum(__x); }

		static Nb_ptr N_maximum(Nb_ptr __x)
		{ return Node_base::N_maximum(__x); }

		static Nb_const_ptr N_maximum(Nb_const_ptr __x)
		{ return Node_base::N_maximum(__x); }

	public:
		typedef RBT_iterator<value_type> iterator;
		typedef RBT_const_iterator<value_type> const_iterator;

		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		pair<Nb_ptr, Nb_ptr> get_insert_unique_pos(const key_type &__k);

		pair<Nb_ptr, Nb_ptr> get_insert_equal_pos(const key_type &__k);

		pair<Nb_ptr, Nb_ptr> get_insert_hint_unique_pos(
			const_iterator __pos,
			const key_type &__k);

		pair<Nb_ptr, Nb_ptr> get_insert_hint_equal_pos(
			const_iterator __pos,
			const key_type &__k);

	private:
		template <typename _NodeGen>
		iterator RBT_insert(Nb_ptr __x, Nb_ptr __y,
			const value_type &__v, _NodeGen &);

		iterator RBT_insert_lower(Nb_ptr __y, const value_type &__v);

		iterator RBT_insert_equal_lower(const value_type &__x);

		template <typename _NodeGen>
		Node_ptr RBT_copy(Const_Node_ptr __x, Nb_ptr __p, _NodeGen &);

		template <typename _NodeGen>
		Node_ptr RBT_copy(const _Rb_tree &__x, _NodeGen &__gen)
		{
			Node_ptr __root = RBT_copy(__x.RBT_begin(), RBT_end(), __gen);
			RBT_leftmost() = N_minimum(__root);
			RBT_rightmost() = N_maximum(__root);
			_M_impl._node_count = __x._M_impl._node_count;
			return __root;
		}

		Node_ptr RBT_copy(const _Rb_tree &__x)
		{
			Alloc_node __an(*this);
			return RBT_copy(__x, __an);
		}

		void RBT_erase(Node_ptr __x);

		iterator RBT_lower_bound(Node_ptr __x, Nb_ptr __y, const _Key &__k);

		const_iterator RBT_lower_bound(Const_Node_ptr __x, Nb_const_ptr __y,
			const _Key &__k) const;

		iterator RBT_upper_bound(Node_ptr __x, Nb_ptr __y, const _Key &__k);

		const_iterator RBT_upper_bound(Const_Node_ptr __x, Nb_const_ptr __y,
			const _Key &__k) const;

	public:
		_Rb_tree() {}

		_Rb_tree(const _Compare &__comp,
				 const allocator_type &__a = allocator_type())
			: _M_impl(__comp, _Node_allocator(__a)) {}

		_Rb_tree(const _Rb_tree &__x) : _M_impl(__x._M_impl)
		{
			if (__x.RBT_root() != 0)
				RBT_root() = RBT_copy(__x);
		}

		~_Rb_tree()
		{
			if (this->_M_impl._node_count != 0)
				RBT_erase(RBT_begin());
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
			return _Alloc_traits::max_size(Get_Node_Allocator());
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
			RBT_erase(RBT_begin());
			_M_impl._M_reset();
		}

		// Set operations.
		iterator find(const key_type &__k);

		const_iterator find(const key_type &__k) const;

		size_type count(const key_type &__k) const;

		iterator lower_bound(const key_type &__k)
		{
			return RBT_lower_bound(RBT_begin(), RBT_end(), __k);
		}

		const_iterator lower_bound(const key_type &__k) const
		{
			return RBT_lower_bound(RBT_begin(), RBT_end(), __k);
		}

		iterator upper_bound(const key_type &__k)
		{
			return RBT_upper_bound(RBT_begin(), RBT_end(), __k);
		}

		const_iterator upper_bound(const key_type &__k) const
		{
			return RBT_upper_bound(RBT_begin(), RBT_end(), __k);
		}

		pair<iterator, iterator> equal_range(const key_type &__k);

		pair<const_iterator, const_iterator> equal_range(const key_type &__k) const;

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
	{ __x.swap(__y); }

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
			if (__x.RBT_root() != 0)
				RBT_root() = RBT_copy(__x, __roan);
		}
		return *this;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	template <typename _NodeGen>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		RBT_insert(Nb_ptr __x, Nb_ptr __p, const _Val &__v, _NodeGen &__node_gen)
	{
		bool __insert_left = (__x != 0 || __p == RBT_end() || _M_impl.key_comp(_KeyOfValue()(__v), N_key(__p)));

		Node_ptr __z = __node_gen(__v);

		this->_M_impl._header.RBT_insert_rebalance(__insert_left, __z, __p, this->_M_impl._header);
		++_M_impl._node_count;
		return iterator(__z);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		RBT_insert_lower(Nb_ptr __p, const _Val &__v)
	{
		bool __insert_left = (__p == RBT_end() || !_M_impl.key_comp(N_key(__p), _KeyOfValue()(__v)));

		Node_ptr __z = Create_Node(__v);

		this->_M_impl._header.RBT_insert_rebalance(__insert_left, __z, __p, this->_M_impl._header);
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
			__x = !_M_impl.key_comp(N_key(__x), _KeyOfValue()(__v)) ? N_left(__x) : N_right(__x);
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
		Node_ptr __top = Clone_Node(__x, __node_gen);
		__top->_parent = __p;

		try
		{
			if (__x->_right)
				__top->_right = RBT_copy(N_right(__x), __top, __node_gen);
			__p = __top;
			__x = N_left(__x);

			while (__x != 0)
			{
				Node_ptr __y = Clone_Node(__x, __node_gen);
				__p->_left = __y;
				__y->_parent = __p;
				if (__x->_right)
					__y->_right = RBT_copy(N_right(__x), __y, __node_gen);
				__p = __y;
				__x = N_left(__x);
			}
		}
		catch(...)
		{
			RBT_erase(__top);
			throw ;
		}
		return __top;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		RBT_erase(Node_ptr __x)
	{
		// Erase without rebalancing.
		while (__x)
		{
			if (__x->_right)
				RBT_erase(N_right(__x));
			Node_ptr __y = N_left(__x);
			Drop_Node(__x);
			__x = __y;
		}
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		RBT_lower_bound(Node_ptr __x, Nb_ptr __y, const _Key &__k)
	{
		while (__x != 0)
		{
			if (!_M_impl.key_comp(N_key(__x), __k))
				__y = __x, __x = N_left(__x);
			else
				__x = N_right(__x);
		}
		return iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		RBT_lower_bound(Const_Node_ptr __x, Nb_const_ptr __y, const _Key &__k) const
	{
		while (__x != 0)
		{
			if (!_M_impl.key_comp(N_key(__x), __k))
			{
				__y = __x;
				__x = N_left(__x);
			}
			else
				__x = N_right(__x);
		}
		return const_iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		RBT_upper_bound(Node_ptr __x, Nb_ptr __y, const _Key &__k)
	{
		while (__x != 0)
		{
			if (_M_impl.key_comp(__k, N_key(__x)))
			{
				__y = __x;
				__x = N_left(__x);
			}
			else
				__x = N_right(__x);
		}
		return iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		RBT_upper_bound(Const_Node_ptr __x, Nb_const_ptr __y, const _Key &__k) const
	{
		while (__x != 0)
		{
			if (_M_impl.key_comp(__k, N_key(__x)))
			{
				__y = __x;
				__x = N_left(__x);
			}
			else
				__x = N_right(__x);
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
			if (_M_impl.key_comp(N_key(__x), __k))
				__x = N_right(__x);
			else if (_M_impl.key_comp(__k, N_key(__x)))
				__y = __x, __x = N_left(__x);
			else
			{
				Node_ptr __xu(__x);
				Nb_ptr __yu(__y);
				__y = __x, __x = N_left(__x);
				__xu = N_right(__xu);
				return (pair<iterator, iterator>(RBT_lower_bound(__x, __y, __k),
												 RBT_upper_bound(__xu, __yu, __k)));
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
		Nb_const_ptr __y = RBT_end();
		while (__x != 0)
		{
			if (_M_impl.key_comp(N_key(__x), __k))
				__x = N_right(__x);
			else if (_M_impl.key_comp(__k, N_key(__x)))
				__y = __x, __x = N_left(__x);
			else
			{
				Const_Node_ptr __xu(__x);
				Nb_const_ptr __yu(__y);
				__y = __x, __x = N_left(__x);
				__xu = N_right(__xu);
				return pair<const_iterator, const_iterator>
					(RBT_lower_bound(__x, __y, __k), RBT_upper_bound(__xu, __yu, __k));
			}
		}
		return pair<const_iterator, const_iterator>(const_iterator(__y), const_iterator(__y));
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		swap(_Rb_tree &__t)
	{
		if (RBT_root() == 0)
		{
			if (__t.RBT_root() != 0)
				_M_impl._M_move_data(__t._M_impl);
		}
		else if (__t.RBT_root() == 0)
			__t._M_impl._M_move_data(_M_impl);
		else
		{
			ft::swap(RBT_root(), __t.RBT_root());
			ft::swap(RBT_leftmost(), __t.RBT_leftmost());
			ft::swap(RBT_rightmost(), __t.RBT_rightmost());
			RBT_root()->_parent = RBT_end();
			__t.RBT_root()->_parent = __t.RBT_end();
			ft::swap(this->_M_impl._node_count, __t._M_impl._node_count);
		}
		// No need to swap header's color as it does not change.
		ft::swap(this->_M_impl.key_comp, __t._M_impl.key_comp);
		_Alloc_traits::_S_on_swap(Get_Node_Allocator(), __t.Get_Node_Allocator());
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
			__comp = _M_impl.key_comp(__k, N_key(__x));
			__x = __comp ? N_left(__x) : N_right(__x);
		}
		iterator __j = iterator(__y);
		if (__comp)
		{
			if (__j == begin())
				return _Res(__x, __y);
			else
				--__j;
		}
		if (_M_impl.key_comp(N_key(__j._Node), __k))
			return _Res(__x, __y);
		return _Res(__j._Node, 0);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr,
		 typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		get_insert_equal_pos(const key_type &__k)
	{
		typedef pair<Nb_ptr, Nb_ptr> _Res;
		Node_ptr __x = RBT_begin();
		Nb_ptr __y = RBT_end();
		while (__x != 0)
		{
			__y = __x;
			__x = _M_impl.key_comp(__k, N_key(__x)) ? N_left(__x) : N_right(__x);
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
			return _Res(RBT_insert(__res.first, __res.second, __v, __an),
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
		pair<Nb_ptr, Nb_ptr> __res = get_insert_equal_pos(_KeyOfValue()(__v));
		Alloc_node __an(*this);
		return RBT_insert(__res.first, __res.second, __v, __an);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr,
		 typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::Nb_ptr>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		get_insert_hint_unique_pos(const_iterator __position, const key_type &__k)
	{
		iterator __pos = __position._M_const_cast();
		typedef pair<Nb_ptr, Nb_ptr> _Res;
		// end()
		if (__pos._Node == RBT_end())
		{
			if (size() > 0 && _M_impl.key_comp(N_key(RBT_rightmost()), __k))
				return _Res(0, RBT_rightmost());
			else
				return get_insert_unique_pos(__k);
		}
		else if (_M_impl.key_comp(__k, N_key(__pos._Node)))
		{
			// First, try before...
			iterator __before = __pos;
			if (__pos._Node == RBT_leftmost()) // begin()
				return _Res(RBT_leftmost(), RBT_leftmost());
			else if (_M_impl.key_comp(N_key((--__before)._Node), __k))
			{
				if (N_right(__before._Node) == 0)
					return _Res(0, __before._Node);
				else
					return _Res(__pos._Node, __pos._Node);
			}
			else
				return get_insert_unique_pos(__k);
		}
		else if (_M_impl.key_comp(N_key(__pos._Node), __k))
		{
			// ... then try after.
			iterator __after = __pos;
			if (__pos._Node == RBT_rightmost())
				return _Res(0, RBT_rightmost());
			else if (_M_impl.key_comp(__k, N_key((++__after)._Node)))
			{
				if (N_right(__pos._Node) == 0)
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
		pair<Nb_ptr, Nb_ptr> __res = get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));
		if (__res.second)
			return RBT_insert(__res.first, __res.second, __v, __node_gen);
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
			if (size() > 0 && !_M_impl.key_comp(__k, N_key(RBT_rightmost())))
				return _Res(0, RBT_rightmost());
			else
				return get_insert_equal_pos(__k);
		}
		else if (!_M_impl.key_comp(N_key(__pos._Node), __k))
		{
			// First, try before...
			iterator __before = __pos;
			if (__pos._Node == RBT_leftmost()) // begin()
				return _Res(RBT_leftmost(), RBT_leftmost());
			else if (!_M_impl.key_comp(__k, N_key((--__before)._Node)))
			{
				if (N_right(__before._Node) == 0)
					return _Res(0, __before._Node);
				else
					return _Res(__pos._Node, __pos._Node);
			}
			else
				return get_insert_equal_pos(__k);
		}
		else
		{
			// ... then try after.
			iterator __after = __pos;
			if (__pos._Node == RBT_rightmost())
				return _Res(0, RBT_rightmost());
			else if (!_M_impl.key_comp(N_key((++__after)._Node), __k))
			{
				if (N_right(__pos._Node) == 0)
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
			return RBT_insert(__res.first, __res.second, __v, __node_gen);
		return RBT_insert_equal_lower(__v);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		Erase_aux(const_iterator __position)
	{
		Node_ptr __y = static_cast<Node_ptr>(this->_M_impl._header.RBT_erase_rebalance(const_cast<Nb_ptr>(__position._Node), this->_M_impl._header));
		Drop_Node(__y);
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
		iterator __j = RBT_lower_bound(RBT_begin(), RBT_end(), __k);
		return (__j == end() || _M_impl.key_comp(__k, N_key(__j._Node))) ? end() : __j;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		find(const _Key &__k) const
	{
		const_iterator __j = RBT_lower_bound(RBT_begin(), RBT_end(), __k);
		return (__j == end() || _M_impl.key_comp(__k, N_key(__j._Node))) ? end() : __j;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue,
			  typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
		count(const _Key &__k) const
	{
		pair<const_iterator, const_iterator> __p = equal_range(__k);
		const size_type __n = distance(__p.first, __p.second);
		return __n;
	}
} // namespace

#endif