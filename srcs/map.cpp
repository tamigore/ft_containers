#include "map.hpp"
#include <map>
#include <list>

#define std std
#define ft ft
#define TESTED_TYPE int

# include <iostream>
# include <string>

typedef ft::map<int, int>::iterator			ft_iterator;
typedef ft::map<int, int>::const_iterator	ft_const_iterator;
typedef std::map<int, int>::iterator		std_iterator;
typedef std::map<int, int>::const_iterator	std_const_iterator;

// --- Class foo
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
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename U1, typename U2>
void	printReverse(ft::map<U1, U2> &mp)
{
	typename ft::map<U1, U2>::iterator it = mp.end(), ite = mp.begin();

	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}

template <typename Key, typename T>
void	printSizeVs(ft::map<Key ,T> const &ft_map, std::map<Key ,T> const &std_map, bool print_content = true)
{
	std::cout << "___________________ft vs std___________________" << std::endl;
	const int ft_size = ft_map.size();
	const int std_size = std_map.size();

	std::cout << "ft_size: " << ft_size << " == std_size: " << std_size <<std::endl;
	std::cout << "ft_max_size: " << (ft_map.max_size() == std_map.max_size() ? "OK" : "KO") << std::endl;
	if (print_content)
	{
		typename ft::map<Key,T>::const_iterator it = ft_map.begin();
		typename ft::map<Key,T>::const_iterator ite = ft_map.end();
		typename std::map<Key,T>::const_iterator s_it = std_map.begin();
		typename std::map<Key,T>::const_iterator s_ite = std_map.end();

		std::cout << std::endl << "Content is:" << std::endl;
		int i = 0;
		while (it != ite)
		{
			if (s_it == s_ite)
			{
				std::cout << "to much elem :" << std::endl;
				while (it != ite)
				{
					std::cout << i << "- ft: [" << it->first << "," << it->second << "]" << std::endl;
					it++;
				}
				break ;
			}
			else
				std::cout << i << "- ft: [" << it->first << "," << it->second << "] == [" << s_it->first << "," << s_it->second << "] :std" << std::endl;
			s_it++;
			it++;
			i++;
		}
		if (s_it != s_ite)
		{
			std::cout << "not enought elem :" << std::endl;
			while (s_it != s_ite)
			{
				std::cout << i << "- std: [" << s_it->first << "," << s_it->second << "]" << std::endl;
				s_it++;
			}
		}
	}
	std::cout << "_______________________________________________" << std::endl;
}

int		TrickyMapConstruct(void)
{
	std::list<std::map<int, std::string>::value_type> lst;
	std::list<std::map<int, std::string>::value_type>::iterator itlst;

	lst.push_back(std::map<int, std::string>::value_type(42, "lol"));
	lst.push_back(std::map<int, std::string>::value_type(50, "mdr"));
	lst.push_back(std::map<int, std::string>::value_type(35, "funny"));
	lst.push_back(std::map<int, std::string>::value_type(45, "bunny"));
	lst.push_back(std::map<int, std::string>::value_type(21, "fizz"));
	lst.push_back(std::map<int, std::string>::value_type(35, "this key is already inside"));
	lst.push_back(std::map<int, std::string>::value_type(55, "fuzzy"));
	lst.push_back(std::map<int, std::string>::value_type(38, "buzz"));
	lst.push_back(std::map<int, std::string>::value_type(55, "inside too"));

	std::cout << "List contains: " << lst.size() << " elements." << std::endl;
	for (itlst = lst.begin(); itlst != lst.end(); ++itlst)
		printPair(itlst);
	std::cout << "---------------------------------------------" << std::endl;

	ft::map<int, std::string> mp(lst.begin(), lst.end());
	std::map<int, std::string> smp(lst.begin(), lst.end());
	lst.clear();

	printSize(mp);
	printSizeVs(mp, smp);
	return (0);
}

template <class MAP>
void	cmp(const MAP &lhs, const MAP &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int		relational_op(void)
{
	ft::map<char, int> mp1;
	ft::map<char, int> mp2;
	std::map<char, int> smp1;
	std::map<char, int> smp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;
	smp1['a'] = 2; smp1['b'] = 3; smp1['c'] = 4; smp1['d'] = 5;
	smp2['a'] = 2; smp2['b'] = 3; smp2['c'] = 4; smp2['d'] = 5;

	cmp(mp1, mp1); // 0
	cmp(smp1, smp1); // 0
	cmp(mp1, mp2); // 1
	cmp(smp1, smp2); // 1

	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;
	smp2['e'] = 6; smp2['f'] = 7; smp2['h'] = 8; smp2['h'] = 9;

	cmp(mp1, mp2); // 2
	cmp(smp1, smp2); // 2
	cmp(mp2, mp1); // 3
	cmp(smp2, smp1); // 3

	std::cout << mp1.begin() << std::endl;
	mp1.begin()->second = 42;
	smp1.begin()->second = 42;
	// (++(++mp1.begin()))->second = 42;
	// (++(++smp1.begin()))->second = 42;

	cmp(mp1, mp2); // 4
	cmp(smp1, smp2); // 4
	cmp(mp2, mp1); // 5
	cmp(smp2, smp1); // 5

	swap(mp1, mp2);
	swap(smp1, smp2);

	cmp(mp1, mp2); // 6
	cmp(smp1, smp2); // 6
	cmp(mp2, mp1); // 7
	cmp(smp2, smp1); // 7
	
	return (0);
}

static int iter = 0;

void	ft_bound(ft::map<int, int> &mp, const int &param)
{
	ft_iterator ite = mp.end(), it[2];
	ft::pair<ft_iterator, ft_iterator>	ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: ";
	if (it[0] == ite)
		std::cout << "end()" << std::endl;
	else
		std::cout << "[" << it[0]->first << "," << it[0]->second << "]" << std::endl;
	std::cout << "upper_bound: ";
	if (it[1] == ite)
		std::cout << "end()" <<std::endl;
	else
		std::cout << "[" << it[1]->first << "," << it[1]->second << "]" << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

void	std_bound(std::map<int, int> &mp, const int &param)
{
	std_iterator ite = mp.end(), it[2];
	std::pair<std_iterator, std_iterator>	ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: ";
	if (it[0] == ite)
		std::cout << "end()" << std::endl;
	else
		std::cout << "[" << it[0]->first << "," << it[0]->second << "]" << std::endl;
	std::cout << "upper_bound: ";
	if (it[1] == ite)
		std::cout << "end()" <<std::endl;
	else
		std::cout << "[" << it[1]->first << "," << it[1]->second << "]" << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

void	ft_const_bound(const ft::map<int, int> &mp, const int &param)
{
	ft_const_iterator ite = mp.end(), it[2];
	ft::pair<ft_const_iterator, ft_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: ";
	if (it[0] == ite)
		std::cout << "end()" << std::endl;
	else
		std::cout << "[" << it[0]->first << "," << it[0]->second << "]" << std::endl;
	std::cout << "upper_bound: ";
	if (it[1] == ite)
		std::cout << "end()" <<std::endl;
	else
		std::cout << "[" << it[1]->first << "," << it[1]->second << "]" << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

void	std_const_bound(const std::map<int, int> &mp, const int &param)
{
	std_const_iterator ite = mp.end(), it[2];
	std::pair<std_const_iterator, std_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: ";
	if (it[0] == ite)
		std::cout << "end()" << std::endl;
	else
		std::cout << "[" << it[0]->first << "," << it[0]->second << "]" << std::endl;
	std::cout << "upper_bound: ";
	if (it[1] == ite)
		std::cout << "end()" <<std::endl;
	else
		std::cout << "[" << it[1]->first << "," << it[1]->second << "]" << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

int		map_bounds(void)
{
	std::list<std::map<int, int>::value_type> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::map<int, int>::value_type(i + 1, (i + 1) * 3));
	ft::map<int, int> mp(lst.begin(), lst.end());
	std::map<int, int> smp(lst.begin(), lst.end());
	printSizeVs(mp, smp);

	ft_const_bound(mp, -10);
	ft_const_bound(mp, 1);
	ft_const_bound(mp, 5);
	ft_const_bound(mp, 10);
	ft_const_bound(mp, 50);
	std_const_bound(smp, -10);
	std_const_bound(smp, 1);
	std_const_bound(smp, 5);
	std_const_bound(smp, 10);
	std_const_bound(smp, 50);

	printSizeVs(mp, smp);

	mp.lower_bound(3)->second = 404;
	mp.upper_bound(7)->second = 842;
	ft_bound(mp, 5);
	ft_bound(mp, 7);
	smp.lower_bound(3)->second = 404;
	smp.upper_bound(7)->second = 842;
	std_bound(smp, 5);
	std_bound(smp, 7);

	printSizeVs(mp, smp);
	return (0);
}

void    map_construct()
{
    std::list<std::map<int, int>::value_type> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::map<int, int>::value_type(lst_size - i, i));

	ft::map<int, int> mp(lst.begin(), lst.end());
	ft_iterator it = mp.begin(), ite = mp.end();
	std::map<int, int> smp(lst.begin(), lst.end());
	std_iterator sit = smp.begin(), site = smp.end();

	printSizeVs(mp, smp);
	// ft::map<int, int> mp_range(it, ite);
	ft::map<int, int> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;
	// std::map<int, int> smp_range(sit, site);
	std::map<int, int> smp_range(sit, --(--site));
	for (int i = 0; sit != site; ++sit)
		sit->second = ++i * 5;

	// it = mp.begin(); ite = mp.end();
	it = mp.begin(); ite = --(--mp.end());
	ft::map<int, int> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;
	// sit = smp.begin(); site = smp.end();
	sit = smp.begin(); site = --(--smp.end());
	std::map<int, int> smp_copy(smp);
	for (int i = 0; sit != site; ++sit)
		sit->second = ++i * 7;


	std::cout << "\t-- PART ONE --" << std::endl;
	printSizeVs(mp, smp);
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp_range, smp_range);
	// mp_range.get_tree()->prettyPrint();
	printSizeVs(mp_copy, smp_range);
	// mp_copy.get_tree()->prettyPrint();

	mp = mp_copy;
	mp_copy = mp_range;
	mp_range.clear();
	smp = smp_copy;
	smp_copy = smp_range;
	smp_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSizeVs(mp, smp);
	printSizeVs(mp_range, smp_range);
	printSizeVs(mp_copy, smp_copy);
	std::cout << "mp destroy" << std::endl;
	mp.~map();
	std::cout << "mp_range destroy" << std::endl;
	mp_range.~map();
	std::cout << "mp_copy destroy" << std::endl;
	mp_copy.~map();
}

int	map_tester()
{
	// map_construct();
	// map_bounds();
	// TrickyMapConstruct();
	relational_op();
	return (0);
}
