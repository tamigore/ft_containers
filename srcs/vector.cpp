#include <vector>
#include "vector.hpp"
#include <iostream>
#include <list>

#define SPACE_STD std
#define SPACE_FT ft
// #define TESTED_TYPE int
#define TESTED_TYPE foo<int>

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}

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
	printSizeVs(ft_vct, std_vct);

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
			*lst_it++ = i * 5;
	ft_vct.assign(lst.begin(), lst.end());
	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
			*lst_it++ = i * 5;
	std_vct.assign(lst.begin(), lst.end());
	printSizeVs(ft_vct, std_vct);

	ft_vct.insert(ft_vct.end(), lst.rbegin(), lst.rend());
	std_vct.insert(std_vct.end(), lst.rbegin(), lst.rend());
	printSizeVs(ft_vct, std_vct);
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
	printSizeVs(ft_v0, std_v0);
	ft_v0.erase(ft_v0.begin() + 2);
	std_v0.erase(std_v0.begin() + 2);
	ft_v0.erase(ft_v0.begin());
	std_v0.erase(std_v0.begin());
	printSizeVs(ft_v0, std_v0);
	ft_v0.push_back('z');
	std_v0.push_back('z');
	ft_v0.push_back('y');
	std_v0.push_back('y');
	ft_v0.push_back('x');
	std_v0.push_back('x');
	ft_v0.push_back('w');
	std_v0.push_back('w');
	printSizeVs(ft_v0, std_v0);
	ft_v0.erase(ft_v0.begin() + 1, ft_v0.end() - 3);
	std_v0.erase(std_v0.begin() + 1, std_v0.end() - 3);
	printSizeVs(ft_v0, std_v0);
	ft_v0.erase(ft_v0.begin(), ft_v0.end());
	std_v0.erase(std_v0.begin(), std_v0.end());
	printSizeVs(ft_v0, std_v0);
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
	printSizeVs(ft_vct, std_vct);
	printSizeVs(ft_vct_two, std_vct_two);

	ft_vct_three.assign(ft_vct.begin(), ft_vct.end());
	ft_vct.assign(ft_vct_two.begin(), ft_vct_two.end());
	ft_vct_two.assign(2, 42);
	ft_vct_four.assign(4, 21);
	std_vct_three.assign(std_vct.begin(), std_vct.end());
	std_vct.assign(std_vct_two.begin(), std_vct_two.end());
	std_vct_two.assign(2, 42);
	std_vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSizeVs(ft_vct, std_vct);
	printSizeVs(ft_vct_two, std_vct_two);
	printSizeVs(ft_vct_three, std_vct_three);
	printSizeVs(ft_vct_four, std_vct_four);

	ft_vct_four.assign(6, 84);
	std_vct_four.assign(6, 84);
	printSizeVs(ft_vct_four, std_vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	ft_vct.assign(5, 53);
	ft_vct_two.assign(ft_vct_three.begin(), ft_vct_three.begin() + 3);
	std_vct.assign(5, 53);
	std_vct_two.assign(std_vct_three.begin(), std_vct_three.begin() + 3);

	printSizeVs(ft_vct, std_vct);
	printSizeVs(ft_vct_two, std_vct_two);

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

// void	test_iter_const(void)
// {
// 	{
// 		const int size = 5;
// 		ft::vector<int> vct(size);
// 		ft::vector<int>::iterator it = vct.begin();
// 		ft::vector<int>::const_iterator ite = vct.begin();
// 		for (int i = 0; i < size; ++i)
// 				it[i] = i;
// 		std::cout << "ok ?" << std::endl;
// 		ite[1] = 42; // < -- error
// 		std::cout << "KO !" << std::endl;
// 	}
// 	{
// 		const int size = 5;
// 		ft::vector<int> vct(size);
// 		ft::vector<int>::iterator it = vct.begin();
// 		ft::vector<int>::const_iterator ite = vct.begin();
// 		for (int i = 0; i < size; ++i)
// 			it[i] = i;
// 		std::cout << "ok ?" << std::endl;
// 		*ite = 42; // < -- error
// 		std::cout << "KO !" << std::endl;
// 	}
// 	{
// 		const int size = 5;
// 		ft::vector<int> const vct(size);
// 		ft::vector<int>::iterator it = vct.begin(); // <-- error expected
// 		std::cout << "ok ?" << std::endl;
// 		for (int i = 0; i < size; ++i)
// 				it[i] = i;
// 		std::cout << "KO !" << std::endl;
// 	}
// }

template <class T, class Alloc>
void    cmp(const SPACE_FT::vector<T, Alloc> &lhs, const SPACE_FT::vector<T, Alloc> &rhs, const SPACE_STD::vector<T, Alloc> &s_lhs, const SPACE_STD::vector<T, Alloc> &s_rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;

	std::cout << "FT > eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << " || STD > eq: " << (s_lhs == s_rhs) << " | ne: " << (s_lhs != s_rhs) << std::endl;
	std::cout << "FT > lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << " || STD > lt: " << (s_lhs <  s_rhs) << " | le: " << (s_lhs <= s_rhs) << std::endl;
	std::cout << "FT > gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << " || STD > gt: " << (s_lhs >  s_rhs) << " | ge: " << (s_lhs >= s_rhs) << std::endl;
}

void	test_relational_op()
{
	SPACE_FT::vector<TESTED_TYPE> ft_vct(4);
	SPACE_FT::vector<TESTED_TYPE> ft_vct2(4);
	SPACE_STD::vector<TESTED_TYPE> vct(4);
	SPACE_STD::vector<TESTED_TYPE> vct2(4);

	cmp(ft_vct, ft_vct, vct, vct);  // 0
	cmp(ft_vct, ft_vct2, vct, vct2); // 1

	vct2.resize(10);
	ft_vct2.resize(10);

	cmp(ft_vct, ft_vct2, vct, vct2); // 2
	cmp(ft_vct2, ft_vct, vct2, vct); // 3

	vct[2] = 42;
	ft_vct[2] = 42;

	cmp(ft_vct, ft_vct2, vct, vct2); // 4
	cmp(ft_vct2, ft_vct, vct2, vct); // 5
	printSizeVs(ft_vct, vct);
	printSizeVs(ft_vct2, vct2);

	swap(vct, vct2);
	swap(ft_vct, ft_vct2);

	printSizeVs(ft_vct, vct);
	printSizeVs(ft_vct2, vct2);
	cmp(ft_vct, ft_vct2, vct, vct2); // 6
	cmp(ft_vct2, ft_vct, vct2, vct); // 7
	cmp(ft_vct, ft_vct, vct, vct); // 8
}

template <typename Ite_1, typename Ite_2, typename Ite_3, typename Ite_4>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const Ite_3 std1, const Ite_4 std2, const bool redo = 1)
{
	// std::cout << "ft : " <<  *first << " == " << *second << " || std : " << *std1 << " == " << *std2 <<std::endl;
	std::cout << " < : " << (first < second) << " = " << (std1 < std2) << std::endl;
	std::cout << " <= : " << (first <= second) << " = " << (std1 <= std2) << std::endl;
	std::cout << " > : " << (first > second) << " = " << (std1 > std2) << std::endl;
	std::cout << " >= : " << (first >= second) << " = " << (std1 >= std2) << std::endl;
	std::cout << " != : " << (first != second) << " = " << (std1 != std2) << std::endl;
	std::cout << " == : " << (first == second) << " = " << (std1 == std2) << std::endl;
	if (redo)
		ft_eq_ope(second, first, std2, std1, 0);
}

int		itw_arrow(void)
{
	const int size = 5;
	ft::vector<TESTED_TYPE> vct(size);
	ft::vector<TESTED_TYPE>::iterator it(vct.begin());
	ft::vector<TESTED_TYPE>::const_iterator ite(vct.end());
	std::vector<TESTED_TYPE> svct(size);
	std::vector<TESTED_TYPE>::iterator sit(svct.begin());
	std::vector<TESTED_TYPE>::const_iterator site(svct.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
	for (int i = 1; sit != site; ++i)
		*sit++ = i;
	printSizeVs(vct, svct, 1);

	it = vct.begin();
	ite = vct.begin();
	sit = svct.begin();
	site = svct.begin();

	std::cout << *(++ite) << " == " << *(++site) << std::endl;
	std::cout << *(ite++) << " == " << *(site++) << std::endl;
	std::cout << *ite++ << " == " << *site++ << std::endl;
	std::cout << *++ite << " == " << *++site << std::endl;

	it->m();
	ite->m();
	sit->m();
	site->m();

	std::cout << *(++it) << " == " << *(++sit) << std::endl;
	std::cout << *(it++) << " == " << *(sit++) << std::endl;
	std::cout << *it++ << " == " << *sit++ << std::endl;
	std::cout << *++it << " == " << *++sit << std::endl;

	std::cout << *(--ite) << " == " << *(--site) << std::endl;
	std::cout << *(ite--) << " == " << *(site--) << std::endl;
	std::cout << *--ite << " == " << *--site << std::endl;
	std::cout << *ite-- << " == " << *site-- << std::endl;

	(*it).m();
	(*ite).m();
	(*sit).m();
	(*site).m();

	std::cout << *(--it) << " == " << *(--sit) << std::endl;
	std::cout << *(it--) << " == " << *(sit--) << std::endl;
	std::cout << *it-- << " == " << *sit-- << std::endl;
	std::cout << *--it << " == " << *--sit << std::endl;

	return (0);
}

void	ite_equ_test(void)
{
	const int size = 5;
	int i = 0;
	SPACE_FT::vector<TESTED_TYPE> vct(size);
	SPACE_FT::vector<TESTED_TYPE>::iterator it_0(vct.begin());
	SPACE_FT::vector<TESTED_TYPE>::iterator it_1(vct.end());
	SPACE_FT::vector<TESTED_TYPE>::iterator it_mid;
	SPACE_STD::vector<TESTED_TYPE> svct(size);
	SPACE_STD::vector<TESTED_TYPE>::iterator sit_0(svct.begin());
	SPACE_STD::vector<TESTED_TYPE>::iterator sit_1(svct.end());
	SPACE_STD::vector<TESTED_TYPE>::iterator sit_mid;

	SPACE_FT::vector<TESTED_TYPE>::const_iterator cit_0 = vct.begin();
	SPACE_FT::vector<TESTED_TYPE>::const_iterator cit_1;
	SPACE_FT::vector<TESTED_TYPE>::const_iterator cit_mid;
	SPACE_STD::vector<TESTED_TYPE>::const_iterator scit_0 = svct.begin();
	SPACE_STD::vector<TESTED_TYPE>::const_iterator scit_1;
	SPACE_STD::vector<TESTED_TYPE>::const_iterator scit_mid;

	for (int i = size; it_0 != it_1; --i)
		*it_0++ = i;
	for (int i = size; sit_0 != sit_1; --i)
		*sit_0++ = i;
	printSizeVs(vct, svct);
	it_0 = vct.begin();
	sit_0 = svct.begin();
	cit_1 = vct.end();
	scit_1 = svct.end();
	it_mid = it_0 + 3;
	sit_mid = sit_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;
	scit_mid = sit_0 + 3; scit_mid = scit_0 + 3; scit_mid = sit_mid;

	std::cout << std::boolalpha;
	std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;
	std::cout << std::boolalpha;
	std::cout << ((sit_0 + 3 == scit_0 + 3) && (scit_0 + 3 == sit_mid)) << std::endl;


	std::cout << "\t\tft_eq_ope:" << std::endl;
	std::cout << "Regular it :\n" << i++ << ": " << std::endl;
	ft_eq_ope(it_0 + 3, it_mid, sit_0 + 3, sit_mid);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_0, it_1, sit_0, sit_1);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_1 - 3, it_mid, sit_1 - 3, sit_mid);
	std::cout << "Const it :\n" << i++ << ": " << std::endl;
	std::cout << "1 :" << *(cit_0 + 3) << " | 2 :" << *(cit_mid) << " | 3 :" << *(sit_0 + 3) << " | 4 :" << *(sit_mid) << std::endl;
	ft_eq_ope(cit_0 + 3, cit_mid, scit_0 + 3, scit_mid); // false ?
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(cit_0, cit_1, scit_0, scit_1);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(cit_1 - 3, cit_mid, scit_1 - 3, scit_mid);
	std::cout << "Both it :\n" << i++ << ": " << std::endl;
	ft_eq_ope(it_mid, cit_0 + 3, sit_mid, scit_0 + 3);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_0, cit_1, sit_0, scit_1);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_1, cit_0, sit_1, scit_0);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_1 - 3, cit_mid, sit_1 - 3, scit_mid);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_mid, cit_1 - 3, sit_mid, scit_1 - 3);
}

void	rite2(void)
{
	const int size = 5;
	SPACE_FT::vector<TESTED_TYPE> vct(size);
	SPACE_FT::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	SPACE_FT::vector<TESTED_TYPE>::const_reverse_iterator ite = vct.rbegin();
	SPACE_STD::vector<TESTED_TYPE> svct(size);
	SPACE_STD::vector<TESTED_TYPE>::reverse_iterator sit = svct.rbegin();
	SPACE_STD::vector<TESTED_TYPE>::const_reverse_iterator site = svct.rbegin();

	for (int i = 0; i < size; ++i)
	{
		it[i] = (size - i) * 5;
		sit[i] = (size - i) * 5;
	}

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	sit = sit + 5;
	sit = 1 + sit;
	sit = sit - 4;
	std::cout << *(it += 2) << " = " << *(sit += 2) << std::endl;
	std::cout << *(it -= 1) << " = " << *(sit -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;
	*(sit -= 2) = 42;
	*(sit += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;
	std::cout << "const_ite +=/-=: " << *(site += 2) << " | " << *(site -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(it == const_it): " << (site == sit) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << "(" << *ite << " " << *it << ")" << std::endl;
	std::cout << "(const_ite - it): " << (site - sit) << "(" << *ite << " " << *it << ")" << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
	std::cout << "(ite + 3 == it): " << (site + 3 == sit) << std::endl;

	printSizeVs(vct, svct);
}

void	rite_equ_test(void)
{
	const int size = 5;
	int i = 0;
	SPACE_FT::vector<TESTED_TYPE> vct(size);
	SPACE_FT::vector<TESTED_TYPE>::reverse_iterator it_0(vct.rbegin());
	SPACE_FT::vector<TESTED_TYPE>::reverse_iterator it_1(vct.rend());
	SPACE_FT::vector<TESTED_TYPE>::reverse_iterator it_mid;
	SPACE_STD::vector<TESTED_TYPE> svct(size);
	SPACE_STD::vector<TESTED_TYPE>::reverse_iterator sit_0(svct.rbegin());
	SPACE_STD::vector<TESTED_TYPE>::reverse_iterator sit_1(svct.rend());
	SPACE_STD::vector<TESTED_TYPE>::reverse_iterator sit_mid;

	SPACE_FT::vector<TESTED_TYPE>::const_reverse_iterator cit_0 = vct.rbegin();
	SPACE_FT::vector<TESTED_TYPE>::const_reverse_iterator cit_1;
	SPACE_FT::vector<TESTED_TYPE>::const_reverse_iterator cit_mid;
	SPACE_STD::vector<TESTED_TYPE>::const_reverse_iterator scit_0 = svct.rbegin();
	SPACE_STD::vector<TESTED_TYPE>::const_reverse_iterator scit_1;
	SPACE_STD::vector<TESTED_TYPE>::const_reverse_iterator scit_mid;

	for (int i = size; it_0 != it_1; --i)
		*it_0++ = i;
	for (int i = size; sit_0 != sit_1; --i)
		*sit_0++ = i;
	printSizeVs(vct, svct);
	it_0 = vct.rbegin();
	cit_1 = vct.rend();
	it_mid = it_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;
	sit_0 = svct.rbegin();
	scit_1 = svct.rend();
	sit_mid = sit_0 + 3;
	scit_mid = sit_0 + 3; scit_mid = scit_0 + 3; scit_mid = sit_mid;

	std::cout << std::boolalpha;
	std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;
	std::cout << std::boolalpha;
	std::cout << ((sit_0 + 3 == scit_0 + 3) && (scit_0 + 3 == sit_mid)) << std::endl;

	std::cout << "\t\tft_eq_ope:" << std::endl;
	std::cout << "Regular it :\n" << i++ << ": " << std::endl;
	ft_eq_ope(it_0 + 3, it_mid, sit_0 + 3, sit_mid);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_0, it_1, sit_0, sit_1);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_1 - 3, it_mid, sit_1 - 3, sit_mid);
	std::cout << "Const it :\n" << i++ << ": " << std::endl;
	ft_eq_ope(cit_0 + 3, cit_mid, scit_0 + 3, scit_mid);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(cit_0, cit_1, scit_0, scit_1);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(cit_1 - 3, cit_mid, scit_1 - 3, scit_mid);
	std::cout << "Both it :\n" << i++ << ": " << std::endl;
	ft_eq_ope(it_0 + 3, cit_mid, sit_0 + 3, scit_mid);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_mid, cit_0 + 3, sit_mid, scit_0 + 3);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_0, cit_1, sit_0, scit_1);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_1, cit_0, sit_1, scit_0);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_1 - 3, cit_mid, sit_1 - 3, scit_mid);
	std::cout << i++ << ": "<< std::endl;
	ft_eq_ope(it_mid, cit_1 - 3, sit_mid, scit_1 - 3);
}

int	vector_tester()
{
	// vector_test();
	// vec_erase_test();
	// vec_assign_test();
	// vec_bidirectionalit_test();
	// vec_erased_test();
	// vec_insert_test();
	// test_copy_construct();
	// test_size();
	// test_swap();
	// test_iter_const();
	itw_arrow();
	// test_relational_op();
	// ite_equ_test();
	// rite2();
	// rite_equ_test();
	return (1);
}