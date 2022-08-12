#include <iostream>

#include "../includes/vector.hpp"
#include "../includes/map.hpp"
#include "../includes/stack.hpp"
#include <vector>
#include <map>
#include <stack>

void	print_vector(ft::vector<int> &fv, std::vector<int> &sv)
{
	std::cout << "=================================================" << std::endl;
	std::cout << "ft" << std::endl;
	std::cout << "size: " << fv.size() << " / capacity: " << fv.capacity() << std::endl << "[ ";
	for (ft::vector<int>::iterator it = fv.begin(); it != fv.end(); it++)
		std::cout << *it << " ";
	std::cout << "]" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "std" << std::endl;
	std::cout << "size: " << sv.size() << " / capacity: " << sv.capacity() << std::endl << "[ ";;
	for (std::vector<int>::iterator it = sv.begin(); it != sv.end(); it++)
		std::cout << *it << " ";
	std::cout << "]" << std::endl << "=================================================" << std::endl << std::endl;
}

void	print_map(ft::map<int, char> &fm, std::map<int, char> &sm)
{
	std::cout << "=================================================" << std::endl;
	std::cout << "ft" << std::endl;
	std::cout << "size: " << fm.size()  << std::endl << "[ ";
	for (ft::map<int, char>::iterator it = fm.begin(); it != fm.end(); it++)
		std::cout << "(" << it->first << "," << it->second << ") ";
	std::cout << "]" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "std" << std::endl;
	std::cout << "size: " << sm.size()  << std::endl << "[ ";;
	for (std::map<int, char>::iterator it = sm.begin(); it != sm.end(); it++)
		std::cout << "(" << it->first << "," << it->second << ") ";
	std::cout << "]" << std::endl << "=================================================" << std::endl << std::endl;
}

int	main(void)
{
	std::cout << "<vector - default constructor>" << std::endl;
	ft::vector<int> fv;
	std::vector<int> sv;
	print_vector(fv, sv);

	std::cout << "<vector - fill constructor>" << std::endl;
	ft::vector<int> fv2(5, 99);
	std::vector<int> sv2(5, 99);
	print_vector(fv2, sv2);

	std::cout << "<vector - copy constructor>" << std::endl;
	ft::vector<int> fv3(fv2);
	std::vector<int> sv3(sv2);
	print_vector(fv3, sv3);
	
	std::cout << "<vector - assignment operator>" << std::endl;
	ft::vector<int> fv4 = fv3;
	std::vector<int> sv4 = sv3;
	print_vector(fv4, sv4);
	
	std::cout << "<vector - push_back>" << std::endl;
	ft::vector<int> fv5;
	std::vector<int> sv5;
	for (int i=0; i<10; i++)
	{
		fv5.push_back(i);
		sv5.push_back(i);
	}
	print_vector(fv5, sv5);

	std::cout << "<vector - pop_back>" << std::endl;
	for (int i=0; i<5; i++)
	{
		fv5.pop_back();
		sv5.pop_back();
	}
	print_vector(fv5, sv5);

	std::cout << "<vector - assign>" << std::endl;
	fv5.assign(fv2.begin(), fv2.end());
	sv5.assign(sv2.begin(), sv2.end());
	print_vector(fv5, sv5);
	
	std::cout << "<vector - clear>" << std::endl;
	fv5.clear();
	sv5.clear();
	print_vector(fv5, sv5);
	
	std::cout << "<vector - resize>" << std::endl;
	fv2.resize(20, 77);
	sv2.resize(20, 77);
	print_vector(fv2, sv2);
	fv2.resize(10, 22);
	sv2.resize(10, 22);
	print_vector(fv2, sv2);

	std::cout << "<vector - reserve>" << std::endl;
	fv2.reserve(35);
	sv2.reserve(35);
	print_vector(fv2, sv2);

	std::cout << "<vector - insert>" << std::endl;
	fv2.insert(fv2.begin()+2, 100);
	sv2.insert(sv2.begin()+2, 100);
	print_vector(fv2, sv2);
	fv2.insert(fv2.begin()+3, 3, 200);
	sv2.insert(sv2.begin()+3, 3, 200);
	print_vector(fv2, sv2);
	fv2.insert(fv2.begin()+4, fv3.begin(), fv3.begin()+2);
	sv2.insert(sv2.begin()+4, sv3.begin(), sv3.begin()+2);
	print_vector(fv2, sv2);

	std::cout << "<vector - erase>" << std::endl;
	fv2.erase(fv2.begin()+2);
	sv2.erase(sv2.begin()+2);
	print_vector(fv2, sv2);
	fv2.erase(fv2.begin(), fv2.begin()+10);
	sv2.erase(sv2.begin(), sv2.begin()+10);
	print_vector(fv2, sv2);
	
	std::cout << "<vector - swap>" << std::endl;
	print_vector(fv2, sv2);
	print_vector(fv4, sv4);
	sv2.swap(sv4);
	fv2.swap(fv4);
	print_vector(fv2, sv2);
	print_vector(fv4, sv4);

	std::cout << "<vector - deep copy>" << std::endl;
	std::vector<int> sv6;
	ft::vector<int> fv6;
	{
		std::vector<int> sv7(5, 99);
		ft::vector<int> fv7(5, 99);
		sv6 = sv7;
		fv6 = fv7;
	}
	print_vector(fv6, sv6);
//-------------------------------------------------------------------------------
	std::cout << "<map - default constructor>" << std::endl;
	ft::map<int, char> fm;
	std::map<int, char> sm;
	print_map(fm, sm);

	std::cout << "<map - insert>" << std::endl;
	fm.insert(ft::pair<int, char>(1, 'a'));
	sm.insert(std::pair<int, char>(1, 'a'));
	fm.insert(ft::pair<int, char>(2, 'b'));
	sm.insert(std::pair<int, char>(2, 'b'));
	fm.insert(ft::pair<int, char>(8, 'h'));
	sm.insert(std::pair<int, char>(8, 'h'));
	fm.insert(ft::pair<int, char>(4, 'd'));
	sm.insert(std::pair<int, char>(4, 'd'));
	fm.insert(ft::pair<int, char>(16, 'p'));
	sm.insert(std::pair<int, char>(16, 'p'));
	print_map(fm, sm);
	ft::map<int, char> fm2;
	std::map<int, char> sm2;
	fm2.insert(ft::pair<int, char>(20, 'j'));
	sm2.insert(std::pair<int, char>(20, 'j'));
	fm2.insert(ft::pair<int, char>(7, 'g'));
	sm2.insert(std::pair<int, char>(7, 'g'));
	fm2.insert(ft::pair<int, char>(24, 'y'));
	sm2.insert(std::pair<int, char>(24, 'y'));
	fm.insert(fm2.begin(), fm2.end());
	sm.insert(sm2.begin(), sm2.end());
	print_map(fm, sm);

	std::cout << "<map - erase>" << std::endl;
	fm.erase(++fm.begin());
	sm.erase(++sm.begin());
	fm.erase(20);
	sm.erase(20);
	fm.erase(fm.begin(), ++fm.begin());
	sm.erase(sm.begin(), ++sm.begin());
	print_map(fm, sm);

	std::cout << "<map - fill constructor>" << std::endl;
	ft::map<int, char> fm3(fm.begin(), fm.end());
	std::map<int, char> sm3(sm.begin(), sm.end());
	print_map(fm3, sm3);

	std::cout << "<map - copy constructor>" << std::endl;
	ft::map<int, char> fm4(fm);
	std::map<int, char> sm4(sm);
	print_map(fm4, sm4);

	std::cout << "<map - assignment operator>" << std::endl;
	ft::map<int, char> fm5 = fm;
	std::map<int, char> sm5 = sm;
	print_map(fm5, sm5);
	
	std::cout << "<map - clear>" << std::endl;
	fm5.clear();
	sm5.clear();
	print_map(fm5, sm5);

	std::cout << "<map - swap>" << std::endl;
	print_map(fm, sm);
	print_map(fm2, sm2);
	fm.swap(fm2);
	sm.swap(sm2);
	print_map(fm, sm);
	print_map(fm2, sm2);
//-------------------------------------------------------------------------------
	std::cout << "<stack>" << std::endl;
	ft::stack<int> fs;
	std::stack<int> ss;
	for (int i=0; i<10; i++)
	{
		fs.push(i);
		ss.push(i);
	}
	for (int i=0; i<10; i++)
	{
		std::cout << fs.top() << " ";
		fs.pop();
	}
	std::cout << std::endl;
	for (int i=0; i<10; i++)
	{
		std::cout << ss.top() << " ";
		ss.pop();
	}
	std::cout << std::endl << std::endl;

	system("leaks a.out");
	return 0;
}
