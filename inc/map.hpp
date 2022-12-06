#ifndef _MAP_HPP_
# define _MAP_HPP_

# include <iostream>
# include <utility>
# include "map_iter.hpp"
// # include "pair.hpp"
# include "RBTree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key											key_type;
			typedef Allocator									allocator_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef Compare										key_compare;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef ft::map_iterator<value_type>				iterator;
			typedef ft::map_iterator<value_type>				const_iterator;
			typedef ft::reverse_map_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_map_iterator<const_iterator>	const_reverse_iterator;
			typedef	ft::Node<value_type>						node_type;
			typedef	ft::RBTree<value_type>						tree_type;

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
		
		public:
			map() : _tree(new tree_type()), _alloc(allocator_type()), _comp(key_compare()), _size(0) {}

			map(const key_compare& comp, const allocator_type& alloc = allocator_type()) :
				_tree(new tree_type()), _alloc(alloc), _comp(comp), _size(0) {}

			template < class InputIt >
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				_comp = comp;
				_alloc = alloc;
				if (!_tree)
					_tree = new tree_type();
				while (first != last)
				{
					_tree->insert(*first);
					first++;
				}
			}

			map(const map& other)
			{
				*this = other;
			}
			
			~map()
			{
				clear();
				if (_tree)
					delete _tree;
			}
			
			map& operator=(const map& other)
			{
				if (this == &other)
					return (*this);
				clear();
				_size = 0;
				_alloc = other.get_allocator();
				_comp = other._comp;
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
				return (_tree->searchTree(key));
			}

			iterator				begin()
			{
				return (iterator(_tree->minimum(_tree->getRoot())));
			}

			const_iterator			begin() const
			{
				return (const_iterator(_tree->minimum(_tree->getRoot())));
			}

			iterator				end()
			{
				return (iterator(_tree->maximum(_tree->getRoot())));
			}

			const_iterator			end() const
			{
				return (const_iterator(_tree->maximum(_tree->getRoot())));
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
				if (size() == 0 || _tree->root == _tree->TNULL)
					return (true);
				return (false);
			}

			size_type	size() const
			{
				return (size_type(_tree->getSize()));
			}

			size_type	max_size() const
			{
				return (allocator_type::max_size());
			}
			
			void						clear();
			std::pair<iterator, bool>	insert( const value_type& value );
			iterator					insert( iterator pos, const value_type& value );
			template< class InputIt >
			void						insert( InputIt first, InputIt last );
			iterator					erase( iterator pos );
			iterator					erase( iterator first, iterator last );
			size_type					erase( const Key& key );
			void						swap( map& other );

			size_type									count( const Key& key ) const;
			iterator									find( const Key& key )
			{
				return (iterator(_tree->searchTree(key)));
			}

			const_iterator								find( const Key& key ) const
			{
				return (const_iterator(_tree->searchTree(key)));
			}

			std::pair<iterator,iterator>				equal_range( const Key& key );
			std::pair<const_iterator,const_iterator>	equal_range( const Key& key ) const;
			iterator									lower_bound( const Key& key );
			const_iterator								lower_bound( const Key& key ) const;
			iterator									upper_bound( const Key& key );
			const_iterator								upper_bound( const Key& key ) const;

			key_compare					key_comp() const;
			// value_compare				value_comp() const;
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs) && !(lhs > rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return ((lhs < rhs) || (lhs > rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), lhs._comp));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs > rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end(), lhs._comp));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs );

}

#endif