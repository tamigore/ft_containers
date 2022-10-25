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

	template< class It >
	class reverse_iterator : ft::iterator<std::random_access_iterator_tag, It>
	{
		protected:
			It current;
		
		public:
			reverse_iterator();
			
			explicit reverse_iterator(It itr) : current(itr) {}
			
			// 	requires (!std::is_same_v<U, It> && std::convertible_to<const U&, It>)
			template<class U>
			explicit reverse_iterator(const U& other) : current(other.base()) {}
		
			It operator*() const
			{
				return (*current); // <== returns the content of prev
			}
		
			reverse_iterator& operator++() { --current; return *this; }
			reverse_iterator operator++(int) { It tmp = *this; ++(*this); return tmp; }
		
			reverse_iterator& operator--() { ++current; return *this; }
			reverse_iterator operator--(int) { It tmp = *this; --(*this); return tmp; }
		
			It base() const { return current; }
	};

	template <typename T>
	class random_access_iterator : ft::iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef T*																				pointer;
			typedef T&																				reference;

			random_access_iterator(void) : _elem(ft_nullptr) {}

			random_access_iterator(pointer elem) : _elem(elem) {}

			random_access_iterator(const random_access_iterator& op) : _elem(op._elem) {}

			random_access_iterator &operator=(const random_access_iterator& op)
			{
				if (this == &op)
					return (*this);
				this->_elem = op._elem;
				return (*this);
			}

			virtual ~random_access_iterator() {}

			pointer base() const { return (this->_elem); }

			reference operator*(void) const { return (*_elem); }

			pointer operator->(void) { return &(this->operator*()); }

			random_access_iterator& operator++(void)
			{
				_elem++;
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
				_elem--;
				return (*this);
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator rtn(*this);
				operator--();
				return (rtn);
			}

			random_access_iterator operator+(difference_type n) const { return (_elem + n); }

			random_access_iterator operator-(difference_type n) const { return (_elem - n); }

			random_access_iterator& operator+=(difference_type n)
			{
				_elem += n;
				return (*this);
			}

			random_access_iterator& operator-=(difference_type n)
			{
				_elem -= n;
				return (*this);
			}

			reference operator[](difference_type n) { return (*(operator+(n))); }

			operator random_access_iterator<const T> () const
			{
				return (random_access_iterator<const T>(this->_elem));
			}

			private:
				pointer _elem;
	};

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator==(const ft::random_access_iterator<T> lhs,
			  const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator==(const ft::random_access_iterator<T_L> lhs,
			  const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator!=(const ft::random_access_iterator<T> lhs,
			  const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator!=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator<(const ft::random_access_iterator<T> lhs,
			  const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator<(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator>(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T_L,
			 typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator>(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator<=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator<=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator>=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator>=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T>
	ft::random_access_iterator<T>
	operator+(typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& rai)
	{
		return (&(*rai) + n);
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator-(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator-(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif