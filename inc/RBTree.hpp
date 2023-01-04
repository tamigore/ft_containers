#ifndef _RBTREE_HPP_
# define _RBTREE_HPP_

# include "utility.hpp"
# include "pair.hpp"
# include <cassert>
# include <iostream>

namespace ft
{
	// data structure that represents a node in the tree
	#define LEFT	0
	#define RIGHT	1
	#define left	child[LEFT]
	#define right	child[RIGHT]
	#define RED		1
	#define BLACK	0

	template <class Key, class T>
	class Node
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

			Node<Key, T> operator=(Node<Key, T> &other)
			{
				if (&other == NULL)
					return (Node<Key, T>());
				key = other.key;
				data = other.data;
				parent = other.parent;
				left = other.left;
				right = other.right;
				color = other.color;
			}
	};

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
			Node<Key, T>					*root;
			Node<Key, T>					TNULL;
			std::allocator<Node<Key, T> >	alloc;

			Node<Key, T>	*searchTreeHelper(Node<Key, T> *node, Key key)
			{
				if (node == &TNULL || key == node->key)
					return node;
				if (key < node->key)
					return searchTreeHelper(node->left, key);
				return searchTreeHelper(node->right, key);
			}

			// fix the rb tree modified by the delete operation
			void fixDelete(Node<Key, T> *x)
			{
				Node<Key, T>	*s;
				while (x != root && x->color == BLACK)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						if (s->color == 1)
						{
							// case 3.1
							s->color = BLACK;
							x->parent->color = 1;
							rotate(x->parent, LEFT);
							s = x->parent->right;
						}
						if (s->left->color == BLACK && s->right->color == BLACK)
						{
							// case 3.2
							s->color = 1;
							x = x->parent;
						} 
						else
						{
							if (s->right->color == BLACK)
							{
								// case 3.3
								s->left->color = BLACK;
								s->color = 1;
								rotate(s, RIGHT);
								s = x->parent->right;
							} 

							// case 3.4
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->right->color = BLACK;
							rotate(x->parent, LEFT);
							x = root;
						}
					}
					else
					{
						s = x->parent->left;
						if (s->color == 1)
						{
							// case 3.1
							s->color = BLACK;
							x->parent->color = 1;
							rotate(x->parent, RIGHT);
							s = x->parent->left;
						}

						if (s->right->color == BLACK && s->right->color == BLACK)
						{
							// case 3.2
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->left->color == BLACK)
							{
								// case 3.3
								s->right->color = BLACK;
								s->color = 1;
								rotate(s, LEFT);
								s = x->parent->left;
							} 

							// case 3.4
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

			void rbTransplant(Node<Key, T>* u, Node<Key, T>* v)
			{
				if (u->parent == NULL)
					root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			bool	deleteNodeHelper(Node<Key, T>* node, Key key)
			{
				// find the node containing key
				Node<Key, T>	*z = &TNULL;
				Node<Key, T>	*x, *y;

				while (node != &TNULL)
				{
					if (node->key == key)
						z = node;
					if (node->key <= key)
						node = node->right;
					else
						node = node->left;
				}
				if (z == &TNULL)
					return (false);
				y = z;
				bool y_original_color = y->color;
				if (z->left == &TNULL)
				{
					x = z->right;
					rbTransplant(z, z->right);
				}
				else if (z->right == &TNULL)
				{
					x = z->left;
					rbTransplant(z, z->left);
				}
				else
				{
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else
					{
						rbTransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					rbTransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				// alloc.deallocate(z);
				delete z;
				if (y_original_color == BLACK)
					fixDelete(x);
				return (true);
			}
			
			// fix the red-black tree
			void fixInsert(Node<Key, T>* k)
			{
				Node<Key, T>* u;
				while (k->parent->color == 1)
				{
					if (k->parent == k->parent->parent->right)
					{
						u = k->parent->parent->left; // uncle
						if (u->color == 1)
						{
							// case 3.1
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left)
							{
								// case 3.2.2
								k = k->parent;
								rotate(k, RIGHT);
							}
							// case 3.2.1
							k->parent->color = BLACK;
							k->parent->parent->color = 1;
							rotate(k->parent->parent, LEFT);
						}
					}
					else
					{
						u = k->parent->parent->right; // uncle

						if (u->color == 1)
						{
							// mirror case 3.1
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = 1;
							k = k->parent->parent;	
						}
						else
						{
							if (k == k->parent->right)
							{
								// mirror case 3.2.2
								k = k->parent;
								rotate(k, LEFT);
							}
							// mirror case 3.2.1
							k->parent->color = BLACK;
							k->parent->parent->color = 1;
							rotate(k->parent->parent, RIGHT);
						}
					}
					if (k == root)
						break;
				}
				root->color = BLACK;
			}

			void printHelper(Node<Key, T>* root, std::string indent, bool last)
			{
				// print the tree structure on the screen
				if (root != &TNULL)
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
					std::cout<<root->key<<"("<<sColor<<")"<<std::endl;
					printHelper(root->left, indent, false);
					printHelper(root->right, indent, true);
				}
			}

		public:
			RBTree()
			{
				root = &TNULL;
			}

			~RBTree()
			{
				Node<Key, T> *min;
				Node<Key, T> *max;

				while (root && root != &TNULL)
				{
					min = this->minimum(root);
					if (min && min != root && min != &TNULL)
						deleteNode(min->key);
					else
					{
						max = this->maximum(root);
						if (max && max != root && max != min && max != &TNULL)
							deleteNode(max->key);
						deleteNode(root->key);
						return ;
					}
				}
			}

			// search the tree for the key k and return the corresponding node
			Node<Key, T>* searchTree(Key k)
			{
				return searchTreeHelper(this->root, k);
			}

			Node<Key, T>* minimum(Node<Key, T>* node)// find the node with the minimum key
			{
				while (node && node != &TNULL && node->left != &TNULL)
					node = node->left;
				return node;
			}

			Node<Key, T>* maximum(Node<Key, T>* node)// find the node with the maximum key
			{
				while (node && node != &TNULL && node->right != &TNULL)
					node = node->right;
				return node;
			}

			Node<Key, T> *successor(Node<Key, T> *x)
			{
				if (!x)
					return (&TNULL);
				// if the right subtree is not nullhe successor is the leftmost node in the right subtree
				if (x->right != &TNULL)
					return minimum(x->right);
				// else it is the lowest ancestor of x whose left child is also an ancestor of x.
				Node<Key, T> *y = x->parent;
				while (y && y != &TNULL && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				if (!y)
					y = &TNULL;
				return y;
			}

			// find the predecessor of a given node
			Node<Key, T> *predecessor(Node<Key, T> *x)
			{
				if (!x)
					return (&TNULL);
				// if the left subtree is not nullhe predecessor is the rightmost node in the left subtree
				if (x->left != &TNULL)
					return maximum(x->left);
				// else it is the highest ancestor of x whose right child is also an ancestor of x.
				Node<Key, T> *y = x->parent;
				while (y && y != &TNULL && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				if (!y)
					y = &TNULL;
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
				if (y->child[l] != &TNULL)
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

			// insert Node to the tree in its appropriate position and fix the tree
			void insert(Node<Key, T>* node)// Ordinary Binary Search Insertion
			{
				node->parent = NULL;
				node->left = &TNULL;
				node->right = &TNULL;
				node->color = RED; // new node must be red

				Node<Key, T>* y = NULL;
				Node<Key, T>* x = this->root;
				while (x != &TNULL)
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
					node->color = BLACK;
				else if (node->parent->parent == NULL)// if the grandparent is null, simply return
					return;
				else // Fix the tree
					fixInsert(node);
			}

			void insert(Key key)
			{
				// Node<Key, T>* node = alloc.allocate(1);
				// *node = Node<Key, T>(key);
				Node<Key, T>* node = new Node<Key, T>(key);
				insert(node);
			}

			void insert(Key key, T val)
			{
				// Node<Key, T>* node = alloc.allocate(1);
				// *node = Node<Key, T>(key, val);
				Node<Key, T>* node = new Node<Key, T>(key, val);
				insert(node);
			}

			Node<Key, T>* getRoot()// retrun root
			{
				return (this->root);
			}

			Node<Key, T>* getNULL()// retrun NULL node
			{
				return (&this->TNULL);
			}

			bool	deleteNode(Key key)// delete the node from the tree
			{
				return (deleteNodeHelper(this->root, key));
			}

			void prettyPrint()// print the tree structure on the screen
			{
				if (root && root != &TNULL)
					printHelper(this->root, "", true);
				else
					std::cout << "RBtree NULL..." << std::endl;
			}
	};
} // namespace ft

#endif