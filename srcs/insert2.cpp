#include <map>
#include "../includes/map.hpp"

#include <list>
#include <iostream>
#include <string>

#define T1 int
#define T2 std::string
typedef ft::map<T1, T2>::value_type T3;
typedef ft::map<T1, T2>::iterator iterator;

static int iter = 0;

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

template <typename MAP, typename U>
void	ft_insert(MAP &mp, U param, U param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.insert(param, param2);
	printSize(mp);
}

int		main(void)
{
	std::list<T3> lst;
	std::list<T3>::iterator itlst;

	lst.push_back(T3(42, "lol"));

	lst.push_back(T3(50, "mdr"));
	lst.push_back(T3(35, "funny"));

	lst.push_back(T3(45, "bunny"));
	lst.push_back(T3(21, "fizz"));
	lst.push_back(T3(38, "buzz"));
	lst.push_back(T3(55, "fuzzy"));

	std::cout << "List contains:" << std::endl;
	for (itlst = lst.begin(); itlst != lst.end(); ++itlst)
		printPair(itlst);

	ft::map<T1, T2> mp;
	ft_insert(mp, lst.begin(), lst.end());

	lst.clear();

	lst.push_back(T3(87, "hey"));
	lst.push_back(T3(47, "eqweqweq"));
	lst.push_back(T3(35, "this key is already inside"));
	lst.push_back(T3(23, "but not that one"));
	lst.push_back(T3(1, "surprising isnt it?"));
	lst.push_back(T3(100, "is it enough??"));
	lst.push_back(T3(55, "inside map too"));

	std::cout << "List contains:" << std::endl;
	for (itlst = lst.begin(); itlst != lst.end(); ++itlst)
		printPair(itlst);

	ft_insert(mp, lst.begin(), lst.begin());
	ft_insert(mp, lst.begin(), lst.end());

	return (0);
}
