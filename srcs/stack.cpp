#include "../inc/stack.hpp"
#include <stack>
#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>

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

int stack_test()
{
	ft::stack<int>							test_stack_int;
	ft::stack<int>							f_stack_int;
	ft::stack<Buffer, std::vector<Buffer> >	f_stack_deq_buffer;
	std::stack<int>							s_stack_int;
	std::stack<Buffer, std::deque<Buffer> >	s_stack_deq_buffer;

	test_stack_int.push(100);
	test_stack_int.push(10);
	test_stack_int.push(1);
	test_stack_int.push(5);
	test_stack_int.push(4);
	test_stack_int.push(5);

	f_stack_int.push(100);
	f_stack_int.push(10);
	f_stack_int.push(1);
	f_stack_int.push(5);
	f_stack_int.push(4);
	f_stack_int.push(5);
	f_stack_int.push(2);

	s_stack_int.push(100);
	s_stack_int.push(10);
	s_stack_int.push(1);
	s_stack_int.push(5);
	s_stack_int.push(4);
	s_stack_int.push(5);

	std::cout << "ft stack top:" << f_stack_int.top() << "\ntest stack top:"<< test_stack_int.top() << "\nstd stack top:"<< s_stack_int.top() << std::endl;
	if (f_stack_int == test_stack_int)
		std::cout << "fd == std" << std::endl;
	if (f_stack_int < test_stack_int)
		std::cout << "fd < std" << std::endl;
	if (f_stack_int <= test_stack_int)
		std::cout << "fd <= std" << std::endl;
	if (f_stack_int != test_stack_int)
		std::cout << "fd != std" << std::endl;
	if (f_stack_int > test_stack_int)
		std::cout << "fd > std" << std::endl;
	if (f_stack_int >= test_stack_int)
		std::cout << "fd >= std" << std::endl;
	
	std::cout << "ft stack top:" << f_stack_int.top() << "\ntest stack top:"<< test_stack_int.top() << "\nstd stack top:"<< s_stack_int.top() << std::endl;
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}