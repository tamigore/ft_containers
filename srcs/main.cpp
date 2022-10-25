#include "ft.hpp"

#include <vector>
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

template <typename T>
void	printSize(ft::vector<T>  &vct, bool print_content = true)
{
	const int size = vct.size();
	const int capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename ft::vector<T>::iterator it = vct.begin();
		typename ft::vector<T>::iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

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

int vector_test()
{
	// Create a vector containing integers
	std::vector<int>	std_vec;
	ft::vector<int>		ft_vec;

	// Add two more integers to vector
	ft_vec.push_back(25);
	ft_vec.push_back(13);
	ft_vec.push_back(2);
	ft_vec.push_back(1);
	ft_vec.push_back(5);
	ft_vec.push_back(3);
	std_vec.push_back(25);
	std_vec.push_back(13);
	std_vec.push_back(2);
	std_vec.push_back(1);
	std_vec.push_back(5);
	std_vec.push_back(3);
 
	// Print out the vector
	for (size_t n = 0; n < ft_vec.size() && n < std_vec.size(); n++)
	{
		std::cout << "std_vec[" << n << "] = " << std_vec[n] << std::endl;
		std::cout << "ft_vec[" << n << "] = " << ft_vec[n] << std::endl;
		if (ft_vec[n] != std_vec[n])
		{
			std::cout << "error int values do not match..." << std::endl;
			return (0);
		}
	}

	ft::vector<int> vct(7);
	ft::vector<int> vct_two(4);
	ft::vector<int> vct_three;
	ft::vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	vct_four.assign(6, 84);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	return (1);
}

int		assigne(void)
{
	ft::vector<int> vct(7);
	ft::vector<int> vct_two(4);
	ft::vector<int> vct_three;
	ft::vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	printSize(vct);
	printSize(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSize(vct);
	printSize(vct_two);
	printSize(vct_three);
	printSize(vct_four);

	vct_four.assign(6, 84);
	printSize(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	printSize(vct);
	printSize(vct_two);

	return (0);
}

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	stack_test();
	vector_test();
	assigne();
	ft::vector<char>	vide1;
	std::vector<char>	vide2;
}