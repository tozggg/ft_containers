#include <ctime>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include "../includes/map.hpp"
#include "../includes/stack.hpp"
#include "../includes/vector.hpp"

class Timer {
 private:
  std::clock_t __start;

 public:
  Timer(void);
  Timer(const Timer& t);
  ~Timer(void);
  Timer& operator=(const Timer& t);

  void start(void);
  std::clock_t stop(void);
};

template <class Map>
std::clock_t map_insert_growing(std::size_t times, Map map) {
  Timer t;
  t.start();
  /* insert & find test */
  for (std::size_t i = 0 ; i < times ; i++) {
    map[i] = true;
    map.find(i);
  }  
  /* copy constructor & destructor test */
  {
    Map tmp(map);
  }
  return t.stop();
}


template <class Stack>
std::clock_t stack_insert_growing(std::size_t times, Stack stack) {
  Timer t;
  t.start();
  /* insert test */
  for (std::size_t i =  0 ; i < times ; i++) {
    stack.push(i);
  }
  /* copy constructor & destructor test */
  {
    Stack tmp(stack);
  }
  /* find & erase test */
  for (std::size_t i = 0 ; i < times ; i++) {
    (void)stack.top();
    stack.pop();
  }
  return t.stop();
}

template <class Vector>
std::clock_t vector_insert_growing(std::size_t times, Vector vector) {
  Timer t;
  t.start();
  /* insert & find test */
  for (std::size_t i = 0 ; i < times ; i++) {
    vector.push_back(i);
    (void)vector[i];
  }
  /* copy constructor & destructor test */
  {
    Vector tmp(vector);
  }
  /* erase test */
  vector.erase(vector.begin(), vector.end());
  return t.stop();
}

void benchmark_map(void);
void benchmark_set(void);
void benchmark_stack(void);
void benchmark_vector(void);

Timer::Timer(void) : __start(0) {}
Timer::Timer(const Timer& t) : __start(t.__start) {}
Timer::~Timer(void) {}
Timer& Timer::operator=(const Timer& t) {
  if (this != &t) {
    __start = t.__start;
  }
  return *this;
}
void Timer::start(void) {
  __start = std::clock();
}
std::clock_t Timer::stop(void) {
  return std::clock() - __start;
}

void benchmark_map(void) {
  std::cout << "\033[1;34m--- MAP BENCHMARK ⚡ ---\033[0m" << std::endl;
  std::clock_t std;
  std::clock_t ft;
  std::map<int, bool> std_map;
  ft::map<int, bool> ft_map;
  std = map_insert_growing(200000, std_map);
  std::cout << "std: " << std << std::endl;
  ft = map_insert_growing(200000, ft_map);
  std::cout << "ft: " << ft << std::endl;
  if (static_cast<double>(ft) / static_cast<double>(std) < 1.0000) {
  std::cout << "our map is " << static_cast<double>(std) / static_cast<double>(ft) << " times faster. ";
  } else {
    std::cout << "our map is " << static_cast<double>(ft) / static_cast<double>(std) << " times slower. ";
  }
  if (static_cast<double>(ft) / static_cast<double>(std) < 20.0000) {
    std::cout << "\033[1;32m[PASS]\033[0m" << std::endl;
  } else {
    std::cout << "\033[1;31m[FAIL]\033[0m" << std::endl;
  }
  std::cout << std::endl;
}

void benchmark_stack(void) {
  std::cout << "\033[1;34m--- STACK BENCHMARK ⚡ ---\033[0m" << std::endl;
  std::clock_t std;
  std::clock_t ft;
  std::stack<int> std_stack;
  ft::stack<int> ft_stack;
  std = stack_insert_growing(200000, std_stack);
  std::cout << "std: " << std << std::endl;
  ft = stack_insert_growing(200000, ft_stack);
  std::cout << "ft: " << ft << std::endl;
  if (static_cast<double>(ft) / static_cast<double>(std) < 1.0000) {
  std::cout << "our stack is " << static_cast<double>(std) / static_cast<double>(ft) << " times faster. ";
  } else {
    std::cout << "our stack is " << static_cast<double>(ft) / static_cast<double>(std) << " times slower. ";
  }
  if (static_cast<double>(ft) / static_cast<double>(std) < 20.0000) {
    std::cout << "\033[1;32m[PASS]\033[0m" << std::endl;
  } else {
    std::cout << "\033[1;31m[FAIL]\033[0m" << std::endl;
  }
  std::cout << std::endl;
}

void benchmark_vector(void) {
  std::cout << "\033[1;34m--- VECTOR BENCHMARK ⚡ ---\033[0m" << std::endl;
  std::clock_t std;
  std::clock_t ft;
  std::vector<int> std_vector;
  ft::vector<int> ft_vector;
  std = vector_insert_growing(200000, std_vector);
  std::cout << "std: " << std << std::endl;
  ft = vector_insert_growing(200000, ft_vector);
  std::cout << "ft: " << ft << std::endl;
  if (static_cast<double>(ft) / static_cast<double>(std) < 1.0000) {
  std::cout << "our vector is " << static_cast<double>(std) / static_cast<double>(ft) << " times faster. ";
  } else {
    std::cout << "our vector is " << static_cast<double>(ft) / static_cast<double>(std) << " times slower. ";
  }
  if (static_cast<double>(ft) / static_cast<double>(std) < 20.0000) {
    std::cout << "\033[1;32m[PASS]\033[0m" << std::endl;
  } else {
    std::cout << "\033[1;31m[FAIL]\033[0m" << std::endl;
  }
  std::cout << std::endl;
}

int main(void) {
  std::cout << "\033[1;94m" <<
    "# ****************************************************************************** #\n"
    "#                                                                                #\n"
    "#                              containers bench test                             #\n"
    "#                                                                                #\n"
    "# ****************************************************************************** #\n"
            << "\033[0m" << std::endl;
  benchmark_map();
  benchmark_stack();
  benchmark_vector();
  return 0;
}
