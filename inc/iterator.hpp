#ifndef _ITERATOR_HPP_
# define _ITERATOR_HPP_

# include <cstddef>

# include "utility.hpp"

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		public:
			/* Type of elements pointed. */
			typedef T			value_type;

			/* Type to represent the difference between two iterators. */
			typedef Distance	difference_type;

			/* Type to represent a pointer to an element pointed */
			typedef Pointer		pointer;

			/* Type to represent a reference to an element pointed */
			typedef Reference	reference;

			/* Category of the iterator. */
			typedef Category	iterator_category;
	};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
			
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class Iterator>
	class reverse_iterator
	{
		public:

			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			
			reverse_iterator() : _content() {}
			
			explicit reverse_iterator (iterator_type it) : _content(it) {}
		   
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _content(rev_it.base()) {}

			virtual ~reverse_iterator() {}
			
			iterator_type base() const
			{ return (_content); }

			reference operator*() const
			{
				iterator_type tmp = _content;
				return (*(--tmp));
			}

			reverse_iterator operator+ (difference_type n) const
			{ return (reverse_iterator(_content - n)); }

			reverse_iterator& operator++()
			{
				--_content;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator& operator+= (difference_type n)
			{
				_content -= n;
				return (*this);
			}

			reverse_iterator operator- (difference_type n) const
			{ return (reverse_iterator(_content + n)); }

			reverse_iterator& operator--()
			{
				++_content;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			reverse_iterator& operator-= (difference_type n)
			{
				_content += n;
				return (*this);
			}

			pointer operator->() const
			{ return &(operator*()); }

			reference operator[] (difference_type n) const
			{ return (this->base()[-n - 1]); }

		private:
			iterator_type     _content;
	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator== (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator!= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator< (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator<= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() < rhs.bash()); }

	template <class Iterator_L, class Iterator_R>
	bool operator> (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{ return (lhs.base() < rhs.base()); }
	
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator>= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <class Iterator>
	reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
	{ return (rev_it + n); }

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() - rhs.base()); }

	template <class Iterator_L, class Iterator_R>
	bool operator- (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{ return (lhs.base() - rhs.base()); }


	template <typename T>
	class random_access_iterator : ft::iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef T*																				pointer;
			typedef T&																				reference;

			random_access_iterator(void) : _content(ft_nullptr) {}

			random_access_iterator(pointer elem) : _content(elem) {}

			random_access_iterator(const random_access_iterator& op) : _content(op._content) {}

			random_access_iterator &operator=(const random_access_iterator& op)
			{
				if (this == &op)
					return (*this);
				this->_content = op._content;
				return (*this);
			}

			virtual ~random_access_iterator() {}

			pointer base() const
			{ return (this->_content); }

			reference operator*(void) const
			{ return (*_content); }

			pointer operator->(void)
			{ return &(this->operator*()); }

			random_access_iterator& operator++(void)
			{
				_content++;
				return (*this);
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator rtn(*this);
				operator++();
				return (rtn);
			}

			random_access_iterator& operator--(void)
			{
				_content--;
				return (*this);
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator rtn(*this);
				operator--();
				return (rtn);
			}

			random_access_iterator operator+(difference_type n) const
			{ return (_content + n); }

			random_access_iterator operator-(difference_type n) const
			{ return (_content - n); }

			random_access_iterator& operator+=(difference_type n)
			{
				_content += n;
				return (*this);
			}

			random_access_iterator& operator-=(difference_type n)
			{
				_content -= n;
				return (*this);
			}

			reference operator[](difference_type n)
			{ return (*(operator+(n))); }

			operator random_access_iterator<const T> () const
			{ return (random_access_iterator<const T>(this->_content)); }

			private:
				pointer _content;
	};

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator==(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() == rhs.base()); }

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator==(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{ return (lhs.base() == rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator!=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() != rhs.base()); }

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator!=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{ return (lhs.base() != rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator<(const ft::random_access_iterator<T> lhs,
			  const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() < rhs.base()); }

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator<(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{ return (lhs.base() < rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator>(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() > rhs.base()); }

	template<typename T_L,
			 typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator>(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{ return (lhs.base() > rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator<=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() <= rhs.base()); }

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator<=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator>=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() >= rhs.base()); }

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator>=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{ return (lhs.base() >= rhs.base()); }

	template<typename T>
	ft::random_access_iterator<T>
	operator+(typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& rai)
	{ return (&(*rai) + n); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator-(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() - rhs.base()); }

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator-(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{ return (lhs.base() - rhs.base()); }
}

#endif