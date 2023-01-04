#include "map.hpp"
#include <map>
#include <list>

#define SPACE_STD std
#define SPACE_FT ft
#define TESTED_TYPE int

#define T1 int
#define T2 int
typedef std::pair<const T1, T2> T3;

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

		if (it != ite)
			std::cout << "ft ite = " << *ite << std::endl;
		if (s_it != s_ite)
			std::cout << "std ite = [" << s_ite->first << "," << s_ite->second << "]" << std::endl;

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

// typedef SPACE_FT::map<T1, T2>::value_type		T3;
typedef SPACE_FT::map<T1, T2>::iterator			ft_iterator;
typedef SPACE_FT::map<T1, T2>::const_iterator	ft_const_iterator;
typedef SPACE_STD::map<T1, T2>::value_type		SFT3;
typedef SPACE_STD::map<T1, T2>::iterator		std_iterator;
typedef SPACE_STD::map<T1, T2>::const_iterator	std_const_iterator;

static int iter = 0;

void	ft_bound(ft::map<T1, T2> &mp, const T1 &param)
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

void	std_bound(std::map<T1, T2> &mp, const T1 &param)
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

// template <typename MAP>
// void	ft_const_bound(const MAP &mp, const T1 &param)
// {
// 	ft_const_iterator ite = mp.end(), it[2];
// 	ft::pair<ft_const_iterator, ft_const_iterator> ft_range;

// 	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
// 	std::cout << "with key [" << param << "]:" << std::endl;
// 	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
// 	ft_range = mp.equal_range(param);
// 	std::cout << "lower_bound: ";
// 	if (it[0] == ite)
// 		std::cout << "end()" << std::endl;
// 	else
// 		std::cout << "[" << it[0]->first << "," << it[0]->second << "]" << std::endl;
// 	std::cout << "upper_bound: ";
// 	if (it[1] == ite)
// 		std::cout << "end()" <<std::endl;
// 	else
// 		std::cout << "[" << it[1]->first << "," << it[1]->second << "]" << std::endl;
// 	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
// }

// template <typename MAP>
// void	std_const_bound(const MAP &mp, const T1 &param)
// {
// 	std_const_iterator ite = mp.end(), it[2];
// 	std::pair<std_const_iterator, std_const_iterator> ft_range;

// 	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
// 	std::cout << "with key [" << param << "]:" << std::endl;
// 	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
// 	ft_range = mp.equal_range(param);
// 	std::cout << "lower_bound: ";
// 	if (it[0] == ite)
// 		std::cout << "end()" << std::endl;
// 	else
// 		std::cout << "[" << it[0]->first << "," << it[0]->second << "]" << std::endl;
// 	std::cout << "upper_bound: ";
// 	if (it[1] == ite)
// 		std::cout << "end()" <<std::endl;
// 	else
// 		std::cout << "[" << it[1]->first << "," << it[1]->second << "]" << std::endl;
// 	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
// }

int		map_bounds(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i + 1, (i + 1) * 3));
	SPACE_FT::map<T1, T2> mp(lst.begin(), lst.end());
	SPACE_STD::map<T1, T2> smp(lst.begin(), lst.end());
	printSizeVs(mp, smp);

	// ft_const_bound(mp, -10);
	// ft_const_bound(mp, 1);
	// ft_const_bound(mp, 5);
	// ft_const_bound(mp, 10);
	// ft_const_bound(mp, 50);
	// std_const_bound(smp, -10);
	// std_const_bound(smp, 1);
	// std_const_bound(smp, 5);
	// std_const_bound(smp, 10);
	// std_const_bound(smp, 50);

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
    std::list<T3> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(lst_size - i, i));

	SPACE_FT::map<T1, T2> mp(lst.begin(), lst.end());
	SPACE_FT::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();
	SPACE_STD::map<T1, T2> smp(lst.begin(), lst.end());
	SPACE_STD::map<T1, T2>::iterator sit = smp.begin(), site = smp.end();

	printSizeVs(mp, smp);
	SPACE_FT::map<T1, T2> mp_range(it, ite);
	// SPACE_FT::map<T1, T2> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;
	SPACE_STD::map<T1, T2> smp_range(sit, site);
	// SPACE_STD::map<T1, T2> smp_range(sit, --(--site));
	for (int i = 0; sit != site; ++sit)
		sit->second = ++i * 5;

	it = mp.begin(); ite = mp.end();
	// it = mp.begin(); ite = --(--mp.end());
	SPACE_FT::map<T1, T2> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;
	sit = smp.begin(); site = smp.end();
	// sit = smp.begin(); site = --(--smp.end());
	SPACE_STD::map<T1, T2> smp_copy(smp);
	for (int i = 0; sit != site; ++sit)
		sit->second = ++i * 7;


	std::cout << "\t-- PART ONE --" << std::endl;
	printSizeVs(mp, smp);
	mp.get_tree()->prettyPrint();
	printSizeVs(mp_range, smp_range);
	mp_range.get_tree()->prettyPrint();
	printSizeVs(mp_copy, smp_range);
	mp_copy.get_tree()->prettyPrint();

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
    map_construct();
	map_bounds();
	return (0);
}
