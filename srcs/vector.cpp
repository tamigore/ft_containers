#include <iostream>
#include <list>

#define TESTED_TYPE foo<int>
#include "test_utils.hpp"


#ifndef STD
	// #include <ft.hpp>
	// #include <map.hpp>
	// #include <stack.hpp>
	#include <vector.hpp>
	#define NAMESPACE ft
#else
	// #include <map>
	// #include <stack>
	#include <vector>
	#define NAMESPACE std
#endif

using namespace NAMESPACE;

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

template <typename T_VEC>
void	printSize(T_VEC const &vec, bool print_content = 1)
{
	const int size = vec.size();
	const int capacity = vec.capacity();

	std::cout << "___________________printSize___________________" << std::endl;
	std::cout << "size: " << size << std::endl;
	std::cout << "capacity is ok ? : " << ((capacity >= size) ? "OK" : "KO") << std::endl;
	std::cout << "max_size: " << vec.max_size() << std::endl;
	if (print_content)
	{
		typename T_VEC::const_iterator it = vec.begin();
		typename T_VEC::const_iterator ite = vec.end();
		std::cout << std::endl << "Content is:" << std::endl;
		int i = 0;
		for (; it != ite; ++it)
			std::cout << "-" << i++ << " : [" << *it << "]" << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}

void	vec_test_assign()
{
	NAMESPACE::vector<int> vct(7);
	NAMESPACE::vector<int> vct_two(4);
	NAMESPACE::vector<int> vct_three;
	NAMESPACE::vector<int> vct_four;

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

}

int		at_const(void)
{
	NAMESPACE::vector<int> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	printSize(vct);

	NAMESPACE::vector<int> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	for (unsigned long int i = 0; i < vct_c.size(); ++i)
		std::cout << "vct_c.at(): " << vct_c.at(i) << std::endl;
	try {
		std::cout << vct_c.at(10) << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
	printSize(vct_c);
	return (0);
}

int		at(void)
{
	NAMESPACE::vector<int> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct.at(): " << vct.at(i) << " | ";
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	printSize(vct);

	NAMESPACE::vector<int> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	try
	{
		vct.at(10) = 42;
	}
	catch (std::out_of_range &e)
	{
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
	return (0);
}

int		vec_bidirect_it(void)
{
	std::list<int> lst;
	std::list<int>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	NAMESPACE::vector<int> vct(lst.begin(), lst.end());
	printSize(vct);

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	printSize(vct);

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	printSize(vct);
	return (0);
}

void	vec_copy_construct()
{
	NAMESPACE::vector<int>		vct(5);
	NAMESPACE::vector<int>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
			*it = (ite - it);

	it = vct.begin();
	NAMESPACE::vector<int> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
			*it = ++i * 5;

	it = vct.begin();
	NAMESPACE::vector<int> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
			*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);
}

void	prepost_incdec(NAMESPACE::vector<int> &vct)
{
	NAMESPACE::vector<int>::iterator it = vct.begin();
	NAMESPACE::vector<int>::iterator it_tmp;

	std::cout << "Pre inc" << std::endl;
	it_tmp = ++it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Pre dec" << std::endl;
	it_tmp = --it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post inc" << std::endl;
	it_tmp = it++;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post dec" << std::endl;
	it_tmp = it--;
	std::cout << *it_tmp << " | " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}

int		vec_ite(void)
{
	const int size = 5;
	NAMESPACE::vector<int> vct(size);
	NAMESPACE::vector<int>::iterator it = vct.begin();
	NAMESPACE::vector<int>::const_iterator ite = vct.begin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;
	prepost_incdec(vct);

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
	std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	printSize(vct, true);
	return (0);
}


int vec_all()
{
	// Create a vector containing integers
	NAMESPACE::vector<int>	vec;

	// Add two more integers to vector
	vec.push_back(25);
	vec.push_back(13);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(5);
	vec.push_back(3);
 
	// Print out the vector
	for (size_t n = 0; n < vec.size(); n++)
		std::cout << "vec[" << n << "] = " << vec[n] << std::endl;

	NAMESPACE::vector<int> vct(7);
	NAMESPACE::vector<int> vct_two(4);
	NAMESPACE::vector<int> vct_three;
	NAMESPACE::vector<int> vct_four;

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
	printSize(vct);
	printSize(vct_three);
	printSize(vct_two);
	printSize(vct_four);

	std::cout << "\t### After assign(): ###" << std::endl;

	vct_four.assign(6, 84);
	printSize(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);
	printSize(vct);
	printSize(vct_two);
	printSize(vct_three);
	printSize(vct_four);
	vct.clear();
	vct_two.erase(++(vct_two.begin()), --(vct_two.end()));
	vct_three.erase(++(++vct_three.begin()));
	vct_four.erase(--(--vct_four.end()));
	// This causes abort of std::vector XD
	// std::cout << "afte all" << std::endl;
	// vct.~vector();
	// std::cout << "vec destroyed" << std::endl;
	// vct_two.~vector();
	// std::cout << "vec_two destroyed" << std::endl;
	// vct_three.~vector();
	// std::cout << "vec_three destroyed" << std::endl;
	// vct_four.~vector();
	// std::cout << "vec_four destroyed" << std::endl;
	return (1);
}

void	vec_erase()
{
	NAMESPACE::vector<char>	_v0;
	int i = 0;
	_v0.push_back('1');
	_v0.push_back('0');
	_v0.push_back('a');
	_v0.push_back('c');
	_v0.push_back('k');
	printSize(_v0);
	std::cout << "erase ret[" << i++ << "] = " << *(_v0.erase(_v0.begin() + 2)) << std::endl;
	std::cout << "erase ret[" << i++ << "] = " << *(_v0.erase(_v0.begin())) << std::endl;
	printSize(_v0);
	_v0.push_back('z');
	_v0.push_back('y');
	_v0.push_back('x');
	_v0.push_back('w');
	printSize(_v0);
	std::cout << "erase ret[" << i++ << "] = " << *(_v0.erase(_v0.begin() + 1, _v0.end() - 3)) << std::endl;
	printSize(_v0);
	std::cout << "erase ret[" << i++ << "] = " << *(_v0.erase(_v0.begin(), _v0.end())) << std::endl;
	printSize(_v0);
}


void    checkErase(NAMESPACE::vector<std::string> const &vct, NAMESPACE::vector<std::string>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "vec[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

void	vec_erased()
{
	NAMESPACE::vector<std::string>		vct(10);

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
}

void	vec_insert()
{
	std::cout << "FIRST PART" << std::endl;
	{
		NAMESPACE::vector<int> vec(10);
		NAMESPACE::vector<int> vec2;
		NAMESPACE::vector<int> vec3;

		for (unsigned long int i = 0; i < vec.size(); ++i)
			vec[i] = (vec.size() - i) * 3;
		printSize(vec);

		vec2.resize(4);
		vec2.insert(vec2.end(), 42);
		printSize(vec2);

		vec2.insert(vec2.begin(), 2, 21);
		printSize(vec2);

		vec2.insert(vec2.end() - 2, 42);
		printSize(vec2);

		vec2.insert(vec2.end(), 2, 84);
		printSize(vec2);

		vec2.resize(4);
		printSize(vec2);

		vec2.insert(vec2.begin() + 2, vec.begin(), vec.end());
		vec.clear();
		printSize(vec2);

		for (int i = 0; i < 5; ++i)
				vec3.insert(vec3.end(), i);
		printSize(vec3);
		vec3.insert(vec3.begin() + 1, 2, 111);
		printSize(vec3);
	}
	std::cout << std::endl;
	std::cout << "SECOND PART" << std::endl;
	{
		NAMESPACE::vector<int> vct(5);
		NAMESPACE::vector<int> vct2;
		const int cut = 3;

		for (unsigned long int i = 0; i < vct.size(); ++i)
				vct[i] = (vct.size() - i) * 7;
		printSize(vct);

		vct2.insert(vct2.begin(), vct.begin(), vct.begin() + cut);
		printSize(vct2);
		vct2.insert(vct2.begin(), vct.begin() + cut, vct.end());
		printSize(vct2);
		vct2.insert(vct2.end(), vct.begin(), vct.begin() + cut);
		printSize(vct2);

		std::cout << "insert return:" << std::endl;

		std::cout << *vct2.insert(vct2.end(), 42) << std::endl;
		printSize(vct2);
		std::cout << *vct2.insert(vct2.begin() + 5, 84) << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		printSize(vct2);
	}
	std::cout << std::endl;
}

int		vec_arrow(void)
{
	const int size = 5;
	NAMESPACE::vector<TESTED_TYPE> vct(size);
	NAMESPACE::vector<TESTED_TYPE>::iterator it(vct.begin());
	NAMESPACE::vector<TESTED_TYPE>::const_iterator ite(vct.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
	printSize(vct, 1);

	it = vct.begin();
	ite = vct.begin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	it->m();
	ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	(*it).m();
	(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;

	return (0);
}

void	is_empty(NAMESPACE::vector<int> const &vct)
{
        std::cout << "ft is_empty: " << vct.empty() << std::endl;
}

void	vec_size()
{
	const int start_size = 7;
	NAMESPACE::vector<int> vct(start_size, 20);
	NAMESPACE::vector<int> vct2;
	NAMESPACE::vector<int>::iterator it = vct.begin();

	for (int i = 2; i < start_size; ++i)
			it[i] = (start_size - i) * 3;
	printSize(vct);

	vct.resize(10, 42);
	printSize(vct);

	vct.resize(18, 43);
	printSize(vct);
	vct.resize(10);
	printSize(vct);
	vct.resize(23, 44);
	printSize(vct);
	vct.resize(5);
	printSize(vct);
	vct.reserve(5);
	vct.reserve(3);
	printSize(vct);
	vct.resize(87);
	vct.resize(5);
	printSize(vct);

	is_empty(vct2);
	vct2 = vct;
	is_empty(vct2);
	vct.reserve(vct.capacity() + 1);
	printSize(vct);
	printSize(vct2);

	vct2.resize(0);
	is_empty(vct2);
	printSize(vct2);
}

void	vec_swap()
{
	NAMESPACE::vector<int> foo(3, 15);
	NAMESPACE::vector<int> bar(5, 42);
	NAMESPACE::vector<int>::const_iterator it_foo = foo.begin();
	NAMESPACE::vector<int>::const_iterator it_bar = bar.begin();

	std::cout << "BEFORE SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSize(foo);
	std::cout << "bar contains:" << std::endl;
	printSize(bar);

	foo.swap(bar);

	std::cout << "AFTER SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSize(foo);
	std::cout << "bar contains:" << std::endl;
	printSize(bar);

	std::cout << "Iterator validity:" << std::endl;
	std::cout << (it_foo == bar.begin()) << std::endl;
	std::cout << (it_bar == foo.begin()) << std::endl;
	std::cout << "END" << std::endl;
}

// void	iter_const(void)
// {
// 	{
// 		const int size = 5;
// 		NAMESPACE::vector<int> vct(size);
// 		NAMESPACE::vector<int>::iterator it = vct.begin();
// 		NAMESPACE::vector<int>::const_iterator ite = vct.begin();
// 		for (int i = 0; i < size; ++i)
// 				it[i] = i;
// 		std::cout << "ok ?" << std::endl;
// 		ite[1] = 42; // < -- error
// 		std::cout << "KO !" << std::endl;
// 	}
// 	{
// 		const int size = 5;
// 		NAMESPACE::vector<int> vct(size);
// 		NAMESPACE::vector<int>::iterator it = vct.begin();
// 		NAMESPACE::vector<int>::const_iterator ite = vct.begin();
// 		for (int i = 0; i < size; ++i)
// 			it[i] = i;
// 		std::cout << "ok ?" << std::endl;
// 		*ite = 42; // < -- error
// 		std::cout << "KO !" << std::endl;
// 	}
// 	{
// 		const int size = 5;
// 		NAMESPACE::vector<int> const vct(size);
// 		NAMESPACE::vector<int>::iterator it = vct.begin(); // <-- error expected
// 		std::cout << "ok ?" << std::endl;
// 		for (int i = 0; i < size; ++i)
// 				it[i] = i;
// 		std::cout << "KO !" << std::endl;
// 	}
// }

template <class T, class Alloc>
void    cmp(const NAMESPACE::vector<T, Alloc> &lhs, const NAMESPACE::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;

	std::cout << " eq == : " << std::boolalpha << (lhs == rhs) << " | ne != : " << (lhs != rhs) << std::endl;
	std::cout << " lt  < : " << std::boolalpha << (lhs <  rhs) << " | le <= : " << (lhs <= rhs) << std::endl;
	std::cout << " gt  > : " << std::boolalpha << (lhs >  rhs) << " | ge >= : " << (lhs >= rhs) << std::endl;
}

void	vec_relational_op()
{
	NAMESPACE::vector<TESTED_TYPE>	vct(4);
	NAMESPACE::vector<TESTED_TYPE>	vct2(4);

	cmp(vct, vct);  // 0
	cmp(vct, vct2); // 1

	vct2.resize(10);

	cmp(vct, vct2); // 2
	cmp(vct2, vct); // 3

	vct[2] = 42;

	cmp(vct, vct2); // 4
	cmp(vct2, vct); // 5
	printSize(vct);
	printSize(vct2);

	swap(vct, vct2);

	printSize(vct);
	printSize(vct2);
	cmp(vct, vct2); // 6
	cmp(vct2, vct); // 7
	cmp(vct, vct); // 8
}

template <typename Ite_1, typename Ite_2>
void eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	std::cout << " <  : " << (first < second)  << std::endl;
	std::cout << " <= : " << (first <= second) << std::endl;
	std::cout << " >  : " << (first > second)  << std::endl;
	std::cout << " >= : " << (first >= second) << std::endl;
	std::cout << " != : " << (first != second) << std::endl;
	std::cout << " == : " << (first == second) << std::endl;
	if (redo)
		eq_ope(second, first, 0);
}

void	vec_ite_equ(void)
{
	const int size = 5;
	int i = 0;
	NAMESPACE::vector<TESTED_TYPE> vct(size);
	NAMESPACE::vector<TESTED_TYPE>::iterator it_0(vct.begin());
	NAMESPACE::vector<TESTED_TYPE>::iterator it_1(vct.end());
	NAMESPACE::vector<TESTED_TYPE>::iterator it_mid;

	NAMESPACE::vector<TESTED_TYPE>::const_iterator cit_0 = vct.begin();
	NAMESPACE::vector<TESTED_TYPE>::const_iterator cit_1;
	NAMESPACE::vector<TESTED_TYPE>::const_iterator cit_mid;

	for (int i = size; it_0 != it_1; --i)
		*it_0++ = i;
	printSize(vct);
	it_0 = vct.begin();
	cit_1 = vct.end();
	it_mid = it_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

	std::cout << std::boolalpha;
	std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;


	std::cout << "\t\teq_ope:" << std::endl;
	std::cout << "Regular it :\n" << i++ << ": " << std::endl;
	eq_ope(it_0 + 3, it_mid);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_0, it_1);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_1 - 3, it_mid);
	std::cout << "Const it :\n" << i++ << ": " << std::endl;
	std::cout << "1 :" << *(cit_0 + 3) << " | 2 :" << *(cit_mid) << std::endl;
	eq_ope(cit_0 + 3, cit_mid); // false ?
	std::cout << i++ << ": "<< std::endl;
	eq_ope(cit_0, cit_1);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(cit_1 - 3, cit_mid);
	std::cout << "Both it :\n" << i++ << ": " << std::endl;
	eq_ope(it_mid, cit_0 + 3);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_0, cit_1);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_1, cit_0);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_1 - 3, cit_mid);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_mid, cit_1 - 3);
}

int		rev_ite_consruct(void)
{
	NAMESPACE::vector<TESTED_TYPE> vct;
	NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();
	NAMESPACE::vector<TESTED_TYPE>::const_iterator cit = vct.begin();

	NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rit(it);

	NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit(rit);
	NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit_(it);
	NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit_2(cit);

	// error expected
	// NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rit_(crit);
	// NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rit2(cit);
	// NAMESPACE::vector<TESTED_TYPE>::iterator it2(rit);
	// NAMESPACE::vector<TESTED_TYPE>::const_iterator cit2(crit);

	std::cout << "OK" << std::endl;
	return (0);
}


void	vec_rite2(void)
{
	const int size = 5;
	NAMESPACE::vector<TESTED_TYPE> vct(size);
	NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << "(" << *ite << " " << *it << ")" << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	printSize(vct);
}

void	vec_rite_equ(void)
{
	const int size = 5;
	int i = 0;
	NAMESPACE::vector<TESTED_TYPE> vct(size);
	NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it_0(vct.rbegin());
	NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it_1(vct.rend());
	NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it_mid;

	NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator cit_0 = vct.rbegin();
	NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator cit_1;
	NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator cit_mid;

	for (int i = size; it_0 != it_1; --i)
		*it_0++ = i;
	printSize(vct);
	it_0 = vct.rbegin();
	cit_1 = vct.rend();
	it_mid = it_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

	std::cout << std::boolalpha;
	std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

	std::cout << "\t\teq_ope:" << std::endl;
	std::cout << "Regular it :\n" << i++ << ": " << std::endl;
	eq_ope(it_0 + 3, it_mid);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_0, it_1);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_1 - 3, it_mid);
	std::cout << "Const it :\n" << i++ << ": " << std::endl;
	eq_ope(cit_0 + 3, cit_mid);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(cit_0, cit_1);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(cit_1 - 3, cit_mid);
	std::cout << "Both it :\n" << i++ << ": " << std::endl;
	eq_ope(it_0 + 3, cit_mid);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_mid, cit_0 + 3);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_0, cit_1);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_1, cit_0);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_1 - 3, cit_mid);
	std::cout << i++ << ": "<< std::endl;
	eq_ope(it_mid, cit_1 - 3);
}

template <class T>
void	print(vector<vector<T> >& lst)
{
	for (typename vector<vector<T> >::iterator it = lst.begin(); it != lst.end(); it++)
	{
		for (typename vector<T>::iterator it2 = it->begin(); it2 != it->end(); it2++)
			cout << *it2 << ' ';
		cout << '\n';
	}
}

template <class T>
void	print(vector<T>& lst)
{
	for (typename vector<T>::iterator it = lst.begin(); it != lst.end(); it++)
		cout << *it << ' ';
	cout << '\n';
}
class Awesome {

	public:

		Awesome( void ) : _n( 42 ) { std::cout << "Default constructor" << std::endl; } //should not happen too often or else there is a wrong use of allocator (which calls the copy constructor)
		Awesome( int n ) : _n( n ) { std::cout << "Int constructor" << std::endl; (void)n; }
		Awesome( Awesome const &rhs ) : _n( 42 ) { *this = rhs;}
		virtual ~Awesome(void) {}

		Awesome &operator=( Awesome const & rhs ) { this->_n = rhs._n; return (*this); }
		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		void operator+=(int rhs){ _n += rhs; }
		int get( void ) const { return this->_n; }

	private:

		int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

template <class T>
void	print_vector(vector<T> &test)
{
	typename vector<T>::iterator		beg = test.begin();
	typename vector<T>::iterator		end = test.end();
	std::cout << "size : " << test.size() << ", capacity : " << test.capacity() << std::endl;
	for (typename vector<T>::iterator it = beg; it != end; it++)
	{
		std::cout << *it << " ";
		if (((it - beg) % 10 == 9) && it > beg)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <class T>
void	push_pop_back_tests(void)
{
	std::cout << std::endl << "PUSH BACK & POP BACK TESTS" << std::endl;
	vector<T> test;

	std::cout << "Empty ? " << test.empty() << " / Capacity : " << test.capacity() << " / Size : " << test.size() << std::endl;
	for (size_t i = 0; i < 51; i++)
	{
		test.push_back(i);
		std::cout << test.size() << ": " << test.capacity() << " - ";
		if (!(i % 10) && i != 0)
			std::cout << std::endl;
	}
	print_vector<T>(test);
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	print_vector<T>(test);
}

template <class T>
void	resize_tests(void)
{
	std::cout << std::endl << "RESIZE TESTS" << std::endl;
	vector<T> test(12, 12);

	test.resize(72);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(100);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(4170);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(171, 12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.resize(62);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
}

template <class T>
void	insert_tests()
{
	std::cout << std::endl << "INSERT TESTS" << std::endl;
	vector<T> test(1, 1);
	vector<T> test2(5, 5);

	test.insert(test.begin(), 200, 12);
	print_vector<T>(test);
	test.insert(test.begin() + 12, 200, 30);
	print_vector<T>(test);
	test.insert(test.end(), 12, 50);
	print_vector<T>(test);
	test.insert(test.end() - 1, 0, 60);
	print_vector<T>(test);
	test.insert(test.end() - 1, 1, 70);
	print_vector<T>(test);
	test.insert(test.begin() + 412, test2.begin(), test2.end());
	print_vector<T>(test);
	test.insert(test.begin() + 6, test2.begin(), test2.end());
	print_vector<T>(test);
	test.insert(test.end(), test2.begin(), test2.end());
	print_vector<T>(test);
}

template <class T>
void	reserve_tests(void)
{
	std::cout << std::endl << "RESERVE TESTS" << std::endl;
	vector<T> test(65, 7);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(12);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(66);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(128);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(1023);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	test.reserve(10252);
	std::cout << "s: " << test.size() << ", c: " << test.capacity() << std::endl;
	try
	{
		test.reserve(test.max_size() + 1);
	}
	catch(std::length_error &le)
	{
		std::cout << "length error" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}
	print_vector<T>(test);
}

template <class T>
void	copy_swap_tests(void)
{
	std::cout << std::endl << "COPY && SWAP TESTS" << std::endl;
	vector<T> test;
	for (size_t i = 0; i < 50; i++) { test.push_back(i); }
	vector<T> test_copy(test);
	for (size_t i = 0; i < test_copy.size(); i++) { test_copy[i] += 100; }
	print_vector<T>(test_copy);
	vector<T> test_range(test.begin() + 20, test.begin() + 30);
	print_vector<T>(test_range);
	test_copy.swap(test);
	print_vector<T>(test);
	print_vector<T>(test_copy);
	test_copy.swap(test_range);
	print_vector<T>(test_range);
	print_vector<T>(test_copy);
	test.swap(test_copy);
	print_vector<T>(test);
	print_vector<T>(test_copy);
}

template <class T>
void	reverse_it_tests(void)
{
	std::cout << std::endl << "REVERSE IT TESTS" << std::endl;
	vector<T> test;
	for (size_t i = 0; i < 12; i++) { test.push_back(i); }
	typename vector<T>::reverse_iterator		revbeg = test.rbegin();
	for (typename vector<T>::reverse_iterator it = revbeg; it != test.rend(); it++)
	{
		std::cout << *it << " ";
		if (!((revbeg - it) % 10) && it != revbeg)
			std::cout << std::endl;
	}
	std::cout << *(test.rbegin() + 2) << std::endl;
	std::cout << *(test.rend() - 8) << std::endl;
	std::cout << (test.rbegin() == revbeg) << std::endl;
	revbeg++;
	std::cout << *revbeg << std::endl;
	std::cout << (test.rbegin() == test.rend()) << std::endl;
	std::cout << (test.rbegin() <= test.rbegin()) << std::endl;
	std::cout << (test.rbegin() < test.rend()) << std::endl;
	std::cout << (test.rbegin() >= test.rend()) << std::endl;
	revbeg += 3;
	std::cout << *revbeg << std::endl;
	std::cout << std::endl;
}

template <class T>
void	erase_clear_tests(void)
{
	std::cout << std::endl << "ERASE && CLEAR TESTS" << std::endl;
	vector<T> test(31, 12);
	test.erase(test.begin(), test.begin() + 5);
	print_vector<T>(test);
	test.erase(test.begin() + 12, test.begin() + 16);
	print_vector<T>(test);
	test.clear();
	print_vector<T>(test);
}

void	max_size_tests(void)
{
	std::cout << std::endl << "MAX SIZE TESTS" << std::endl;
	vector<int> test(31, 12);
	vector<std::string> test2;
	vector<long long int> test3;
	vector<Awesome> test4;
	vector<unsigned int> test5(12, 340);
	std::cout << test.max_size() << std::endl;
	std::cout << test2.max_size() << std::endl;
	std::cout << test3.max_size() << std::endl;
	std::cout << test4.max_size() << std::endl;
	std::cout << test5.max_size() << std::endl;
}

void	awesome_tests(void)
{
	std::cout << std::endl << "AWESOME TESTS" << std::endl;
	vector<Awesome> test(21, 12);
	print_vector<Awesome>(test);
	vector<Awesome> test2;
	print_vector<Awesome>(test2);
	test2.push_back(12);
	test2.push_back(8);
	test2.push_back(16);
	print_vector<Awesome>(test2);
	std::cout << "SAME ?" << (test.begin() + 1 == test2.begin() + 1) << std::endl;
	test.assign(test2.begin(), test2.end());
	print_vector<Awesome>(test);
	test = test2;
	print_vector<Awesome>(test);
	std::cout << "SAME ?" << (test.begin() + 1 == test2.begin() + 1) << std::endl;
	test.insert(test.end(), test2.begin(), test2.end());
	print_vector<Awesome>(test);
	test.insert(test.begin(), test2.begin(), test2.end());
	test2 = test;
	print_vector<Awesome>(test);
	std::cout << "end awesome test" << std::endl;
}

int main_mazoi()
{
	push_pop_back_tests<int>();
	resize_tests<int>();
	insert_tests<int>();
	reserve_tests<int>();
	copy_swap_tests<int>();
	reverse_it_tests<int>();
	erase_clear_tests<int>();
	max_size_tests();
	awesome_tests();
	push_pop_back_tests<Awesome>();
	resize_tests<Awesome>();
	insert_tests<Awesome>();
	reserve_tests<Awesome>();
	copy_swap_tests<Awesome>();
	reverse_it_tests<Awesome>();
	erase_clear_tests<Awesome>();
	return (0);
}

int vec_string_main()
{
	vector<string> JOHN;
	vector<string> BOB(5, "Hello");
	cout << "BOB(5, 8) : ";
	for (size_t i = 0; i < BOB.size(); i++)
		cout << BOB[i] << ' ';
	cout << '\n';
	vector<string> MIKE(BOB);

	// CTORs
	cout << "\nCTORS\n";
	cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	cout << "BOB is empty? " << BOB.empty() << '\n';

	cout << "Size of JOHN " << JOHN.size() << std::endl;
	cout << "Size of BOB " << BOB.size() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;


	// RESIZE
	size_t	bob_resize = 2;
	cout << "\nRESIZE\n";
	BOB.resize(bob_resize);
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 53\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 58\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 63\n";

	size_t	mike_resize = 9;
	bob_resize = 0;
	
	BOB.resize(bob_resize);
	cout << "BOB is empty now ? " << BOB.empty() << '\n';
	MIKE.resize(mike_resize, "juste some random string");
	/*
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	cout << "Capacity of JOHN " << JOHN.capacity() << std::endl;
	cout << "Size of BOB " << BOB.size() << std::endl;
	cout << "Capacity of BOB " << BOB.capacity() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	cout << "Capacity of MIKE " << MIKE.capacity() << std::endl;
	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 86\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 91\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_resize)
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 96\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	// RESERVE
	cout << "\nRESERVE\n";

	size_t	john_reserve = 5;
	size_t	bob_reserve = 3;
	size_t	mike_reserve = 83;

	JOHN.reserve(john_reserve);
	BOB.reserve(bob_reserve);
	MIKE.reserve(mike_reserve);
	/*
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	cout << "Capacity of JOHN " << JOHN.capacity() << std::endl;
	cout << "Size of BOB " << BOB.size() << std::endl;
	cout << "Capacity of BOB " << BOB.capacity() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	cout << "Capacity of MIKE " << MIKE.capacity() << std::endl;
	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= john_reserve)
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 120\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_reserve)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 125\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_reserve)
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 130\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//AT
	cout << "\nAT\n";
	try
	{
		cout << MIKE.at(2) << '\n';
		cout << MIKE.at(87) << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		cout << "OOR error caught\n";
	}

	// FRONT / BACK
	cout << "\nFRONT / BACK\n";
	cout << "front() of MIKE : " << MIKE.front() << '\n';
	cout << "back() of MIKE : " << MIKE.back() << '\n';

	//ASSIGN
	cout << "\nASSIGN\n";
	BOB.assign(42, "James BOND");

	//ASSIGN RANGE
	cout << "\nASSIGN RANGE\n";
	vector<string>	assign_range;
	assign_range.assign(8, "Covfefe");
	assign_range.assign(BOB.begin() + 1, BOB.end() - 2);

	//EMPTY
	cout << "\nEMPTY\n";
	cout << "BOB is empty ? " << BOB.empty() << '\n';
	cout << "BOB at(41) : " << BOB.at(41) << '\n';

	//PUSH/POP_BACK
	cout << "\nPUSH/POP_BACK\n";
	BOB.push_back("My name is Bond");
	cout << "last elem of BOB : " << BOB.back() << '\n';
	BOB.pop_back();
	cout << "last elem of BOB : " << BOB.back() << '\n';

	//INSERT
	cout << "\nINSERT\n";
	vector<string>	insert_in_me;
	for (size_t i = 0; i < 15; i++)
		insert_in_me.push_back(ft::to_string(i) + " I love hbaudet\n");
	cout << "after push_back, before at\n";
	for (size_t i = 0; i < insert_in_me.size(); i++)
		cout << insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<string>::iterator	tmp;
	tmp = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp, 8, "Norminet");
	for (size_t i = 0; i < insert_in_me.size(); i++)
		cout << insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<string>::const_iterator const_it(insert_in_me.begin());
	cout << "Const it : " << std::endl;
	cout << *const_it << '\n';
//	*const_it = 89; // Does not compile because it's a const_iterator


	//INSERT
	cout << "\nINSERT\n";
	vector<string>	std_insert_in_me;
	for (size_t i = 0; i < 15; i++)
		std_insert_in_me.push_back(ft::to_string(i) + " 42 ");
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		cout << std_insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<string>::iterator	std_tmp;
	std_tmp = std_insert_in_me.begin() + 4;
	std_insert_in_me.insert(std_tmp, 8, "Why are you reading this!?");
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		cout << std_insert_in_me.at(i) << ' ';
	cout << '\n';


	//INSERT RANGE
	cout << "\nINSERT RANGE\n";
	vector<string>	insert_bis;
	for (size_t i = 0; i < 7; i++)
		insert_bis.push_back(ft::to_string(3 * i));
	for (size_t i = 0; i < insert_bis.size(); i++)
		cout << insert_bis[i] << ' ';
	cout << '\n';

	insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
	for (size_t i = 0; i < insert_bis.size(); i++)
		cout << insert_bis[i] << ' ';
	cout << '\n';


	//ERASE
	cout << "\nERASE\n";
	vector<string>	erase_in_me;
	for (size_t i = 0; i < 15; i++)
		erase_in_me.push_back(ft::to_string(2 * i));
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
//		if (erase_in_me[i] < 10)
//			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 7);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
//		if (erase_in_me[i] < 10)
//			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
//		if (erase_in_me[i] < 10)
//			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	//SWAP
	cout << "\nSWAP\n";
	BOB.swap(MIKE);
	/*
	cout << "Size of BOB " << BOB.size() << std::endl;
	cout << "Capacity of BOB " << BOB.capacity() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	cout << "Capacity of MIKE " << MIKE.capacity() << std::endl;
	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 272\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 277\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 282\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	MIKE.swap(JOHN);
	/*
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	cout << "Capacity of JOHN " << JOHN.capacity() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	cout << "Capacity of MIKE " << MIKE.capacity() << std::endl;
	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 298\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 303\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 308\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//CLEAR
	cout << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();
	/*
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	cout << "Capacity of JOHN " << JOHN.capacity() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	cout << "Capacity of MIKE " << MIKE.capacity() << std::endl;
	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 327\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 332\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 337\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//NON MEMBER Functions
	cout << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);
	/*
	cout << "Size of BOB " << BOB.size() << std::endl;
	cout << "Capacity of BOB " << BOB.capacity() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	cout << "Capacity of MIKE " << MIKE.capacity() << std::endl;
	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 355\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 360\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 365\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;
	
	//RELATIONAL OPERATORS
	cout << "\nRELATIONAL OPERATORS\n";
	vector<string> MIKE_2(MIKE);
	cout << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	cout << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';

	vector<string> real;
	real.assign(5, "foo");
	for (vector<string>::iterator it = real.begin(); it != real.end(); it++)
		cout << *it << " ";
	cout << '\n';

	cout << std::endl;
	return (0);
}


int	vector_tester()
{
	vec_test_assign();
	vec_bidirect_it();
	vec_copy_construct();
	vec_erase();
	vec_erased();
	vec_insert();
	vec_arrow();
	vec_ite();
	vec_ite_equ();
	// iter_const();
	vec_size();
	vec_swap();
	vec_all();
	vec_relational_op();
	vec_rite2();
	vec_rite_equ();
	main_mazoi();
	vec_string_main();
	return (1);
}