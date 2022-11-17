#ifndef _RBTREE_HPP_
# define _RBTREE_HPP_

# include "utility.hpp"
# include <cassert>
# include <iostream>

# define NIL NULL
# define LEFT  0
# define RIGHT 1
# define left  child[LEFT]
# define right child[RIGHT]

namespace ft
{
	// data structure that represents a node in the tree
	#define RED 1
	#define BLACK 0

	template <class T>
	struct Node
	{
		T	data;
		int key; // holds the key
		Node *parent; // pointer to the parent
		Node *child[2]; // pointer to child
		int color; // 1 -> Red, 0 -> Black
	};
	
	template <class T>
	void	printNode(Node<T> *x)
	{
		std::cout << "key :" << x->key << " | color :" <<(x->color == BLACK ? "BLACK" : "RED") << " | data :" << x->data << std::endl;
	};

	// class RBTree implements the operations in Red Black Tree
	template <class T>
	class RBTree
	{
		private:
			Node<T> *root;
			Node<T> *TNULL;

			Node<T>	*searchTreeHelper(Node<T> *node, int key)
			{
				if (node == TNULL || key == node->key)
					return node;
				if (key < node->key)
					return searchTreeHelper(node->left, key);
				return searchTreeHelper(node->right, key);
			}

			// fix the rb tree modified by the delete operation
			void fixDelete(Node<T> *x)
			{
				Node<T>	*s;
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

			void rbTransplant(Node<T>* u, Node<T>* v)
			{
				if (u->parent == NULL)
					root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void deleteNodeHelper(Node<T>* node, int key)
			{
				// find the node containing key
				Node<T>	*z = TNULL;
				Node<T>	*x, *y;
				while (node != TNULL)
				{
					if (node->key == key)
						z = node;
					if (node->key <= key)
						node = node->right;
					else
						node = node->left;
				}
				if (z == TNULL)
				{
					std::cout<<"Couldn't find key in the tree"<<std::endl;
					return;
				} 
				y = z;
				int y_original_color = y->color;
				if (z->left == TNULL)
				{
					x = z->right;
					rbTransplant(z, z->right);
				}
				else if (z->right == TNULL)
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
				delete z;
				if (y_original_color == BLACK)
					fixDelete(x);
			}
			
			// fix the red-black tree
			void fixInsert(Node<T>* k)
			{
				Node<T>* u;
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

			void printHelper(Node<T>* root, std::string indent, bool last)
			{
				// print the tree structure on the screen
				if (root != TNULL)
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
				TNULL = new Node<T>;
				TNULL->data = T();
				TNULL->color = BLACK;
				TNULL->left = NULL;
				TNULL->right = NULL;
				root = TNULL;
			}

			~RBTree()
			{
				Node<T> *min;
				Node<T> *max;

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
						delete TNULL;
						return ;
					}
				}
			}

			// search the tree for the key k and return the corresponding node
			Node<T>* searchTree(int k)
			{
				return searchTreeHelper(this->root, k);
			}

			Node<T>* minimum(Node<T>* node)// find the node with the minimum key
			{
				while (node->left != TNULL)
					node = node->left;
				return node;
			}

			Node<T>* maximum(Node<T>* node)// find the node with the maximum key
			{
				while (node->right != TNULL)
					node = node->right;
				return node;
			}

			void	rotate(Node<T> *x, int dir)// rotate node in dir
			{
				int l = 0;
				int r = 1;
				if (dir == 1)
				{
					l = 1;
					r = 0;
				}
				Node<T>* y = x->child[r];
				x->child[r] = y->child[l];
				if (y->child[l] != TNULL)
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
			void insert(int key)// Ordinary Binary Search Insertion
			{
				Node<T>* node = new Node<T>;
				node->parent = NULL;
				node->key = key;
				node->data = T();
				node->left = TNULL;
				node->right = TNULL;
				node->color = 1; // new node must be red

				Node<T>* y = NULL;
				Node<T>* x = this->root;

				while (x != TNULL)
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

			void insert(int key, T data) // Ordinary Binary Search Insertion
			{
				Node<T>* node = new Node<T>;
				node->parent = NULL;
				node->key = key;
				node->data = data;
				node->left = TNULL;
				node->right = TNULL;
				node->color = 1; // new node must be red

				Node<T>* y = NULL;
				Node<T>* x = this->root;

				while (x != TNULL) // compare key to insert min values left and max right
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

			Node<T>* getRoot()// retrun root
			{
				return this->root;
			}

			void deleteNode(int key)// delete the node from the tree
			{
				deleteNodeHelper(this->root, key);
			}

			void prettyPrint()// print the tree structure on the screen
			{
				if (root)
					printHelper(this->root, "", true);
			}
	};
} // namespace ft

#endif