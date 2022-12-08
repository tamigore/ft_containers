#include "map.hpp"
#include <map>
#include <list>

#define SPACE_STD std
#define SPACE_FT ft
#define TESTED_TYPE int

#define T1 int
#define T2 int
typedef ft::pair<const T1, T2> T3;

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
		for (; it != ite; ++it)
		{
			if (s_it == s_ite)
				std::cout << "to much elem" << std::endl;
			else
			{
				std::cout << i << "- ft: |" << *it  << std::endl;// "| == |" << *s_it << "| :std" << std::endl;
				s_it++;
			}
			i++;
		}
	}
	std::cout << "_______________________________________________" << std::endl;
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

	SPACE_FT::map<T1, T2> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;
	SPACE_STD::map<T1, T2> smp_range(sit, --(--site));
	for (int i = 0; sit != site; ++sit)
		sit->second = ++i * 5;

	it = mp.begin(); ite = --(--mp.end());
	SPACE_FT::map<T1, T2> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;
	sit = smp.begin(); site = --(--smp.end());
	SPACE_STD::map<T1, T2> smp_copy(smp);
	for (int i = 0; sit != site; ++sit)
		sit->second = ++i * 7;


	std::cout << "\t-- PART ONE --" << std::endl;
	printSizeVs(mp, smp);
	printSizeVs(mp_range, smp_range);
	printSizeVs(mp_copy, smp_range);

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
}

int	map_tester()
{
    map_construct();
	return (0);
}
