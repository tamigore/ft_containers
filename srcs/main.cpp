
#include <iostream>
#include <string>
#include <deque>

#include "ft.hpp"

#ifndef STD
	// #include <map.hpp>
	// #include <stack.hpp>
	// #include <vector.hpp>
	#define NAMESPACE ft
#else
	#include <map>
	#include <stack>
	#include <vector>
	#define NAMESPACE std
#endif

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
class MutantStack : public NAMESPACE::stack<T>
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

	typedef typename NAMESPACE::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main42()
{
	const int seed = 2;
	srand(seed);

	NAMESPACE::vector<std::string> vector_str;
	NAMESPACE::vector<int> vector_int;
	NAMESPACE::stack<int> stack_int;
	NAMESPACE::vector<Buffer> vector_buffer;
	NAMESPACE::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	NAMESPACE::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	NAMESPACE::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cout << "NORMAL ! :P" << std::endl;
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(NAMESPACE::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		NAMESPACE::map<int, int> copy = map_int;
	}
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

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	if (argc >= 2 && std::string(argv[1]).compare("std") == 0)
		std::cout << "NAMESPACE is : std" << std::endl;
	else
		std::cout << "NAMESPACE is : ft" << std::endl;
	vector_tester();
	stack_tester();
	map_tester();
	main42();
	return (0);
}