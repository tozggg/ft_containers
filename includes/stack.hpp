#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <typename T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container							container_type;
			typedef typename container_type::value_type	value_type;
			typedef typename container_type::size_type	size_type;
	
		protected:
			container_type	_c;
		
		public:
			/* constructor */
			explicit stack(const container_type& ctnr = container_type()) : _c(ctnr) {}
			stack(const stack& other) : _c(other._c) {}

			/* destructor */
			~stack(void) {}

			/* assignment operator */
			stack& operator=(const stack& rhs)
			{
				_c = rhs.c;
				return *this;
			}
			
			/* member functions */
			bool				empty() const { return _c.empty(); }
			size_type			size() const { return _c.size(); }
			value_type&			top() { return _c.back(); }
			const value_type&	top() const { return _c.back(); }
			void				push (const value_type& val) { _c.push_back(val); }
			void				pop() { _c.pop_back(); }

			/* relational operators */
			friend bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{ return lhs._c == rhs._c; }

			friend bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{ return lhs._c != rhs._c; }

			friend bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{ return lhs._c < rhs._c; }

			friend bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{ return lhs._c <= rhs._c; }

			friend bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{ return lhs._c > rhs._c; }

			friend bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{ return lhs._c >= rhs._c; }
	};
}

#endif
