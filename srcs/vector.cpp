#include <iostream>
#include <list>

#define TESTED_TYPE foo<int>

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
	// std::cout << "capacity: " << capacity << " | capacity is ok ? : " << ((capacity >= size) ? "OK" : "KO") << std::endl;
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

	try {
		vct.at(10) = 42;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
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
	std::cout << "afte all" << std::endl;
	vct.~vector();
	std::cout << "vec destroyed" << std::endl;
	vct_two.~vector();
	std::cout << "vec_two destroyed" << std::endl;
	vct_three.~vector();
	std::cout << "vec_three destroyed" << std::endl;
	vct_four.~vector();
	std::cout << "vec_four destroyed" << std::endl;
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

		// vec2.resize(4);
		vec2.insert(vec2.end(), 42);
		printSize(vec2);

		vec2.insert(vec2.begin(), 2, 21);
		printSize(vec2);

		// std::cout << *(vec2.end() - 2) << " || " << (vec2._end - 2) << std::endl;
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
	return (1);
}