#include "RBTree.hpp"

static ft::Node_base*	localRBT_increment(ft::Node_base* __x) throw ()
{
	if (__x->_right != 0) 
	{
		__x = __x->_right;
		while (__x->_left != 0)
			__x = __x->_left;
	}
	else 
	{
		ft::Node_base* __y = __x->_parent;
		while (__x == __y->_right) 
		{
			__x = __y;
			__y = __y->_parent;
		}
		if (__x->_right != __y)
			__x = __y;
	}
	return __x;
}

ft::Node_base*	ft::RBT_increment(ft::Node_base* __x) throw ()
{
	return localRBT_increment(__x);
}

const ft::Node_base*	ft::RBT_increment(const ft::Node_base* __x) throw ()
{
	return localRBT_increment(const_cast<ft::Node_base*>(__x));
}

static ft::Node_base*	localRBT_decrement(ft::Node_base* __x) throw ()
{
	if (__x->_color == ft::RED && __x->_parent->_parent == __x)
		__x = __x->_right;
	else if (__x->_left != 0)
	{
		ft::Node_base* __y = __x->_left;
		while (__y->_right != 0)
			__y = __y->_right;
		__x = __y;
	}
	else
	{
		ft::Node_base* __y = __x->_parent;
		while (__x == __y->_left)
		{
			__x = __y;
			__y = __y->_parent;
		}
		__x = __y;
	}
	return __x;
}

ft::Node_base*	ft::RBT_decrement(ft::Node_base* __x) throw ()
{
	return localRBT_decrement(__x);
}

const ft::Node_base*	ft::RBT_decrement(const ft::Node_base* __x) throw ()
{
	return localRBT_decrement(const_cast<ft::Node_base*>(__x));
}

unsigned int	ft::RBT_black_count(const ft::Node_base* __node, const ft::Node_base* __root) throw ()
{
	if (__node == 0)
		return 0;
	unsigned int __sum = 0;
	do
	{
		if (__node->_color == ft::BLACK)
			++__sum;
		if (__node == __root)
			break;
		__node = __node->_parent;
	}
	while (1);
	return __sum;
}

void	ft::RBT_rotate_left(ft::Node_base* const __x, ft::Node_base*& __root)
{
	ft::Node_base* const __y = __x->_right;

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

void	ft::RBT_rotate_right(ft::Node_base* const __x, ft::Node_base*& __root)
{
	ft::Node_base* const __y = __x->_left;

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

void	ft::RBT_insert_rebalance(const bool __insert_left, ft::Node_base* __x, ft::Node_base* __p, ft::Node_base& __header) throw ()
{
	ft::Node_base *& __root = __header._parent;

	// Initialize fields in new node to insert.
	__x->_parent = __p;
	__x->_left = 0;
	__x->_right = 0;
	__x->_color = ft::RED;

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
	while (__x != __root && __x->_parent->_color == ft::RED)
	{
		ft::Node_base* const __xpp = __x->_parent->_parent;

		if (__x->_parent == __xpp->_left)
		{
			ft::Node_base* const __y = __xpp->_right;
			if (__y && __y->_color == ft::RED)
			{
				__x->_parent->_color = ft::BLACK;
				__y->_color = ft::BLACK;
				__xpp->_color = ft::RED;
				__x = __xpp;
			}
			else
			{
				if (__x == __x->_parent->_right)
				{
					__x = __x->_parent;
					RBT_rotate_left(__x, __root);
				}
				__x->_parent->_color = ft::BLACK;
				__xpp->_color = ft::RED;
				RBT_rotate_right(__xpp, __root);
			}
		}
		else
		{
			ft::Node_base* const __y = __xpp->_left;
			if (__y && __y->_color == ft::RED)
			{
				__x->_parent->_color = ft::BLACK;
				__y->_color = ft::BLACK;
				__xpp->_color = ft::RED;
				__x = __xpp;
			}
			else
			{
				if (__x == __x->_parent->_left)
				{
					__x = __x->_parent;
					RBT_rotate_right(__x, __root);
				}
				__x->_parent->_color = ft::BLACK;
				__xpp->_color = ft::RED;
				RBT_rotate_left(__xpp, __root);
			}
		}
	}
	__root->_color = ft::BLACK;
}

ft::Node_base*	ft::RBT_erase_rebalance(ft::Node_base* const __z, ft::Node_base& __header) throw ()
{
	ft::Node_base *& __root = __header._parent;
	ft::Node_base *& __leftmost = __header._left;
	ft::Node_base *& __rightmost = __header._right;
	ft::Node_base* __y = __z;
	ft::Node_base* __x = 0;
	ft::Node_base* __x_parent = 0;

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
			__y->_parent->_left = __x;   // __y must be a child of _left
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
		std::swap(__y->_color, __z->_color);
		__y = __z;
		// __y now points to node to be actually deleted
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
			if (__z->_right == 0)        // __z->_left must be null also
				__leftmost = __z->_parent;
			// makes __leftmost == _M_header if __z == __root
			else
				__leftmost = ft::Node_base::_S_minimum(__x);
		}
		if (__rightmost == __z)
		{
			if (__z->_left == 0)         // __z->_right must be null also
				__rightmost = __z->_parent;
			// makes __rightmost == _M_header if __z == __root
			else                      // __x == __z->_left
				__rightmost = ft::Node_base::_S_maximum(__x);
		}
	}
	if (__y->_color != ft::RED)
	{
		while (__x != __root && (__x == 0 || __x->_color == ft::BLACK))
		{
			if (__x == __x_parent->_left)
			{
				ft::Node_base* __w = __x_parent->_right;
				if (__w->_color == ft::RED)
				{
					__w->_color = ft::BLACK;
					__x_parent->_color = ft::RED;
					RBT_rotate_left(__x_parent, __root);
					__w = __x_parent->_right;
				}
				if ((__w->_left == 0 || __w->_left->_color == ft::BLACK) &&
					(__w->_right == 0 || __w->_right->_color == ft::BLACK))
				{
					__w->_color = ft::RED;
					__x = __x_parent;
					__x_parent = __x_parent->_parent;
				}
				else
				{
					if (__w->_right == 0 || __w->_right->_color == ft::BLACK)
					{
						__w->_left->_color = ft::BLACK;
						__w->_color = ft::RED;
						RBT_rotate_right(__w, __root);
						__w = __x_parent->_right;
					}
					__w->_color = __x_parent->_color;
					__x_parent->_color = ft::BLACK;
					if (__w->_right)
						__w->_right->_color = ft::BLACK;
					RBT_rotate_left(__x_parent, __root);
					break;
				}
			}
			else
			{
				// same as above, with _right <-> _left.
				ft::Node_base* __w = __x_parent->_left;
				if (__w->_color == ft::RED)
				{
					__w->_color = ft::BLACK;
					__x_parent->_color = ft::RED;
					RBT_rotate_right(__x_parent, __root);
					__w = __x_parent->_left;
				}
				if ((__w->_right == 0 || __w->_right->_color == ft::BLACK) &&
					(__w->_left == 0 || __w->_left->_color == ft::BLACK))
				{
					__w->_color = ft::RED;
					__x = __x_parent;
					__x_parent = __x_parent->_parent;
				}
				else
				{
					if (__w->_left == 0 || __w->_left->_color == ft::BLACK)
					{
						__w->_right->_color = ft::BLACK;
						__w->_color = ft::RED;
						RBT_rotate_left(__w, __root);
						__w = __x_parent->_left;
					}
					__w->_color = __x_parent->_color;
					__x_parent->_color = ft::BLACK;
					if (__w->_left)
						__w->_left->_color = ft::BLACK;
					RBT_rotate_right(__x_parent, __root);
					break;
				}
			}
		}
		if (__x)
			__x->_color = ft::BLACK;
	}
	return __y;
}