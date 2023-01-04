#ifndef _MAP_HPP_
# define _MAP_HPP_

# include <iostream>
# include <utility>
# include "map_iter.hpp"
// # include "pair.hpp"
# include "RBTree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key											key_type;
			typedef Allocator									allocator_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef ft::pair<const Key, const T>				const_value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef Compare										key_compare;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef ft::map_iterator<key_type, value_type>		iterator;
			typedef ft::map_iterator<key_type, value_type>		const_iterator;
			typedef ft::reverse_map_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_map_iterator<const_iterator>	const_reverse_iterator;
			typedef	ft::Node<key_type, value_type>				node_type;
			typedef	ft::RBTree<key_type, value_type>			tree_type;

			class value_compare
			{
				friend class map;
				
				protected:
					key_compare comp;
					value_compare (key_compare c) : comp(c) {}
				
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
		
		private:
			tree_type		*_tree;
			allocator_type	_alloc;
			key_compare		_comp;
			size_type		_size;
		
		public: //for testing
			tree_type	*get_tree() const
			{
				return (_tree);
			}

			bool	insert_tree(value_type val)
			{
				node_type	*node = _tree->searchTree(val.first);
				
				if (!node || node == _tree->getNULL())
				{
					// Node *new_node = node_alloc
					_tree->insert(val.first, val);
					_size++;
					return (true);
				}
				return (false);
			}
		
		public:
			map() : _tree(new tree_type()), _alloc(allocator_type()), _comp(key_compare()), _size(0) {}

			map(const key_compare& comp, const allocator_type& alloc = allocator_type()) :
				_tree(new tree_type()), _alloc(alloc), _comp(comp), _size(0) {}

			template < class InputIt >
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				_comp = comp;
				_alloc = alloc;
				_size = 0;
				_tree = new tree_type();
				while (first != last)
				{
					insert_tree(*first);
					first++;
				}
			}

			map(const map& other)
			{
				_tree = new tree_type();
				_size = 0;
				_alloc = other.get_allocator();
				_comp = other.key_comp();
				insert(other.begin(), other.end());
			}
			
			~map()
			{
				if (_tree)
					delete _tree;
				_tree = NULL; // obligatoire avec new / delete ? A tester avec allocator...
			}
			
			map& operator=(const map& other)
			{
				if (this == &other)
					return (*this);
				clear();
				_size = 0;
				_alloc = other.get_allocator();
				_comp = other.key_comp();
				insert(other.begin(), other.end());
				return (*this);
			}

			allocator_type get_allocator() const
			{
				return (_alloc);
			}
			
			T&			at(const Key& key)
			{
				return (_tree->searchTree(key));
			}

			const T&	at(const Key& key) const
			{
				return (_tree->searchTree(key));
			}
			
			T& operator[](const Key& key)
			{
				ft::Node<Key, value_type> *search = _tree->searchTree(key);

				if (search == _tree->getNULL())
				{
					value_type val = make_pair(key, T());
					return (insert(val).first->second);
				}
				return (search->data.second);
			}

			iterator				begin()
			{
				return (iterator(_tree, _tree->minimum(_tree->getRoot())));
			}

			const_iterator			begin() const
			{
				return (const_iterator(_tree, _tree->minimum(_tree->getRoot())));
			}

			iterator				end()
			{
				// return (iterator(_tree, _tree->maximum(_tree->getRoot())));
				if (_tree->getRoot() == _tree->getNULL())
					return (begin());
				return (iterator(_tree, _tree->getNULL()));
			}

			const_iterator			end() const
			{
				// return (const_iterator(_tree, _tree->maximum(_tree->getRoot())));
				if (_tree->getRoot() == _tree->getNULL())
					return (begin());
				return (const_iterator(_tree, _tree->getNULL()));
			}

			reverse_iterator		rbegin()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(begin()));
			}

			reverse_iterator		rend()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(end()));
			}

			bool		empty() const
			{
				if (size() == 0 || _tree->getRoot() == _tree->getNULL())
					return (true);
				return (false);
			}

			size_type	size() const
			{
				return (size_type(_size));
			}

			size_type	max_size() const
			{
				return (_alloc.max_size());
			}
			
			void						clear()
			{
				delete _tree;
				_tree = new tree_type();
				_size = 0;
			}

			ft::pair<iterator, bool>	insert( const value_type& value )
			{
				bool 		ret = insert_tree(value);
				iterator	res = iterator(_tree, _tree->searchTree(value.first));
				
				return (ft::make_pair(res, ret));
			}

			iterator					insert( iterator pos, const value_type& value )
			{
				(void)pos;
				return (insert(value).first);
			}

			template< class InputIt >
			void						insert( InputIt first, InputIt last )
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}

			void						erase( iterator pos )
			{
				_tree->deleteNode(pos->first);
				_size--;
			}

			void						erase( iterator first, iterator last )
			{
				while (first != last)
				{
					_tree->deleteNode(first->first);
					first++;
					_size--;
				}
			}

			size_type					erase( const Key& key )
			{
				bool res = _tree->deleteNode(key);
				if (res)
					_size--;
				return (res);
			}

			void						swap( map& other )
			{
				ft::swap(other._tree, this->_tree);
				ft::swap(other._size, this->_size);
				ft::swap(other._comp, this->_comp);
				ft::swap(other._alloc, this->_alloc);
			}

			size_type									count( const Key& key ) const
			{
				iterator	i = begin();
				size_type	ret = 0;
				while (i != end())
				{
					ret++;
					if (i->first == key)
						break;
					i++;
				}
				return (ret);
			}

			iterator									find( const Key& key )
			{
				return (iterator(_tree, _tree->searchTree(key)));
			}

			const_iterator								find( const Key& key ) const
			{
				return (const_iterator(_tree, _tree->searchTree(key)));
			}

			ft::pair<iterator,iterator>				equal_range( const Key& key )
			{
				return (make_pair(lower_bound(key), upper_bound(key)));
			}

			ft::pair<const_iterator,const_iterator>	equal_range( const Key& key ) const
			{
				return (make_pair(lower_bound(key), upper_bound(key)));
			}

			iterator									lower_bound( const Key& key )
			{
				iterator	i = begin();

				while (i != end() && _comp(i->first, key))
					i++;
				return (i);
			}

			const_iterator								lower_bound( const Key& key ) const
			{
				const_iterator	i = begin();

				while (i != end() && _comp(i->first, key))
					i++;
				return (i);
			}

			iterator									upper_bound( const Key& key )
			{
				iterator	i = begin();

				while (i != end() && _comp(i->first, key))
					i++;
				if (i != end() && !_comp(key, i->first))
					i++;
				return (i);
			}

			const_iterator								upper_bound( const Key& key ) const
			{
				const_iterator	i = begin();

				while (i != end() && _comp(i->first, key))
					i++;
				if (i != end() && !_comp(key, i->first))
					i++;
				return (i);
			}

			key_compare					key_comp() const
			{
				return (_comp);
			}

			value_compare				value_comp() const
			{
				return (value_compare());
			}
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs) && !(rhs < lhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return ((lhs < rhs) || (lhs > rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		// return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), lhs.key_comp()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs > rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
		// return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end(), rhs.key_comp()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
		// ft::swap(lhs.get_tree(), rhs.get_tree());
		// ft::swap(lhs.key_comp(), rhs.key_comp());
		// ft::swap(lhs._size, rhs._size);
		// ft::swap(lhs._alloc, rhs._alloc);
	}

}

#endif