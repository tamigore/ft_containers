#include "RBTree.hpp"

static ft::Node_base*	localRBT_increment(ft::Node_base* __x) throw ()
{
	if (__x->_M_right != 0) 
	{
		__x = __x->_M_right;
		while (__x->_M_left != 0)
			__x = __x->_M_left;
	}
	else 
	{
		ft::Node_base* __y = __x->_M_parent;
		while (__x == __y->_M_right) 
		{
			__x = __y;
			__y = __y->_M_parent;
		}
		if (__x->_M_right != __y)
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
	if (__x->_M_color == ft::RED && __x->_M_parent->_M_parent == __x)
		__x = __x->_M_right;
	else if (__x->_M_left != 0)
	{
		ft::Node_base* __y = __x->_M_left;s
		while (__y->_M_right != 0)
			__y = __y->_M_right;
		__x = __y;
	}
	else
	{
		ft::Node_base* __y = __x->_M_parent;
		while (__x == __y->_M_left)
		{
			__x = __y;
			__y = __y->_M_parent;
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
		if (__node->_M_color == ft::BLACK)
			++__sum;
		if (__node == __root)
			break;
		__node = __node->_M_parent;
	}
	while (1);
	return __sum;
}

void	ft::RBT_rotate_left(ft::Node_base* const __x, ft::Node_base*& __root)
{
	ft::Node_base* const __y = __x->_M_right;

	__x->_M_right = __y->_M_left;
	if (__y->_M_left !=0)
		__y->_M_left->_M_parent = __x;
	__y->_M_parent = __x->_M_parent;

	if (__x == __root)
		__root = __y;
	else if (__x == __x->_M_parent->_M_left)
		__x->_M_parent->_M_left = __y;
	else
		__x->_M_parent->_M_right = __y;
	__y->_M_left = __x;
	__x->_M_parent = __y;
}

void	ft::RBT_rotate_right(ft::Node_base* const __x, ft::Node_base*& __root)
{
	ft::Node_base* const __y = __x->_M_left;

	__x->_M_left = __y->_M_right;
	if (__y->_M_right != 0)
		__y->_M_right->_M_parent = __x;
	__y->_M_parent = __x->_M_parent;

	if (__x == __root)
		__root = __y;
	else if (__x == __x->_M_parent->_M_right)
		__x->_M_parent->_M_right = __y;
	else
		__x->_M_parent->_M_left = __y;
	__y->_M_right = __x;
	__x->_M_parent = __y;
}

void	ft::RBT_insert_rebalance(const bool __insert_left, ft::Node_base* __x, ft::Node_base* __p, ft::Node_base& __header) throw ()
{
	ft::Node_base *& __root = __header._M_parent;

	// Initialize fields in new node to insert.
	__x->_M_parent = __p;
	__x->_M_left = 0;
	__x->_M_right = 0;
	__x->_M_color = ft::RED;

	// Insert.
	// Make new node child of parent and maintain root, leftmost and
	// rightmost nodes.
	// N.B. First node is always inserted left.
	if (__insert_left)
	{
		__p->_M_left = __x; // also makes leftmost = __x when __p == &__header

		if (__p == &__header)
		{
			__header._M_parent = __x;
			__header._M_right = __x;
		}
		else if (__p == __header._M_left)
			__header._M_left = __x; // maintain leftmost pointing to min node
	}
	else
	{
		__p->_M_right = __x;

		if (__p == __header._M_right)
			__header._M_right = __x; // maintain rightmost pointing to max node
	}
	// Rebalance.
	while (__x != __root && __x->_M_parent->_M_color == ft::RED)
	{
		ft::Node_base* const __xpp = __x->_M_parent->_M_parent;

		if (__x->_M_parent == __xpp->_M_left)
		{
			ft::Node_base* const __y = __xpp->_M_right;
			if (__y && __y->_M_color == ft::RED)
			{
				__x->_M_parent->_M_color = ft::BLACK;
				__y->_M_color = ft::BLACK;
				__xpp->_M_color = ft::RED;
				__x = __xpp;
			}
			else
			{
				if (__x == __x->_M_parent->_M_right)
				{
					__x = __x->_M_parent;
					RBT_rotate_left(__x, __root);
				}
				__x->_M_parent->_M_color = ft::BLACK;
				__xpp->_M_color = ft::RED;
				RBT_rotate_right(__xpp, __root);
			}
		}
		else
		{
			ft::Node_base* const __y = __xpp->_M_left;
			if (__y && __y->_M_color == ft::RED)
			{
				__x->_M_parent->_M_color = ft::BLACK;
				__y->_M_color = ft::BLACK;
				__xpp->_M_color = ft::RED;
				__x = __xpp;
			}
			else
			{
				if (__x == __x->_M_parent->_M_left)
				{
					__x = __x->_M_parent;
					RBT_rotate_right(__x, __root);
				}
				__x->_M_parent->_M_color = ft::BLACK;
				__xpp->_M_color = ft::RED;
				RBT_rotate_left(__xpp, __root);
			}
		}
	}
	__root->_M_color = ft::BLACK;
}

ft::Node_base*	ft::RBT_erase_rebalance(ft::Node_base* const __z, ft::Node_base& __header) throw ()
{
	ft::Node_base *& __root = __header._M_parent;
	ft::Node_base *& __leftmost = __header._M_left;
	ft::Node_base *& __rightmost = __header._M_right;
	ft::Node_base* __y = __z;
	ft::Node_base* __x = 0;
	ft::Node_base* __x_parent = 0;

	if (__y->_M_left == 0)     // __z has at most one non-null child. y == z.
		__x = __y->_M_right;     // __x might be null.
	else
		if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
			__x = __y->_M_left;    // __x is not null.
	else
	{
		// __z has two non-null children.  Set __y to
		__y = __y->_M_right;   //   __z's successor.  __x might be null.
		while (__y->_M_left != 0)
			__y = __y->_M_left;
		__x = __y->_M_right;
	}
	if (__y != __z)
	{
		// relink y in place of z.  y is z's successor
		__z->_M_left->_M_parent = __y;
		__y->_M_left = __z->_M_left;
		if (__y != __z->_M_right)
		{
			__x_parent = __y->_M_parent;
			if (__x) __x->_M_parent = __y->_M_parent;
			__y->_M_parent->_M_left = __x;   // __y must be a child of _M_left
			__y->_M_right = __z->_M_right;
			__z->_M_right->_M_parent = __y;
		}
		else
			__x_parent = __y;
		if (__root == __z)
			__root = __y;
		else if (__z->_M_parent->_M_left == __z)
			__z->_M_parent->_M_left = __y;
		else
			__z->_M_parent->_M_right = __y;
		__y->_M_parent = __z->_M_parent;
		std::swap(__y->_M_color, __z->_M_color);
		__y = __z;
		// __y now points to node to be actually deleted
	}
	else
	{ // __y == __z
		__x_parent = __y->_M_parent;
		if (__x)
			__x->_M_parent = __y->_M_parent;
		if (__root == __z)
			__root = __x;
		else
			if (__z->_M_parent->_M_left == __z)
				__z->_M_parent->_M_left = __x;
			else
				__z->_M_parent->_M_right = __x;
		if (__leftmost == __z)
		{
			if (__z->_M_right == 0)        // __z->_M_left must be null also
				__leftmost = __z->_M_parent;
			// makes __leftmost == _M_header if __z == __root
			else
				__leftmost = ft::Node_base::_S_minimum(__x);
		}
		if (__rightmost == __z)
		{
			if (__z->_M_left == 0)         // __z->_M_right must be null also
				__rightmost = __z->_M_parent;
			// makes __rightmost == _M_header if __z == __root
			else                      // __x == __z->_M_left
				__rightmost = ft::Node_base::_S_maximum(__x);
		}
	}
	if (__y->_M_color != ft::RED)
	{
		while (__x != __root && (__x == 0 || __x->_M_color == ft::BLACK))
		{
			if (__x == __x_parent->_M_left)
			{
				ft::Node_base* __w = __x_parent->_M_right;
				if (__w->_M_color == ft::RED)
				{
					__w->_M_color = ft::BLACK;
					__x_parent->_M_color = ft::RED;
					RBT_rotate_left(__x_parent, __root);
					__w = __x_parent->_M_right;
				}
				if ((__w->_M_left == 0 || __w->_M_left->_M_color == ft::BLACK) &&
					(__w->_M_right == 0 || __w->_M_right->_M_color == ft::BLACK))
				{
					__w->_M_color = ft::RED;
					__x = __x_parent;
					__x_parent = __x_parent->_M_parent;
				}
				else
				{
					if (__w->_M_right == 0 || __w->_M_right->_M_color == ft::BLACK)
					{
						__w->_M_left->_M_color = ft::BLACK;
						__w->_M_color = ft::RED;
						RBT_rotate_right(__w, __root);
						__w = __x_parent->_M_right;
					}
					__w->_M_color = __x_parent->_M_color;
					__x_parent->_M_color = ft::BLACK;
					if (__w->_M_right)
						__w->_M_right->_M_color = ft::BLACK;
					RBT_rotate_left(__x_parent, __root);
					break;
				}
			}
			else
			{
				// same as above, with _M_right <-> _M_left.
				ft::Node_base* __w = __x_parent->_M_left;
				if (__w->_M_color == ft::RED)
				{
					__w->_M_color = ft::BLACK;
					__x_parent->_M_color = ft::RED;
					RBT_rotate_right(__x_parent, __root);
					__w = __x_parent->_M_left;
				}
				if ((__w->_M_right == 0 || __w->_M_right->_M_color == ft::BLACK) &&
					(__w->_M_left == 0 || __w->_M_left->_M_color == ft::BLACK))
				{
					__w->_M_color = ft::RED;
					__x = __x_parent;
					__x_parent = __x_parent->_M_parent;
				}
				else
				{
					if (__w->_M_left == 0 || __w->_M_left->_M_color == ft::BLACK)
					{
						__w->_M_right->_M_color = ft::BLACK;
						__w->_M_color = ft::RED;
						RBT_rotate_left(__w, __root);
						__w = __x_parent->_M_left;
					}
					__w->_M_color = __x_parent->_M_color;
					__x_parent->_M_color = ft::BLACK;
					if (__w->_M_left)
						__w->_M_left->_M_color = ft::BLACK;
					RBT_rotate_right(__x_parent, __root);
					break;
				}
			}
		}
		if (__x)
			__x->_M_color = ft::BLACK;
	}
	return __y;
}