
#include <vector>
#include <stack>
#include "../includes/vector.hpp"
#include "../includes/stack.hpp"

#include <iostream>

int main(void)
{
	ft::stack<int> s;
	ft::vector<int> v;

//	for (int i = 0; i <=10; i++)
//		v.push_back(i);

	ft::vector<int> k;
	for (int i = 1; i <=4; i++)
		k.push_back(i * 100);


	typedef ft::vector_iterator<int> iter_type;
	iter_type it = v.begin() + 2;

//	v.insert(it, 3, 77);	
	v.insert(v.end(), 42);
//	v.insert(v.begin(), 2, 21);

	for (iter_type i = v.begin(); i != v.end(); i++)
	{
		std::cout << *i << std::endl;
	}

	
	
	return 0;
}
