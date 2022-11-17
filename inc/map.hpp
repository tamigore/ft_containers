#ifndef _MAP_HPP_
# define _MAP_HPP_

# include <iostream>
# include <utility>
# include "iterator.hpp"
# include "RBTree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key										key_type;
			typedef Allocator								allocator_type;
			typedef T										mapped_type;
			typedef std::pair<const Key, T>					value_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef Compare									key_compare;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef ft::random_access_iterator<T>			iterator;
			typedef ft::random_access_iterator<T>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		private:
			ft::RBTree<T>	_data;
			allocator_type	_alloc;
			key_compare		_comp;
			pointer			_start;
			pointer			_end;
			pointer			_capacity;
		
		public:
			map() : _data(), _alloc(), _comp(), _start(ft_nullptr),
				_end(ft_nullptr), _capacity(ft_nullptr) {};
			map( const Compare& comp, const Allocator& alloc = Allocator() ) :
				_data(), _alloc(alloc), _comp(comp), _start(ft_nullptr), _end(ft_nullptr), _capacity(ft_nullptr) {};
			template < class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() );
			map( const map& other ) : _data(other._data), _alloc(other._alloc), _comp(other._comp), _start(other._start),
				_end(other._end), _capacity(other._capacity) {};
			
			~map() {};
			
			map& operator=( const map& other )	;
			
			allocator_type get_allocator() const;
			
			T&			at( const Key& key );
			const T&	at( const Key& key ) const;
			
			T& operator[]( const Key& key );

			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;

			bool		empty() const;
			size_type	size() const;
			size_type	max_size() const;
			
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
			iterator									find( const Key& key );
			const_iterator								find( const Key& key ) const;
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
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs );
		   
}

#endif