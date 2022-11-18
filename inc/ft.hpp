#ifndef _FT_HPP_
# define _FT_HPP_

# include "map.hpp"
# include "vector.hpp"
# include "stack.hpp"

#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>
#include <list>

// int vector_test();
// int stack_test();

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
	public:
		MutantStack() {}
		MutantStack(const MutantStack<T>& src) { *this = src; }
		MutantStack<T>& operator=(const MutantStack<T>& rhs) 
		{
			this->c = rhs.c;
			return *this;
		}
		~MutantStack() {}

		typedef typename ft::stack<T>::container_type::iterator iterator;

		iterator begin() { return this->c.begin(); }
		iterator end() { return this->c.end(); }
};

template <typename T>
void	printSizeVs(ft::vector<T> const &ft_vec, std::vector<T> const &std_vec, bool print_content = true)
{
	std::cout << "___________________ft vs std___________________" << std::endl;
	const int ft_size = ft_vec.size();
	const int ft_capacity = ft_vec.capacity();
	const int std_size = std_vec.size();
	const int std_capacity = std_vec.capacity();

	std::cout << "ft_size: " << ft_size << " == std_size: " << std_size <<std::endl;
	std::cout << "ft_capacity: " << ft_capacity << " == " << std_capacity << " :std_capacity || capacity is ok ? : " << ((ft_capacity >= ft_size) ? "OK" : "KO") << std::endl;
	std::cout << "ft_max_size: " << (ft_vec.max_size() == std_vec.max_size() ? "OK" : "KO") << std::endl;
	if (print_content)
	{
		typename ft::vector<T>::const_iterator it = ft_vec.begin();
		typename ft::vector<T>::const_iterator ite = ft_vec.end();
		typename std::vector<T>::const_iterator s_it = std_vec.begin();
		typename std::vector<T>::const_iterator s_ite = std_vec.end();
		std::cout << std::endl << "Content is:" << std::endl;
		int i = 0;
		for (; it != ite; ++it)
		{
			if (s_it >= s_ite)
				std::cout << "to much elem" << std::endl;
			else
			{
				std::cout << i << "- ft: |" << *it  << "| == |" << *s_it << "| :std" << std::endl;
				s_it++;
			}
			i++;
		}
	}
	std::cout << "_______________________________________________" << std::endl;
}

// template <typename T>
// void	printSize(ft::vector<T> const &vct, bool print_content = true)
// {
// 	std::cout << "______________________ft_______________________" << std::endl;
// 	const int size = vct.size();
// 	const int capacity = vct.capacity();
// 	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
// 	// Cannot limit capacity's max value because it's implementation dependent
// 	std::cout << "size: " << size << std::endl;
// 	std::cout << "capacity: " << isCapacityOk << std::endl;
// 	std::cout << "max_size: " << vct.max_size() << std::endl;
// 	if (print_content)
// 	{
// 		typename ft::vector<T>::const_iterator it = vct.begin();
// 		typename ft::vector<T>::const_iterator ite = vct.end();
// 		std::cout << std::endl << "Content is:" << std::endl;
// 		for (; it != ite; ++it)
// 			std::cout << "- " << *it << std::endl;
// 	}
// 	std::cout << "_______________________________________________" << std::endl;
// }

// template <typename T>
// void	printSize_std(std::vector<T> const &vct, bool print_content = true)
// {
// 	std::cout << "______________________std______________________" << std::endl;
// 	const int size = vct.size();
// 	const int capacity = vct.capacity();
// 	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
// 	// Cannot limit capacity's max value because it's implementation dependent
// 	std::cout << "size: " << size << std::endl;
// 	std::cout << "capacity: " << isCapacityOk << std::endl;
// 	std::cout << "max_size: " << vct.max_size() << std::endl;
// 	if (print_content)
// 	{
// 		typename std::vector<T>::const_iterator it = vct.begin();
// 		typename std::vector<T>::const_iterator ite = vct.end();
// 		std::cout << std::endl << "Content is:" << std::endl;
// 		for (; it != ite; ++it)
// 			std::cout << "- " << *it << std::endl;
// 	}
// 	std::cout << "_______________________________________________" << std::endl;
// }

namespace ft
{
	// template < class T, class Allocator = std::allocator<T> >
	// class vector;

	// template< class T, class Alloc = T>
	// class map;
	
	// template <class T, class Container = std::vector<T> >
	// class stack;
}

#endif