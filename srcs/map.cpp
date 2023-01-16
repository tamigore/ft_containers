// #include "map.hpp"
#include <map>
#include <list>

#ifndef STD
	// #include <ft.hpp>
	#include <map.hpp>
	// #include <stack.hpp>
	// #include <vector.hpp>
	#define NAMESPACE ft
#else
	#include <map>
	#include <stack>
	#include <vector>
	#define NAMESPACE std
#endif

#define TESTED_TYPE int

# include <iostream>
# include <string>


typedef NAMESPACE::map<int, int>::iterator			iterator;
typedef NAMESPACE::map<int, int>::const_iterator	const_iterator;


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
void	printReverse(NAMESPACE::map<U1, U2> &mp)
{
	typename NAMESPACE::map<U1, U2>::iterator it = mp.end(), ite = mp.begin();

	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
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

	NAMESPACE::map<int, std::string> mp(lst.begin(), lst.end());
	lst.clear();

	printSize(mp);
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
	NAMESPACE::map<char, int> mp1;
	NAMESPACE::map<char, int> mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	cmp(mp1, mp1); // 0
	cmp(mp1, mp2); // 1

	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

	cmp(mp1, mp2); // 2
	cmp(mp2, mp1); // 3

	mp1.begin()->second = 42;
	(++(++mp1.begin()))->second = 42;

	cmp(mp1, mp2); // 4
	cmp(mp2, mp1); // 5

	swap(mp1, mp2);

	cmp(mp1, mp2); // 6
	cmp(mp2, mp1); // 7
	
	return (0);
}

static int iter = 0;

void	bound(NAMESPACE::map<int, int> &mp, const int &param)
{
	iterator	ite = mp.end(), it[2];
	NAMESPACE::pair<iterator, iterator>	ft_range;

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

void	const_bound(const NAMESPACE::map<int, int> &mp, const int &param)
{
	const_iterator ite = mp.end(), it[2];
	NAMESPACE::pair<const_iterator, const_iterator> ft_range;

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
	NAMESPACE::map<int, int> mp(lst.begin(), lst.end());
	printSize(mp);

	const_bound(mp, -10);
	const_bound(mp, 1);
	const_bound(mp, 5);
	const_bound(mp, 10);
	const_bound(mp, 50);

	printSize(mp);

	mp.lower_bound(3)->second = 404;
	mp.upper_bound(7)->second = 842;
	bound(mp, 5);
	bound(mp, 7);

	printSize(mp);
	return (0);
}

void    map_construct()
{
    std::list<std::map<int, int>::value_type> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::map<int, int>::value_type(lst_size - i, i));

	NAMESPACE::map<int, int> mp(lst.begin(), lst.end());
	iterator it = mp.begin(), ite = mp.end();

	printSize(mp);
	NAMESPACE::map<int, int> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;

	it = mp.begin(); ite = --(--mp.end());
	NAMESPACE::map<int, int> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);

	mp = mp_copy;
	mp_copy = mp_range;
	mp_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);
	std::cout << "mp destroy" << std::endl;
	mp.~map();
	std::cout << "mp_range destroy" << std::endl;
	mp_range.~map();
	std::cout << "mp_copy destroy" << std::endl;
	mp_copy.~map();
	std::cout << "WHY ????" << std::endl; 
} // leaks here for destructor of std::map

static int count_erase = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << count_erase++ << "] --" << std::endl;
	mp.erase(param);
	// printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << count_erase++ << "] --" << std::endl;
	mp.erase(param, param2);
	// printSize(mp);
}

int		erase(void)
{
	std::list<std::pair<const int, std::string> > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::pair<const int, std::string>(i, std::string((lst_size - i), i + 65)));
	NAMESPACE::map<int, std::string> mp(lst.begin(), lst.end());
	printSize(mp);
	int i = 0;
	std::cout << "erase :" << i++ << std::endl;
	ft_erase(mp, ++mp.begin());
	printSize(mp);

	std::cout << "erase :" << i++ << std::endl;
	ft_erase(mp, mp.begin());
	printSize(mp);
	std::cout << "erase :" << i++ << std::endl;
	ft_erase(mp, --mp.end());
	printSize(mp);

	std::cout << "erase :" << i++ << std::endl;
	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
	printSize(mp);
	std::cout << "erase :" << i++ << std::endl;
	ft_erase(mp, --(--(--mp.end())), --mp.end());
	printSize(mp);

	std::cout << "[10] Hello insert" << std::endl;
	mp[10] = "Hello";
	std::cout << "[11] Hi there insert" << std::endl;
	mp[11] = "Hi there";
	printSize(mp);
	ft_erase(mp, --(--(--mp.end())), mp.end());
	printSize(mp);

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
	printSize(mp);
	ft_erase(mp, mp.begin(), mp.end());
	printSize(mp);
	return (0);
}

typedef NAMESPACE::map<char, foo<float> >::const_iterator const_it;

static unsigned int i = 0;

void	ft_comp(const NAMESPACE::map<char, foo<float> > &mp, const const_it &it1, const const_it &it2)
{
	bool res[2];

	std::cout << "\t-- [" << ++i << "] --" << std::endl;
	res[0] = mp.key_comp()(it1->first, it2->first);
	res[1] = mp.value_comp()(*it1, *it2);
	std::cout << "with [" << it1->first << " and " << it2->first << "]: ";
	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}

int		comp(void)
{
	NAMESPACE::map<char, foo<float> >	mp;

	mp['a'] = 2.3;
	mp['b'] = 1.4;
	mp['c'] = 0.3;
	mp['d'] = 4.2;
	printSize(mp);

	for (const_it it1 = mp.begin(); it1 != mp.end(); ++it1)
		for (const_it it2 = mp.begin(); it2 != mp.end(); ++it2)
			ft_comp(mp, it1, it2);

	printSize(mp);
	return (0);
}

// int		ite_n1(void)
// {
// 	NAMESPACE::map<int, int> const mp;
// 	NAMESPACE::map<int, int>::iterator it = mp.begin(); // <-- error expected

// 	(void)it;
// 	return (0);
// }

typedef NAMESPACE::map<int, std::string> mapy;
typedef NAMESPACE::map<int, std::string>::iterator ity;

void	ft_find(mapy mp, ity it, int const &k)
{
	ity	ret = mp.find(k);

	if (ret != it)
		printPair(ret);
	else
		std::cout << "ft map::find(" << k << ") returned end()" << std::endl;
}

void	ft_count(mapy mp, int const &k)
{
	std::cout << "ft map::count(" << k << ")\treturned [" << mp.count(k) << "]" << std::endl;
}

int		find_count(void)
{
	mapy mp;
	ity it = mp.end();

	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	printSize(mp);

	std::cout << "\t-- FIND --" << std::endl;
	ft_find(mp, it, 12);
	ft_find(mp, it, 3);
	ft_find(mp, it, 35);
	ft_find(mp, it, 90);
	ft_find(mp, it, 100);

	std::cout << "\t-- COUNT --" << std::endl;
	ft_count(mp, -3);
	ft_count(mp, 12);
	ft_count(mp, 3);
	ft_count(mp, 35);
	ft_count(mp, 90);
	ft_count(mp, 100);

	mp.find(27)->second = "newly inserted mapped_value";

	printSize(mp);

	NAMESPACE::map<int, std::string> const c_map(mp.begin(), mp.end());
	std::cout << "const map.find(" << 42 << ")->second: [" << c_map.find(42)->second << "]" << std::endl;
	std::cout << "const map.count(" << 80 << "): [" << c_map.count(80) << "]" << std::endl;
	return (0);
}

int		ite_arrow(void)
{
	std::list<std::pair<const float, foo<int> > > lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::pair<const float, foo<int> >(2.5 + i, i + 1));

	NAMESPACE::map<int, foo<int> > mp(lst.begin(), lst.end());
	NAMESPACE::map<int, foo<int> >::iterator it(mp.begin());
	NAMESPACE::map<int, foo<int> >::const_iterator ite(mp.begin());
	printSize(mp);

	printPair(++ite);
	printPair(ite++);
	printPair(ite++);
	printPair(++ite);

	std::cout << "FOO TEST:" << std::endl;
	it->second.m();
	ite->second.m();

	printPair(++it);
	printPair(it++);
	printPair(it++);
	printPair(++it);

	printPair(--ite);
	printPair(ite--);
	printPair(--ite);
	printPair(ite--);

	std::cout << "FOO TEST:" << std::endl;
	(*it).second.m();
	(*ite).second.m();

	printPair(--it);
	printPair(it--);
	printPair(it--);
	printPair(--it);
	return (0);
}

int	map_tester()
{
	map_construct();
	map_bounds();
	TrickyMapConstruct();
	relational_op();
	erase();
	comp();
	// ite_n1();
	ite_arrow();
	find_count();
	return (0);
}
