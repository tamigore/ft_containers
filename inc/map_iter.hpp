#ifndef _MAP_ITER_HPP_
# define _MAP_ITER_HPP_

# include <cstddef>
# include "utility.hpp"
# include "iterator.hpp"
# include "RBTree.hpp"
# include "pair.hpp"

namespace ft
{
	template <class Key, class T>
	class map_iterator : ft::iterator<std::bidirectional_iterator_tag, T>
	{		
		public:
			typedef typename ft::iterator_traits<T*>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T*>::value_type		value_type;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::reference			reference;
			typedef typename ft::RBTree<Key, T>							Tree;
			typedef typename ft::Node<Key, T>							TNode;


			map_iterator(void) : _tree(NULL), _node(NULL) {}

			map_iterator(Tree *tree, TNode *node) : _tree(tree), _node(node) {}

			map_iterator(const map_iterator& op) : _tree(op._tree), _node(op._node) {}

			map_iterator &operator=(const map_iterator& op)
			{
				if (this == &op)
					return (*this);
				this->_tree = op._tree;
				this->_node = op._node;
				return (*this);
			}

			virtual ~map_iterator() {}

			pointer base() const
			{ return (&(this->_node->data)); }

			reference operator*(void) const
			{ return (*base()); }

			pointer operator->(void)
			{ return &(this->operator*()); }

			pointer operator->(void) const
			{ return &(this->operator*()); }

			map_iterator& operator++(void)
			{
				_node = _tree->successor(_node);
				return (*this);
			}

			map_iterator operator++(int)
			{
				map_iterator rtn(*this);
				operator++();
				return (rtn);
			}

			map_iterator& operator--(void)
			{
				_node = _tree->predecessor(_node);
				return (*this);
			}

			map_iterator operator--(int)
			{
				map_iterator rtn(*this);
				operator--();
				return (rtn);
			}

			map_iterator operator+(difference_type n) const
			{
				map_iterator rtn(*this);

				while (n > 0 && rtn._node)
				{
					rtn._node = rtn._tree->successor(rtn._node);
					n--;
				} 
				return (rtn);
			}

			map_iterator operator-(difference_type n) const
			{
				map_iterator rtn(*this);

				while (n > 0 && rtn._node)
				{
					rtn._node = rtn._tree->predecessor(rtn._node);
					n--;
				} 
				return (rtn);
			}

			map_iterator& operator+=(difference_type n)
			{
				*this += n;
				return (*this);
			}

			map_iterator& operator-=(difference_type n)
			{
				*this -= n;
				return (*this);
			}

			reference operator[](difference_type n)
			{ return (*(operator+(n))); }

			operator map_iterator<const Key, T> () const
			{ return (map_iterator<const Key, T>(this->_tree, this->_node)); }
			
		public:
			Tree		*_tree;
			TNode		*_node;
	};

	template <class T1, class T2>
	std::ostream	&operator<<(std::ostream &os, const map_iterator<T1,T2> &x)
	{
		if (x._node && x._tree && x._node != x._tree->getNULL())
			os << "[" << x->first << "," << x->second << "]";
		else if (!x._node)
			os << "node NULL" << std::endl;
		else if (!x._tree)
			os << "tree NULL" << std::endl;
		else
			os << "NULL" << std::endl;
		return (os);
	}

	template <class Key, class T>
	typename ft::map_iterator<Key, T>::difference_type
	operator==(const ft::map_iterator<Key, T> lhs, const ft::map_iterator<Key, T> rhs)
	{ return (lhs.base() == rhs.base()); }

	template <class Key_L, class T_L, class Key_R, class T_R>
	bool	operator==(const ft::map_iterator<Key_L, T_L> lhs, const ft::map_iterator<Key_R, T_R> rhs)
	{ return (lhs.base() == rhs.base()); }

	template <class Key, class T>
	bool	operator!=(const ft::map_iterator<Key, T> lhs, const ft::map_iterator<Key, T> rhs)
	{ return (lhs.base() != rhs.base()); }

	template <class Key_L, class T_L, class Key_R, class T_R>
	bool	operator!=(const ft::map_iterator<Key_L, T_L> lhs, const ft::map_iterator<Key_R, T_R> rhs)
	{ return (lhs.base() != rhs.base()); }

	template <class Key, class T>
	bool	operator<(const ft::map_iterator<Key, T> lhs,
			  const ft::map_iterator<Key, T> rhs)
	{ return (lhs.base() < rhs.base()); }

	template <class Key_L, class T_L, class Key_R, class T_R>
	bool	operator<(const ft::map_iterator<Key_L, T_L> lhs, const ft::map_iterator<Key_R, T_R> rhs)
	{ return (lhs.base() < rhs.base()); }

	template <class Key, class T>
	bool	operator>(const ft::map_iterator<Key, T> lhs, const ft::map_iterator<Key, T> rhs)
	{ return (lhs.base() > rhs.base()); }

	template <class Key_L, class T_L, class Key_R, class T_R>
	bool	operator>(const ft::map_iterator<Key_L, T_L> lhs, const ft::map_iterator<Key_R, T_R> rhs)
	{ return (lhs.base() > rhs.base()); }

	template <class Key, class T>
	bool	operator<=(const ft::map_iterator<Key, T> lhs, const ft::map_iterator<Key, T> rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <class Key_L, class T_L, class Key_R, class T_R>
	bool	operator<=(const ft::map_iterator<Key_L, T_L> lhs, const ft::map_iterator<Key_R, T_R> rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <class Key, class T>
	bool	operator>=(const ft::map_iterator<Key, T> lhs, const ft::map_iterator<Key, T> rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <class Key_L, class T_L, class Key_R, class T_R>
	bool	operator>=(const ft::map_iterator<Key_L, T_L> lhs, const ft::map_iterator<Key_R, T_R> rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <class Key, class T>
	ft::map_iterator<Key, T>
	operator+(typename ft::map_iterator<Key, T>::difference_type n, typename ft::map_iterator<Key, T>& rai)
	{ return (&(*rai) + n); }

	template <class Key, class T>
	typename ft::map_iterator<Key, T>::difference_type
	operator-(const ft::map_iterator<Key, T> lhs, const ft::map_iterator<Key, T> rhs)
	{ return (lhs.base() - rhs.base()); }

	template <class Key_L, class T_L, class Key_R, class T_R>
	typename ft::map_iterator<Key_L, T_L>::difference_type
	operator-(const ft::map_iterator<Key_L, T_L> lhs, const ft::map_iterator<Key_R, T_R> rhs)
	{ return (lhs.base() - rhs.base()); }

	template <class Iterator>
	class reverse_map_iterator
	{		
		public:

			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			
			reverse_map_iterator() : _content() {}
			
			explicit reverse_map_iterator (iterator_type it) : _content(it) {}
		   
			template <class Iter>
			reverse_map_iterator (const reverse_map_iterator<Iter>& rev_it) : _content(rev_it.base()) {}

			virtual ~reverse_map_iterator() {}
			
			iterator_type base() const
			{ return (_content); }

			reference operator*() const
			{
				iterator_type tmp = _content;
				return (*(--tmp));
			}

			reverse_map_iterator operator+ (difference_type n) const
			{ return (reverse_map_iterator(_content - n)); }

			reverse_map_iterator& operator++()
			{
				--_content;
				return (*this);
			}

			reverse_map_iterator operator++(int)
			{
				reverse_map_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_map_iterator& operator+= (difference_type n)
			{
				_content -= n;
				return (*this);
			}

			reverse_map_iterator operator- (difference_type n) const
			{ return (reverse_map_iterator(_content + n)); }

			reverse_map_iterator& operator--()
			{
				++_content;
				return (*this);
			}

			reverse_map_iterator operator--(int)
			{
				reverse_map_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			reverse_map_iterator& operator-= (difference_type n)
			{
				_content += n;
				return (*this);
			}

			pointer operator->() const
			{ return &(operator*()); }

			reference operator[] (difference_type n) const
			{ return (this->base()[-n - 1]); }
	
		private:
			iterator_type	_content;
	};

	template <class Iterator>
	bool operator== (const reverse_map_iterator<Iterator>& lhs, const reverse_map_iterator<Iterator>& rhs)
	{ return (rhs.base() == lhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator== (const reverse_map_iterator<Iterator_L>& lhs, const reverse_map_iterator<Iterator_R>& rhs)
	{ return (rhs.base() == lhs.base()); }

	template <class Iterator>
	bool operator!= (const reverse_map_iterator<Iterator>& lhs, const reverse_map_iterator<Iterator>& rhs)
	{ return (rhs.base() != lhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator!= (const reverse_map_iterator<Iterator_L>& lhs, const reverse_map_iterator<Iterator_R>& rhs)
	{ return (rhs.base() != lhs.base()); }

	template <class Iterator>
	bool operator< (const reverse_map_iterator<Iterator>& lhs,const reverse_map_iterator<Iterator>& rhs)
	{ return (rhs.base() > lhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator< (const reverse_map_iterator<Iterator_L>& lhs, const reverse_map_iterator<Iterator_R>& rhs)
	{ return (rhs.base() > lhs.base()); }

	template <class Iterator>
	bool operator<= (const reverse_map_iterator<Iterator>& lhs, const reverse_map_iterator<Iterator>& rhs)
	{ return (rhs.base() >= lhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator<= (const reverse_map_iterator<Iterator_L>& lhs, const reverse_map_iterator<Iterator_R>& rhs)
	{ return (rhs.base() >= lhs.base()); }

	template <class Iterator>
	bool operator> (const reverse_map_iterator<Iterator>& lhs, const reverse_map_iterator<Iterator>& rhs)
	{ return (rhs.base() < lhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator> (const reverse_map_iterator<Iterator_L>& lhs, const reverse_map_iterator<Iterator_R>& rhs)
	{ return (rhs.base() < lhs.base()); }
	
	template <class Iterator>
	bool operator>= (const reverse_map_iterator<Iterator>& lhs, const reverse_map_iterator<Iterator>& rhs)
	{ return (rhs.base() <= lhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator>= (const reverse_map_iterator<Iterator_L>& lhs, const reverse_map_iterator<Iterator_R>& rhs)
	{ return (rhs.base() >= lhs.base()); }

	template <class Iterator>
	reverse_map_iterator<Iterator> operator+ ( typename reverse_map_iterator<Iterator>::difference_type n, const reverse_map_iterator<Iterator>& rev_it)
	{ return (rev_it + n); }

	template <class Iterator>
	typename reverse_map_iterator<Iterator>::difference_type
	operator- (const reverse_map_iterator<Iterator>& lhs, const reverse_map_iterator<Iterator>& rhs)
	{ return (rhs.base() - lhs.base()); } // revers for all ?

	template <class Iterator_L, class Iterator_R>
	typename reverse_map_iterator<Iterator_L>::difference_type
	operator- (const reverse_map_iterator<Iterator_L>& lhs, const reverse_map_iterator<Iterator_R>& rhs)
	{ return (rhs.base() - lhs.base()); } // revers for all ?
}

#endif