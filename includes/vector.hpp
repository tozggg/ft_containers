#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <algorithm>
# include <stdexcept>
# include "utils.hpp"
# include "iterator.hpp"

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T                                            	value_type;
		typedef Alloc                                        	allocator_type;
		typedef typename allocator_type::reference           	reference;
		typedef typename allocator_type::const_reference     	const_reference;
		typedef typename allocator_type::pointer             	pointer;
		typedef typename allocator_type::const_pointer       	const_pointer;
		typedef ft::vector_iterator<value_type>              	iterator;
		typedef ft::vector_iterator<const value_type>        	const_iterator;
		typedef typename ft::reverse_iterator<iterator>      	reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t									difference_type;
		typedef std::size_t                              		size_type;

	private:
		allocator_type    _alloc;
		pointer           _ptr;
		size_type         _size;
		size_type         _capacity;
	
	public:
		/* constructor */
		explicit vector(const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _ptr(NULL), _size(0), _capacity(0) {}
		
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _ptr(NULL), _size(n), _capacity(n)
		{
			_ptr = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_ptr + i, val);
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),\
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		: _alloc(alloc), _ptr(NULL), _size(0)
		{
			size_type n = std::distance(first, last);
			_size = n;
			_capacity = n;
			_ptr = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_ptr + i, *(first++));
		}

		vector(const vector& other)
		: _alloc(other._alloc), _ptr(NULL)
		{
			_ptr = _alloc.allocate(other._capacity);
			_size = other._size;
			_capacity = other._capacity;
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_ptr + i, other._ptr[i]);
		}

		/* destructor */
		~vector()
		{
			clear();
			if (_ptr)
				_alloc.deallocate(_ptr, _capacity);
		}

		/* assignment operator */
		vector& operator=(const vector& v)
		{
			if (this != &v)
				assign(v.begin(), v.end());
			return *this;
		}

		/* iterators */
		iterator 				begin() { return iterator(_ptr); }
		const_iterator			begin() const { return const_iterator(_ptr); }
		iterator				end() { return iterator(_ptr + _size); }
		const_iterator			end() const { return const_iterator(_ptr + _size); }
		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

		/* capacity */
		size_type	size() const { return _size; }

		size_type	max_size() const
		{ return std::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type>::max()); }

		void		resize(size_type n, value_type val = value_type())
		{
			if (n > _capacity)
				reserve( (n > _capacity * 2) ? n : _capacity * 2 );
			if (n >= _size)
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(_ptr + i, val);
			}
			else
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(_ptr + i);
			}
			_size = n;
		}
		
		size_type	capacity() const { return _capacity; }
		
		bool		empty() const { return _size == 0 ? true : false; }
		
		void		reserve(size_type n)
		{
			if (n > max_size())
				throw (std::length_error("allocate size too big"));
			if (n > _capacity)
			{
				pointer new_ptr = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(new_ptr + i, *(_ptr + i));
				_alloc.deallocate(_ptr, _capacity);
				_ptr = new_ptr;
				_capacity = n;
			}
		}

		/* element access */
		reference		operator[](size_type n) { return _ptr[n]; }
		const_reference	operator[](size_type n) const { return _ptr[n]; }

		reference		at(size_type n)
		{
			if (n >= size()) 
				throw (std::out_of_range("index out of range"));
			return _ptr[n];
		}
		const_reference	at(size_type n) const
		{
			if (n >= size())
				throw (std::out_of_range("index out of range"));
			return _ptr[n];
		}

		reference		front() { return *begin(); }
		const_reference front() const { return *begin(); }
		reference		back() { return *(end() - 1); }
		const_reference	back() const { return *(end() - 1); }

		/* modifiers */
		template <typename InputIterator>
		void	assign(InputIterator first, InputIterator last,\
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			clear();
			size_type n = std::distance(first, last);
			if (n > _capacity)
				reserve(n);
			for (InputIterator it = first; it != last; it++)
				push_back(*it);
		}

		void	assign(size_type n, const value_type& val)
		{
			clear();
			if (n > _capacity) 
				reserve(n);
			for (size_type i = 0; i < n; i++)
				push_back(val);
		}

		void	push_back(const value_type& val)
		{
			if (_size == _capacity)
				reserve( empty() ? 1 : _capacity * 2 );
			_alloc.construct(_ptr + _size, val);
			++_size;
		}

		void	pop_back()
		{
			if (_size > 0)
				_alloc.destroy(_ptr + (_size - 1));
			--_size;
		}

		iterator	insert(iterator position, const value_type& val)
		{
			size_type idx = position - begin();
			if (_size == _capacity)
				reserve( empty() ? 1 : _capacity * 2 );
			size_type j = _size;
			while (j != idx)
			{
				--j;
				_alloc.construct(&(*(_ptr + j + 1)), *(_ptr + j));
			}
  			_alloc.construct(&(*(_ptr + idx)), val);
  			++_size;
  			return (iterator(_ptr + idx));
		}
		
		iterator	insert(iterator position, size_type n, const value_type& val)
		{
			size_type idx = position - begin();
			if (_size + n > _capacity)
				reserve( (_size + n > _capacity * 2) ? _size + n : _capacity * 2 );
			size_type j = _size;
			while (j != idx)
			{
				--j;
				_alloc.construct(&(*(_ptr + j + n)), *(_ptr + j));
			}
			for (size_type i = 0; i < n; i++)
   				_alloc.construct(&(*(_ptr + idx + i)), val);
  			_size += n;
  			return (iterator(_ptr + idx));
		}

		template <typename InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last,\
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			size_type idx = position - begin();
			size_type n = std::distance(first, last);
			if (_size + n > _capacity)
				reserve( (_size + n > _capacity * 2) ? _size + n : _capacity * 2 );
			size_type j = _size;
			while (j != idx)
			{
				--j;
				_alloc.construct(&(*(_ptr + j + n)), *(_ptr + j));
			}
			for (size_type i = n; i > 0; i--)
				_alloc.construct(&(*(_ptr + idx + (i - 1))), *(--last));
			_size += n;
		}

		iterator erase(iterator position)
		{
			iterator it = begin();
			while (it != position)
				++it;
			_alloc.destroy(&(*it));
			while (it + 1 != end())
			{
				_alloc.construct(&(*it), *(it + 1));
				++it;
			}
			pop_back();
			return position;
		}

		iterator erase(iterator first, iterator last)
		{
			iterator position = first;
			size_type n = std::distance(first, last);
			iterator it = begin();
			while (it != first)
				++it;
			for (; first != last; first++)
				_alloc.destroy(&(*first));
			while (it + n != end())
			{
				_alloc.construct(&(*it), *(it + n));
				++it;
			}
			for (size_type i = 0; i < n; i++)
				pop_back();
			return position;
		}

		void swap (vector& x)
		{
			allocator_type    tmp_alloc = _alloc;
			pointer           tmp_ptr = _ptr;
			size_type         tmp_size = _size;
			size_type         tmp_capacity = _capacity;

			_alloc = x._alloc;
			_ptr = x._ptr;
			_capacity = x._capacity;
			_size = x._size;

			x._alloc = tmp_alloc;
			x._ptr = tmp_ptr;
			x._capacity = tmp_capacity;
			x._size = tmp_size;
		}

		void clear()
		{
			for (iterator it = begin(); it != end(); it++)
				_alloc.destroy(&(*it));
			_size = 0;
		}

		/* allocator */
		allocator_type	get_allocator() const { return _alloc; }
	};	

	/* relational operators */
	template <typename T, typename Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template <typename T, typename Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <typename T, typename Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	
	template <typename T, typename Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return !(rhs < lhs); }

	template <typename T, typename Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return rhs < lhs; }

	template <typename T, typename Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return !(lhs < rhs); }

	/* swap */
	template <typename T, typename Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{ x.swap(y); }
}

#endif
