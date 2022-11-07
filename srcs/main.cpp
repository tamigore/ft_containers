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

void    checkErase(ft::vector<std::string> const &ft_vct, ft::vector<std::string>::const_iterator const &it, std::vector<std::string> const &std_vct, std::vector<std::string>::const_iterator const &sit)
{
	static int i = 0;
	static int j = 0;
	std::cout << "" << std::endl;
	std::cout << "_ft_ [" << i++ << "] " << "erase: " << it - ft_vct.begin() << std::endl;
	std::cout << "_std_ [" << j++ << "] " << "erase: " << sit - std_vct.begin() << std::endl;
	printSizeVs(ft_vct, std_vct);
}

void	vec_erased_test()
{
	ft::vector<std::string>		ft_vct(10);
	std::vector<std::string>	std_vct(10);

	for (unsigned long int i = 0; i < ft_vct.size(); ++i)
			ft_vct[i] = std::string((ft_vct.size() - i), i + 65);
	for (unsigned long int i = 0; i < std_vct.size(); ++i)
			std_vct[i] = std::string((std_vct.size() - i), i + 65);
	printSizeVs(ft_vct, std_vct);

	checkErase(ft_vct, ft_vct.erase(ft_vct.begin() + 2), std_vct, std_vct.erase(std_vct.begin() + 2));
	
	checkErase(ft_vct, ft_vct.erase(ft_vct.begin()), std_vct, std_vct.erase(std_vct.begin()));
	checkErase(ft_vct, ft_vct.erase(ft_vct.end() - 1), std_vct, std_vct.erase(std_vct.end() - 1));

	checkErase(ft_vct, ft_vct.erase(ft_vct.begin(), ft_vct.begin() + 3), std_vct, std_vct.erase(std_vct.begin(), std_vct.begin() + 3));
	checkErase(ft_vct, ft_vct.erase(ft_vct.end() - 3, ft_vct.end() - 1), std_vct, std_vct.erase(std_vct.end() - 3, std_vct.end() - 1));

	ft_vct.push_back("Hello");
	ft_vct.push_back("Hi there");
	std_vct.push_back("Hello");
	std_vct.push_back("Hi there");
	printSizeVs(ft_vct, std_vct);
	checkErase(ft_vct, ft_vct.erase(ft_vct.end() - 3, ft_vct.end()), std_vct, std_vct.erase(std_vct.end() - 3, std_vct.end()));

	ft_vct.push_back("ONE");
	ft_vct.push_back("TWO");
	ft_vct.push_back("THREE");
	ft_vct.push_back("FOUR");
	std_vct.push_back("ONE");
	std_vct.push_back("TWO");
	std_vct.push_back("THREE");
	std_vct.push_back("FOUR");
	printSizeVs(ft_vct, std_vct);
	checkErase(ft_vct, ft_vct.erase(ft_vct.begin(), ft_vct.end()), std_vct, std_vct.erase(std_vct.begin(), std_vct.end()));
}

void	vec_insert_test()
{
	std::cout << "FIRST PART" << std::endl;
	{
		ft::vector<int> ft_vec(10);
		ft::vector<int> ft_vec2;
		ft::vector<int> ft_vec3;
		std::vector<int> std_vec(10);
		std::vector<int> std_vec2;
		std::vector<int> std_vec3;

		for (unsigned long int i = 0; i < ft_vec.size(); ++i)
			ft_vec[i] = (ft_vec.size() - i) * 3;
		for (unsigned long int i = 0; i < std_vec.size(); ++i)
			std_vec[i] = (std_vec.size() - i) * 3;
		printSizeVs(ft_vec, std_vec);

		// ft_vec2.resize(4);
		// std_vec2.resize(4);
		ft_vec2.insert(ft_vec2.end(), 42);
		std_vec2.insert(std_vec2.end(), 42);
		printSizeVs(ft_vec2, std_vec2);

		ft_vec2.insert(ft_vec2.begin(), 2, 21);
		std_vec2.insert(std_vec2.begin(), 2, 21);
		printSizeVs(ft_vec2, std_vec2);

		// std::cout << *(ft_vec2.end() - 2) << " || " << (ft_vec2._end - 2) << std::endl;
		ft_vec2.insert(ft_vec2.end() - 2, 42);
		std_vec2.insert(std_vec2.end() - 2, 42);
		printSizeVs(ft_vec2, std_vec2);

		ft_vec2.insert(ft_vec2.end(), 2, 84);
		std_vec2.insert(std_vec2.end(), 2, 84);
		printSizeVs(ft_vec2, std_vec2);

		ft_vec2.resize(4);
		std_vec2.resize(4);
		printSizeVs(ft_vec2, std_vec2);

		ft_vec2.insert(ft_vec2.begin() + 2, ft_vec.begin(), ft_vec.end());
		ft_vec.clear();
		std_vec2.insert(std_vec2.begin() + 2, std_vec.begin(), std_vec.end());
		std_vec.clear();
		printSizeVs(ft_vec2, std_vec2);

		for (int i = 0; i < 5; ++i)
				ft_vec3.insert(ft_vec3.end(), i);
		for (int i = 0; i < 5; ++i)
				std_vec3.insert(std_vec3.end(), i);
		printSizeVs(ft_vec3, std_vec3);
		ft_vec3.insert(ft_vec3.begin() + 1, 2, 111);
		std_vec3.insert(std_vec3.begin() + 1, 2, 111);
		printSizeVs(ft_vec3, std_vec3);
	}
	std::cout << std::endl;
	std::cout << "SECOND PART" << std::endl;
	{
		ft::vector<int> ft_vct(5);
		std::vector<int> std_vct(5);
		ft::vector<int> ft_vct2;
		std::vector<int> std_vct2;
		const int cut = 3;

		for (unsigned long int i = 0; i < ft_vct.size(); ++i)
				ft_vct[i] = (ft_vct.size() - i) * 7;
		for (unsigned long int i = 0; i < std_vct.size(); ++i)
				std_vct[i] = (std_vct.size() - i) * 7;
		printSizeVs(ft_vct, std_vct);

		ft_vct2.insert(ft_vct2.begin(), ft_vct.begin(), ft_vct.begin() + cut);
		std_vct2.insert(std_vct2.begin(), std_vct.begin(), std_vct.begin() + cut);
		printSizeVs(ft_vct2, std_vct2);
		ft_vct2.insert(ft_vct2.begin(), ft_vct.begin() + cut, ft_vct.end());
		std_vct2.insert(std_vct2.begin(), std_vct.begin() + cut, std_vct.end());
		printSizeVs(ft_vct2, std_vct2);
		ft_vct2.insert(ft_vct2.end(), ft_vct.begin(), ft_vct.begin() + cut);
		std_vct2.insert(std_vct2.end(), std_vct.begin(), std_vct.begin() + cut);
		printSizeVs(ft_vct2, std_vct2);

		std::cout << "insert return:" << std::endl;

		std::cout << *ft_vct2.insert(ft_vct2.end(), 42)  << " = " << *std_vct2.insert(std_vct2.end(), 42) << std::endl;
		printSizeVs(ft_vct2, std_vct2);
		
		
		std::cout << *ft_vct2.insert(ft_vct2.begin() + 5, 84) << " = " << *std_vct2.insert(std_vct2.begin() + 5, 84) << std::endl;
		std::cout << "----------------------------------------" << std::endl;

		printSizeVs(ft_vct2, std_vct2);
	}
	std::cout << std::endl;
}

void	test_copy_construct()
{
	ft::vector<int>		ft_vct(5);
	ft::vector<int>::iterator it = ft_vct.begin(), ite = ft_vct.end();
	std::vector<int>	std_vct(5);
	std::vector<int>::iterator sit = std_vct.begin(), site = std_vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	std::cout << "len: " << (site - sit) << std::endl;
	for (; it != ite; ++it)
			*it = (ite - it);
	for (; sit != site; ++sit)
			*sit = (site - sit);

	it = ft_vct.begin();
	sit = std_vct.begin();
	ft::vector<int> ft_vct_range(it, --(--ite));
	std::vector<int> std_vct_range(sit, --(--site));
	for (int i = 0; it != ite; ++it)
			*it = ++i * 5;
	for (int i = 0; sit != site; ++sit)
			*sit = ++i * 5;

	it = ft_vct.begin();
	sit = std_vct.begin();
	ft::vector<int> ft_vct_copy(ft_vct);
	std::vector<int> std_vct_copy(std_vct);
	for (int i = 0; it != ite; ++it)
			*it = ++i * 7;
	for (int i = 0; sit != site; ++sit)
			*sit = ++i * 7;
	ft_vct_copy.push_back(42);
	ft_vct_copy.push_back(21);
	std_vct_copy.push_back(42);
	std_vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSizeVs(ft_vct, std_vct);
	printSizeVs(ft_vct_range, std_vct_range);
	printSizeVs(ft_vct_copy, std_vct_copy);

	ft_vct = ft_vct_copy;
	std_vct = std_vct_copy;
	ft_vct_copy = ft_vct_range;
	std_vct_copy = std_vct_range;
	ft_vct_range.clear();
	std_vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSizeVs(ft_vct, std_vct);
	printSizeVs(ft_vct_range, std_vct_range);
	printSizeVs(ft_vct_copy, std_vct_copy);
}

void	is_empty(ft::vector<int> const &ft_vct, std::vector<int> const &std_vct)
{
        std::cout << "ft is_empty: " << ft_vct.empty() << " | std is_empty: " << std_vct.empty() << std::endl;
}

void	test_size()
{
	const int start_size = 7;
	ft::vector<int> ft_vct(start_size, 20);
	ft::vector<int> ft_vct2;
	ft::vector<int>::iterator it = ft_vct.begin();
	std::vector<int> std_vct(start_size, 20);
	std::vector<int> std_vct2;
	std::vector<int>::iterator sit = std_vct.begin();

	for (int i = 2; i < start_size; ++i)
			it[i] = (start_size - i) * 3;
	for (int i = 2; i < start_size; ++i)
			sit[i] = (start_size - i) * 3;
	printSizeVs(ft_vct, std_vct);

	ft_vct.resize(10, 42);
	std_vct.resize(10, 42);
	printSizeVs(ft_vct, std_vct);

	ft_vct.resize(18, 43);
	std_vct.resize(18, 43);
	printSizeVs(ft_vct, std_vct);
	ft_vct.resize(10);
	std_vct.resize(10);
	printSizeVs(ft_vct, std_vct);
	ft_vct.resize(23, 44);
	std_vct.resize(23, 44);
	printSizeVs(ft_vct, std_vct);
	ft_vct.resize(5);
	std_vct.resize(5);
	printSizeVs(ft_vct, std_vct);
	ft_vct.reserve(5);
	std_vct.reserve(5);
	ft_vct.reserve(3);
	std_vct.reserve(3);
	printSizeVs(ft_vct, std_vct);
	ft_vct.resize(87);
	std_vct.resize(87);
	ft_vct.resize(5);
	std_vct.resize(5);
	printSizeVs(ft_vct, std_vct);

	is_empty(ft_vct2, std_vct2);
	ft_vct2 = ft_vct;
	std_vct2 = std_vct;
	is_empty(ft_vct2, std_vct2);
	ft_vct.reserve(ft_vct.capacity() + 1);
	std_vct.reserve(std_vct.capacity() + 1);
	printSizeVs(ft_vct, std_vct);
	printSizeVs(ft_vct2, std_vct);

	ft_vct2.resize(0);
	std_vct2.resize(0);
	is_empty(ft_vct2, std_vct2);
	printSizeVs(ft_vct2, std_vct2);
}

void	test_swap()
{
	ft::vector<int> foo(3, 15);
	ft::vector<int> bar(5, 42);
	std::vector<int> sfoo(3, 15);
	std::vector<int> sbar(5, 42);
	ft::vector<int>::const_iterator it_foo = foo.begin();
	ft::vector<int>::const_iterator it_bar = bar.begin();
	std::vector<int>::const_iterator sit_foo = sfoo.begin();
	std::vector<int>::const_iterator sit_bar = sbar.begin();

	std::cout << "BEFORE SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSizeVs(foo, sfoo);
	std::cout << "bar contains:" << std::endl;
	printSizeVs(bar, sbar);

	foo.swap(bar);
	sfoo.swap(sbar);

	std::cout << "AFTER SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSizeVs(foo, sfoo);
	std::cout << "bar contains:" << std::endl;
	printSizeVs(bar, sbar);

	std::cout << "Iterator validity:" << std::endl;
	std::cout << (it_foo == bar.begin()) << std::endl;
	std::cout << (it_bar == foo.begin()) << std::endl;
	std::cout << (sit_foo == sbar.begin()) << std::endl;
	std::cout << (sit_bar == sfoo.begin()) << std::endl;
	std::cout << "END" << std::endl;
}

void	test_iter_const(void)
{
	{
		const int size = 5;
		ft::vector<int> vct(size);
		ft::vector<int>::iterator it = vct.begin();
		ft::vector<int>::const_iterator ite = vct.begin();

		for (int i = 0; i < size; ++i)
				it[i] = i;

		std::cout << "ok ?" << std::endl;
		ite[1] = 42; // < -- error
		std::cout << "KO !" << std::endl;
	}
	{
		const int size = 5;
		ft::vector<int> vct(size);
		ft::vector<int>::iterator it = vct.begin();
		ft::vector<int>::const_iterator ite = vct.begin();

		for (int i = 0; i < size; ++i)
			it[i] = i;
		std::cout << "ok ?" << std::endl;
		*ite = 42; // < -- error
		std::cout << "KO !" << std::endl;
	}
	{
		const int size = 5;
		ft::vector<int> const vct(size);
		ft::vector<int>::iterator it = vct.begin(); // <-- error expected

		std::cout << "ok ?" << std::endl;
		for (int i = 0; i < size; ++i)
				it[i] = i;
		std::cout << "KO !" << std::endl;
	}
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
	// vec_erased_test();
	vec_insert_test();
	// test_copy_construct();
	// test_size();
	// test_swap();
	// test_iter_const();
	return (0);
}