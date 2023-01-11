#include "map.hpp"
#include <map>
#include <list>

// #define std std
// #define ft ft
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

	// std::cout << mp1.begin() << std::endl;
	mp1.begin()->second = 42;
	smp1.begin()->second = 42;
	(++(++mp1.begin()))->second = 42;
	(++(++smp1.begin()))->second = 42;

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

template <typename MAP1, typename MAP2>
void	ft_erase(MAP1 &fmp, MAP2 &smp, int pos)
{
	std::cout << "\t-- [" << count_erase++ << "] --" << std::endl;
	if (param == 1)
	fmp.erase(param);
	smp.erase(param);
	printSizeVs(fmp, smp);
}

template <typename MAP1, typename MAP2>
void	ft_erase(MAP1 &fmp, MAP2 &smp, int pos1, int pose2)
{
	ft_iterator start = fmp.begin(), stop = fmp.begin();
	std_iterator start1 = smp.begin(), stop1 = smp.begin();
	std::cout << "\t-- [" << count_erase++ << "] --" << std::endl;
	if (pos1 < 0)
	{
		start = fmp.end();
		start1 = smp.end();
	}
	if (pos2 < 0)
	{
		start = fmp.end();
		start1 = smp.end();
	}
	fmp.erase(param, param2);
	smp.erase(param, param2);
	printSizeVs(fmp, smp);
}

int		erase(void)
{
	std::list<std::pair<const int, std::string> > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::pair<const int, std::string>(i, std::string((lst_size - i), i + 65)));
	ft::map<int, std::string> mp(lst.begin(), lst.end());
	std::map<int, std::string> smp(lst.begin(), lst.end());
	printSizeVs(mp, smp);
	int i = 0;
	std::cout << "erase :" << i++ << std::endl;
	ft_erase(mp, ++mp.begin());
	ft_erase(smp, ++smp.begin());
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp, smp);

	std::cout << "erase :" << i++ << std::endl;
	ft_erase(mp, mp.begin());
	ft_erase(smp, smp.begin());
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp, smp);
	std::cout << "erase :" << i++ << std::endl;
	ft_erase(mp, --mp.end());
	ft_erase(smp, --smp.end());
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp, smp);

	std::cout << "erase :" << i++ << std::endl;
	// ft::map<int, std::string>::iterator it = mp.begin();
	// ++(++(++it));
	// it++;
	// it++;
	// std::cout << it << std::endl;
	// std::cout << ++(++(++mp.begin())) << std::endl;
	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
	ft_erase(smp, smp.begin(), ++(++(++smp.begin())));
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp, smp);
	std::cout << "erase :" << i++ << std::endl;
	ft_erase(mp, --(--(--mp.end())), --mp.end());
	ft_erase(smp, --(--(--smp.end())), --smp.end());
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp, smp);

	std::cout << "[10] Hello insert" << std::endl;
	mp[10] = "Hello";
	smp[10] = "Hello";
	std::cout << "[11] Hi there insert" << std::endl;
	mp[11] = "Hi there";
	smp[11] = "Hi there";
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp, smp);
	ft_erase(mp, --(--(--mp.end())), mp.end());
	ft_erase(smp, --(--(--smp.end())), smp.end());
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp, smp);

	mp[12] = "ONE";
	smp[12] = "ONE";
	mp[13] = "TWO";
	smp[13] = "TWO";
	mp[14] = "THREE";
	smp[14] = "THREE";
	mp[15] = "FOUR";
	smp[15] = "FOUR";
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp, smp);
	ft_erase(mp, mp.begin(), mp.end());
	ft_erase(smp, smp.begin(), smp.end());
	// mp.get_tree()->prettyPrint();
	printSizeVs(mp, smp);
	return (0);
}

typedef ft::map<char, foo<float> >::const_iterator const_it;

static unsigned int i = 0;

void	ft_comp(const ft::map<char, foo<float> > &mp, const const_it &it1, const const_it &it2)
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
	ft::map<char, foo<float> >	mp;

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
// 	ft::map<int, int> const mp;
// 	ft::map<int, int>::iterator it = mp.begin(); // <-- error expected

// 	(void)it;
// 	return (0);
// }

// int		ite_n2(void)
// {
// 	{
// 		std::map<char,int> mymap;
// 		mymap['b'] = 100;
// 		mymap['a'] = 200;
// 		mymap['c'] = 300;
// 		// show content:
// 		{
// 			std::map<int, int>::const_iterator it = mymap.begin();
// 			while (it != mymap.end())
// 			{
// 				std::cout << it->first << " => " << it->second << '\n';
// 				it++;
// 			}
// 		}
// 		{
// 			for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
// 				std::cout << it->first << " => " << it->second << '\n';
// 		}
// 	}
// 	// {
// 	// 	ft::map<char,int> mymap;
// 	// 	mymap['b'] = 100;
// 	// 	mymap['a'] = 200;
// 	// 	mymap['c'] = 300;
// 	// 	// show content:
// 	// 	{
// 	// 		ft::map<int, int>::const_iterator it = mymap.begin();
// 	// 		while (it != mymap.end())
// 	// 		{
// 	// 			std::cout << it->first << " => " << it->second << '\n';
// 	// 			it++;
// 	// 		}
// 	// 	}
// 	// 	{
// 	// 		for (ft::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
// 	// 			std::cout << it->first << " => " << it->second << '\n';
// 	// 	}
// 	// }
// 	return 0;
// }

typedef ft::map<int, std::string> ft_map;
typedef ft::map<int, std::string>::iterator ft_it;
typedef std::map<int, std::string> std_map;
typedef std::map<int, std::string>::iterator std_it;

void	ft_find(ft_map mp, std_map smp, ft_it it, std_it sit, int const &k)
{
	ft_it	ret = mp.find(k);
	std_it	sret = smp.find(k);

	if (ret != it)
		printPair(ret);
	else
		std::cout << "ft map::find(" << k << ") returned end()" << std::endl;
	if (sret != sit)
		printPair(sret);
	else
		std::cout << "std map::find(" << k << ") returned end()" << std::endl;
}

void	ft_count(ft_map mp, std_map smp, int const &k)
{
	std::cout << "ft map::count(" << k << ")\treturned [" << mp.count(k) << "]" << std::endl;
	std::cout << "std map::count(" << k << ")\treturned [" << smp.count(k) << "]" << std::endl;
}

int		find_count(void)
{
	ft_map mp;
	ft_it it = mp.end();
	std_map smp;
	std_it sit = smp.end();

	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	smp[42] = "fgzgxfn";
	smp[25] = "funny";
	smp[80] = "hey";
	smp[12] = "no";
	smp[27] = "bee";
	smp[90] = "8";
	printSizeVs(mp, smp);

	std::cout << "\t-- FIND --" << std::endl;
	ft_find(mp, smp, it, sit, 12);
	ft_find(mp, smp, it, sit, 3);
	ft_find(mp, smp, it, sit, 35);
	ft_find(mp, smp, it, sit, 90);
	ft_find(mp, smp, it, sit, 100);

	std::cout << "\t-- COUNT --" << std::endl;
	ft_count(mp, smp, -3);
	ft_count(mp, smp, 12);
	ft_count(mp, smp, 3);
	ft_count(mp, smp, 35);
	ft_count(mp, smp, 90);
	ft_count(mp, smp, 100);

	mp.find(27)->second = "newly inserted mapped_value";
	smp.find(27)->second = "newly inserted mapped_value";

	printSizeVs(mp, smp);

	ft::map<int, std::string> const c_map(mp.begin(), mp.end());
	std::map<int, std::string> const s_map(smp.begin(), smp.end());
	std::cout << "const map.find(" << 42 << ")->second: [" << c_map.find(42)->second << "]" << std::endl;
	std::cout << "const map.find(" << 42 << ")->second: [" << s_map.find(42)->second << "]" << std::endl;
	std::cout << "const map.count(" << 80 << "): [" << c_map.count(80) << "]" << std::endl;
	std::cout << "const map.count(" << 80 << "): [" << s_map.count(80) << "]" << std::endl;
	return (0);
}

int		ite_arrow(void)
{
	std::list<std::pair<const float, foo<int> > > lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::pair<const float, foo<int> >(2.5 + i, i + 1));

	ft::map<int, foo<int> > mp(lst.begin(), lst.end());
	ft::map<int, foo<int> >::iterator it(mp.begin());
	ft::map<int, foo<int> >::const_iterator ite(mp.begin());
	std::map<int, foo<int> > smp(lst.begin(), lst.end());
	std::map<int, foo<int> >::iterator sit(smp.begin());
	std::map<int, foo<int> >::const_iterator site(smp.begin());
	printSizeVs(mp, smp);

	printPair(++ite);
	printPair(++site);
	printPair(ite++);
	printPair(site++);
	printPair(ite++);
	printPair(site++);
	printPair(++ite);
	printPair(++site);

	std::cout << "FOO TEST:" << std::endl;
	it->second.m();
	ite->second.m();
	sit->second.m();
	site->second.m();

	printPair(++it);
	printPair(++sit);
	printPair(it++);
	printPair(sit++);
	printPair(it++);
	printPair(sit++);
	printPair(++it);
	printPair(++sit);

	printPair(--ite);
	printPair(--site);
	printPair(ite--);
	printPair(site--);
	printPair(--ite);
	printPair(--site);
	printPair(ite--);
	printPair(site--);

	std::cout << "FOO TEST:" << std::endl;
	(*it).second.m();
	(*sit).second.m();
	(*ite).second.m();
	(*site).second.m();

	printPair(--it);
	printPair(--sit);
	printPair(it--);
	printPair(sit--);
	printPair(it--);
	printPair(sit--);
	printPair(--it);
	printPair(--sit);
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
	// ite_n1(); //pls help
	// ite_n2();
	ite_arrow();
	find_count();
	return (0);
}
