#include "ft.hpp"

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

void	vec_bidirectionalit_test(void)
{
	std::list<int> lst;
	std::list<int>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
			lst.push_back(i * 3);

	ft::vector<int>		ft_vct(lst.begin(), lst.end());
	std::vector<int>	std_vct(lst.begin(), lst.end());
	printSize(ft_vct);
	printSize_std(std_vct);

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
			*lst_it++ = i * 5;
	ft_vct.assign(lst.begin(), lst.end());
	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
			*lst_it++ = i * 5;
	std_vct.assign(lst.begin(), lst.end());
	printSize(ft_vct);
	printSize_std(std_vct);

	ft_vct.insert(ft_vct.end(), lst.rbegin(), lst.rend());
	std_vct.insert(std_vct.end(), lst.rbegin(), lst.rend());
	printSize(ft_vct);
	printSize_std(std_vct);
}

void	vec_erase_test()
{
	ft::vector<char>	ft_v0;
	std::vector<char>	std_v0;
	ft_v0.push_back('1');
	std_v0.push_back('1');
	ft_v0.push_back('0');
	std_v0.push_back('0');
	ft_v0.push_back('a');
	std_v0.push_back('a');
	ft_v0.push_back('c');
	std_v0.push_back('c');
	ft_v0.push_back('k');
	std_v0.push_back('k');
	printSize(ft_v0);
	printSize_std(std_v0);
	ft_v0.erase(ft_v0.begin() + 2);
	std_v0.erase(std_v0.begin() + 2);
	ft_v0.erase(ft_v0.begin());
	std_v0.erase(std_v0.begin());
	printSize(ft_v0);
	printSize_std(std_v0);
	ft_v0.push_back('z');
	std_v0.push_back('z');
	ft_v0.push_back('y');
	std_v0.push_back('y');
	ft_v0.push_back('x');
	std_v0.push_back('x');
	ft_v0.push_back('w');
	std_v0.push_back('w');
	printSize(ft_v0);
	printSize_std(std_v0);
	ft_v0.erase(ft_v0.begin() + 1, ft_v0.end() - 3);
	std_v0.erase(std_v0.begin() + 1, std_v0.end() - 3);
	printSize(ft_v0);
	printSize_std(std_v0);
	ft_v0.erase(ft_v0.begin(), ft_v0.end());
	std_v0.erase(std_v0.begin(), std_v0.end());
	printSize(ft_v0);
	printSize_std(std_v0);
}

void	vec_assign_test()
{
	ft::vector<int> ft_vct(7);
	ft::vector<int> ft_vct_two(4);
	ft::vector<int> ft_vct_three;
	ft::vector<int> ft_vct_four;
	std::vector<int> std_vct(7);
	std::vector<int> std_vct_two(4);
	std::vector<int> std_vct_three;
	std::vector<int> std_vct_four;

	for (unsigned long int i = 0; i < ft_vct.size(); ++i)
			ft_vct[i] = (ft_vct.size() - i) * 3;
	for (unsigned long int i = 0; i < ft_vct_two.size(); ++i)
			ft_vct_two[i] = (ft_vct_two.size() - i) * 5;
	for (unsigned long int i = 0; i < std_vct.size(); ++i)
			std_vct[i] = (std_vct.size() - i) * 3;
	for (unsigned long int i = 0; i < std_vct_two.size(); ++i)
			std_vct_two[i] = (std_vct_two.size() - i) * 5;
	printSize(ft_vct);
	printSize_std(std_vct);
	printSize(ft_vct_two);
	printSize_std(std_vct_two);

	ft_vct_three.assign(ft_vct.begin(), ft_vct.end());
	ft_vct.assign(ft_vct_two.begin(), ft_vct_two.end());
	ft_vct_two.assign(2, 42);
	ft_vct_four.assign(4, 21);
	std_vct_three.assign(std_vct.begin(), std_vct.end());
	std_vct.assign(std_vct_two.begin(), std_vct_two.end());
	std_vct_two.assign(2, 42);
	std_vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSize(ft_vct);
	printSize_std(std_vct);
	printSize(ft_vct_two);
	printSize_std(std_vct_two);
	printSize(ft_vct_three);
	printSize_std(std_vct_three);
	printSize(ft_vct_four);
	printSize_std(std_vct_four);

	ft_vct_four.assign(6, 84);
	std_vct_four.assign(6, 84);
	printSize(ft_vct_four);
	printSize_std(std_vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	ft_vct.assign(5, 53);
	ft_vct_two.assign(ft_vct_three.begin(), ft_vct_three.begin() + 3);
	std_vct.assign(5, 53);
	std_vct_two.assign(std_vct_three.begin(), std_vct_three.begin() + 3);

	printSize(ft_vct);
	printSize_std(std_vct);
	printSize(ft_vct_two);
	printSize_std(std_vct_two);

}

void    checkErase(ft::vector<int> const &vct, ft::vector<int>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

int             main(void)
{
	ft::vector<int> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
			vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));

	return (0);
}

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	// stack_test();
	// vector_test();
	// vec_erase_test();
	// vec_assign_test();
	// vec_bidirectionalit_test();
}