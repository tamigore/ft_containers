#ifndef _RBTREE_HPP_
# define _RBTREE_HPP_

# include "utility.hpp"
# include "pair.hpp"
# include <cassert>
# include <iostream>

namespace ft
{
	// data structure that represents a node in the tree
	#define LEFT  0
	#define RIGHT 1
	#define left  child[LEFT]
	#define right child[RIGHT]
	#define RED 1
	#define BLACK 0

	template <class Key, class T>
	class	Node
	{
		public:

			Key		key; // holds the key
			T		data;
			Node 	*parent; // pointer to the parent
			Node 	*child[2]; // pointer to child
			bool 	color; // 1 -> Red, 0 -> Black

			Node() : key(Key()), data(T()), parent(NULL)
			{
				left = NULL;
				right = NULL;
				color = BLACK;
			}

			Node(Key newKey) : key(newKey), data(T()), parent(NULL)
			{
				left = NULL;
				right = NULL;
				color = BLACK;
			}

			Node(Key newKey, T val) : key(newKey), data(val), parent(NULL)
			{
				left = NULL;
				right = NULL;
				color = BLACK;
			}
	};

	template <class Key, class T>
	bool	operator==(const ft::Node<Key, T> lhs, const ft::Node<Key, T> rhs)
	{ return (lhs.parent == rhs.parent && lhs.left == rhs.left && lhs.right == rhs.right && lhs.color == rhs.color); }

	template <class Key, typename T>
	bool	operator!=(const ft::Node<Key, T> lhs, const ft::Node<Key, T> rhs)
	{ return (lhs.parent != rhs.parent && lhs.left != rhs.left && lhs.right != rhs.right && lhs.color != rhs.color); }

	template <class Key, class T>
	void	printNode(Node<Key, T> *x)
	{
		std::cout << "_PrintNode_" << std::endl;
		if (x)
		{
			if (x->key)
				std::cout << "key :" << x->key<< std::endl;
			std::cout << "color :" <<(x->color == BLACK ? "BLACK" : "RED") << std::endl;
			std::cout << "data :" << x->data << std::endl;
		}
		else
			std::cout << "NULL" << std::endl;
		std::cout << "____________" << std::endl;
	};

	// class RBTree implements the operations in Red Black Tree
	template <class Key, class T>
	class RBTree
	{
		private:
			Node<Key, T>	*root;

			Node<Key, T>	*searchTreeHelper(Node<Key, T> *node, Key key)
			{
				if (node == NULL || key == node->key)
					return node;
				if (key < node->key)
					return searchTreeHelper(node->left, key);
				return searchTreeHelper(node->right, key);
			}

			// fix the rb tree modified by the delete operation 
			void	fixDelete(Node<Key, T> *x)
			{
				Node<Key, T>	*s;

				std::cout << "?" << std::endl;
				while (x && x != root && x->color == BLACK)
				{
					std::cout << "while" << std::endl;
					if (x == x->parent->left)
					{
						std::cout << "if" << std::endl;
						s = x->parent->right;
						if (s->color == 1)
						{
							// std::cout << "case 3.1" << std::endl;
							s->color = BLACK;
							x->parent->color = 1;
							rotate(x->parent, LEFT);
							s = x->parent->right;
						}
						if (s->left->color == BLACK && s->right->color == BLACK)
						{
							// std::cout << "case 3.2" << std::endl;
							s->color = 1;
							x = x->parent;
						} 
						else
						{
							if (s->right->color == BLACK)
							{
								// std::cout << "case 3.3" << std::endl;
								s->left->color = BLACK;
								s->color = 1;
								rotate(s, RIGHT);
								s = x->parent->right;
							} 
							// std::cout << "case 3.4" << std::endl;
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->right->color = BLACK;
							rotate(x->parent, LEFT);
							x = root;
						}
					}
					else
					{
						std::cout << "else" << std::endl;
						s = x->parent->left;
						if (s && s->color == 1)
						{
							std::cout << "case 3.1" << std::endl;
							s->color = BLACK;
							x->parent->color = 1;
							rotate(x->parent, RIGHT);
							s = x->parent->left;
						}
						if (s && s->right->color == BLACK && s->right->color == BLACK)
						{
							std::cout << "case 3.2" << std::endl;
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->left->color == BLACK)
							{
								std::cout << "case 3.3" << std::endl;
								s->right->color = BLACK;
								s->color = 1;
								rotate(s, LEFT);
								s = x->parent->left;
							}
							std::cout << "case 3.4" << std::endl;
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->left->color = BLACK;
							rotate(x->parent, RIGHT);
							x = root;
						}
					}
				}
				x->color = BLACK;
			}

			void	rbTransplant(Node<Key, T> *u, Node<Key, T> *v)
			{
				if (u->parent == NULL)
					root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void	deleteNodeHelper(Node<Key, T> *node, Key key)
			{
				// find the node containing key
				Node<Key, T>	*z = NULL;
				Node<Key, T>	*x, *y;

				std::cout << "deleteNodeHelper" << std::endl;
				printNode(node);
				while (node != NULL)
				{
					if (node->key == key)
						z = node;
					if (node->key <= key)
						node = node->right;
					else
						node = node->left;
				}
				if (z == NULL)
					return;
				y = z;
				bool y_original_color = y->color;
				if (z->left == NULL)
				{
					// std::cout << "if" << std::endl;
					x = z->right;
					rbTransplant(z, z->right);
				}
				else if (z->right == NULL)
				{
					// std::cout << "else if ?" << std::endl;
					x = z->left;
					rbTransplant(z, z->left);
				}
				else
				{
					// std::cout << "else ?" << std::endl;
					y = minimum(z->right);
					// std::cout << "?" << std::endl;
					y_original_color = y->color;
					// std::cout << "?" << std::endl;
					x = y->right;
					// std::cout << "?" << std::endl;
					if (y->parent == z)
						x->parent = y;
					else
					{
						rbTransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					// std::cout << "?" << std::endl;
					rbTransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				if (z)
					delete z;
				if (y_original_color == BLACK)
					fixDelete(x);
			}
			
			// fix the red-black tree
			void fixInsert(Node<Key, T> *k)
			{
				Node<Key, T> *u;

				while (k->parent->color == RED)
				{
					std::cout << "while ?" << std::endl;
					if (k->parent == k->parent->parent->right)
					{
						std::cout << "if ?" << std::endl;
						u = k->parent->parent->left; // uncle
						printNode(k);
						printNode(k->parent);
						printNode(k->parent->parent);
						printNode(u);
						if (u && u->color == RED) // case 3.1
						{
							std::cout << "if 2 ?" << std::endl;
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							std::cout << "else 2 ?" << std::endl;
							if (k == k->parent->left) // case 3.2.2
							{
								std::cout << "if 3 ?" << std::endl;
								k = k->parent;
								rotate(k, RIGHT);
							}
							// case 3.2.1
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							rotate(k->parent->parent, LEFT);
						}
					}
					else
					{
						u = k->parent->parent->right; // uncle

						if (u && u->color == RED)// mirror case 3.1
						{
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;	
						}
						else
						{
							if (k == k->parent->right)// mirror case 3.2.2
							{
								k = k->parent;
								rotate(k, LEFT);
							}
							// mirror case 3.2.1
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							rotate(k->parent->parent, RIGHT);
						}
					}
					if (k == root)
						break;
				}
				root->color = BLACK;
			}

			// fix the red-black tree
			// void	fixInsert(Node<Key, T> *k)
			// {
			// 	Node<Key, T>* u;

			// 	while (k->parent->color == 1)
			// 	{
			// 		if (k->parent == k->parent->parent->right)
			// 		{
			// 			u = k->parent->parent->left; // uncle
			// 			if (u->color == 1)
			// 			{
			// 				// case 3.1
			// 				u->color = BLACK;
			// 				k->parent->color = BLACK;
			// 				k->parent->parent->color = 1;
			// 				k = k->parent->parent;
			// 			}
			// 			else
			// 			{
			// 				if (k == k->parent->left)
			// 				{
			// 					// case 3.2.2
			// 					k = k->parent;
			// 					rotate(k, RIGHT);
			// 				}
			// 				// case 3.2.1
			// 				k->parent->color = BLACK;
			// 				k->parent->parent->color = 1;
			// 				rotate(k->parent->parent, LEFT);
			// 			}
			// 		}
			// 		else
			// 		{
			// 			u = k->parent->parent->right; // uncle

			// 			if (u->color == 1)
			// 			{
			// 				// mirror case 3.1
			// 				u->color = BLACK;
			// 				k->parent->color = BLACK;
			// 				k->parent->parent->color = 1;
			// 				k = k->parent->parent;	
			// 			}
			// 			else
			// 			{
			// 				if (k == k->parent->right)
			// 				{
			// 					// mirror case 3.2.2
			// 					k = k->parent;
			// 					rotate(k, LEFT);
			// 				}
			// 				// mirror case 3.2.1
			// 				k->parent->color = BLACK;
			// 				k->parent->parent->color = 1;
			// 				rotate(k->parent->parent, RIGHT);
			// 			}
			// 		}
			// 		if (k == root)
			// 			break;
			// 	}
			// 	root->color = BLACK;
			// }

			void	printHelper(Node<Key, T>* root, std::string indent, bool last)
			{
				// print the tree structure on the screen
				if (root != NULL)
				{
					std::cout << indent;
					if (last)
					{
						std::cout<<"R----";
						indent += "     ";
					}
					else
					{
						std::cout<<"L----";
						indent += "|    ";
					}
					std::string sColor = root->color?"RED":"BLACK";
					std::cout << root->key << "("<< sColor << ")" << std::endl;
					printHelper(root->left, indent, false);
					printHelper(root->right, indent, true);
				}
			}

		public:
			RBTree()
			{
				root = NULL;
			}

			RBTree(const RBTree& other)
			{
				*this = other;
			}

			~RBTree()
			{
				Node<Key, T> *min;
				Node<Key, T> *max;

				while (root)
				{
					min = this->minimum(root);
					max = this->maximum(root);
					if (min != root)
					{
						// printNode(min);
						deleteNode(min->key);
					}
					else if (max != root && max != min)
					{
						// printNode(max);
						deleteNode(max->key);
					}
					else
					{
						// printNode(root);
						deleteNode(root->key);
					}
				}
			}

			RBTree &operator=(const RBTree& other)
			{
				if (&other == this)
					return (*this);
				if (!other.getRoot())
					root = NULL;
				else
					root = other.getRoot();
				return (*this);
			}

			// search the tree for the key k and return the corresponding node
			Node<Key, T>	*searchTree(Key k)
			{
				return searchTreeHelper(this->root, k);
			}

			Node<Key, T>	*minimum(Node<Key, T> *node)// find the node with the minimum key
			{
				while (node->left != NULL)
					node = node->left;
				return node;
			}

			Node<Key, T>	*maximum(Node<Key, T> *node)// find the node with the maximum key
			{
				while (node->right != NULL)
					node = node->right;
				return node;
			}

			Node<Key, T>	*successor(Node<Key, T> *x)
			{
				// if the right subtree is not nullhe successor is the leftmost node in the right subtree
				if (x->right != NULL)
					return minimum(x->right);
				// else it is the lowest ancestor of x whose left child is also an ancestor of x.
				Node<Key, T> *y = x->parent;
				while (y != NULL && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			// find the predecessor of a given node
			Node<Key, T>	*predecessor(Node<Key, T> *x)
			{
				// if the left subtree is not nullhe predecessor is the rightmost node in the left subtree
				if (x->left != NULL && x->left != NULL)
					return maximum(x->left);
				// else it is the highest ancestor of x whose right child is also an ancestor of x.
				Node<Key, T> *y = x->parent;
				while (y != NULL && y != NULL && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			void	rotate(Node<Key, T> *x, int dir)// rotate node in dir
			{
				int l = 0;
				int r = 1;
				if (dir == 1)
				{
					l = 1;
					r = 0;
				}
				Node<Key, T>* y = x->child[r];
				x->child[r] = y->child[l];
				if (y->child[l] != NULL)
					y->child[l]->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					this->root = y;
				else if (x == x->parent->child[l])
					x->parent->child[l] = y;
				else
					x->parent->child[r] = y;
				y->child[l] = x;
				x->parent = y;
			}

			// insert the key to the tree in its appropriate position and fix the tree
			void	insert(Node<Key, T> *node)// Ordinary Binary Search Insertion
			{
				Node<Key, T> *y = NULL;
				Node<Key, T> *x = this->root;

				while (x != NULL) //find node parent
				{
					y = x;
					if (node->key < x->key)
						x = x->left;
					else
						x = x->right;
				}
				node->parent = y; // y is parent of x
				if (y == NULL)
					root = node;
				else if (node->key < y->key)
					y->left = node;
				else
					y->right = node;
				if (node->parent == NULL) // if new node is a root node, simply return
				{
					node->color = BLACK;
					return ;
				}
				if (node->parent->parent == NULL)// if the grandparent is null, simply return
					return ;
				fixInsert(node);// Fix the tree
			}

			// insert the key to the tree in its appropriate position and fix the tree
			void	insert(Key key)// Ordinary Binary Search Insertion
			{
				Node<Key, T> *node = new Node<Key, T>(key);
				node->color = RED;
				insert(node);
				printNode(node);
			}

			void	insert(Key key, T val)// Ordinary Binary Search Insertion
			{
				Node<Key, T> *node = new Node<Key, T>(key, val);
				node->color = RED;
				insert(node);
				printNode(node);
			}

			Node<Key, T>	*getRoot()// retrun root
			{
				return this->root;
			}

			void	deleteNode(Key key)// delete the node from the tree
			{
				deleteNodeHelper(this->root, key);
			}

			// void	deleteNode(Key key, Node<Key, T> *node)// delete the node from the tree
			// {
			// 	deleteNodeHelper(node, key);
			// }

			void	prettyPrint()// print the tree structure on the screen
			{
				if (root)
					printHelper(this->root, "", true);
			}
	};
} // namespace ft

#endif