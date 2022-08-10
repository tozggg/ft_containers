
#include <vector>
#include <stack>
#include <map>
#include "../includes/vector.hpp"
#include "../includes/stack.hpp"

#include <iostream>

int main(void)
{
	typedef std::map<int, int>::iterator iter_type;
	std::map<int, int> m;
	std::map<int, int> k;

	std::pair<iter_type, bool> test = m.insert(std::pair<int ,int>(3, 8));

	size_t st = k.erase(2);


	std::cout << st << std::endl;

	
	
	return 0;
}
