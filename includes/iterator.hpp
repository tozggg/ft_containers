#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
	/* iterator_traits */
	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type  	difference_type;
		typedef typename Iterator::value_type       	value_type;
		typedef typename Iterator::pointer          	pointer;
		typedef typename Iterator::reference        	reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t                  	difference_type;
		typedef T                               	value_type;
		typedef T*                              	pointer;
		typedef T&                              	reference;
		typedef std::random_access_iterator_tag 	iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t                  	difference_type;
		typedef T                               	value_type;
		typedef const T*                        	pointer;
		typedef const T&                        	reference;
		typedef std::random_access_iterator_tag 	iterator_category;
	};


	/* reverse_iterator */
	template <typename Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator                                                iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
		typedef typename iterator_traits<Iterator>::value_type          value_type;
		typedef typename iterator_traits<Iterator>::difference_type     difference_type;
		typedef typename iterator_traits<Iterator>::pointer             pointer;
		typedef typename iterator_traits<Iterator>::reference           reference;
	
	private:
		iterator_type _base;
	
	public:
		reverse_iterator() : _base() {}
		reverse_iterator(iterator_type it) : _base(it) {}
		template <typename Iter>
		reverse_iterator(const reverse_iterator<Iter>& other) : _base(other.base()) {}

		reverse_iterator operator=(const reverse_iterator& rhs)
		{
			_base = rhs._base;
			return *this;
		}

		iterator_type base() const { return _base; }

		reference			operator*() const { iterator_type tmp(_base); return *(--tmp); }
		pointer				operator->() const { return &(operator*()); }
		reference			operator[](difference_type n) const { return *(_base - 1 - n); }
		reverse_iterator&	operator++() { --_base; return *this; }
		reverse_iterator	operator++(int) { reverse_iterator tmp(*this); --_base; return tmp; }
		reverse_iterator&	operator--() { ++_base; return *this; }
		reverse_iterator	operator--(int) { reverse_iterator tmp(*this); ++_base; return tmp; }
		reverse_iterator	operator+(difference_type n) const { return reverse_iterator(_base - n); }
		reverse_iterator&	operator+=(difference_type n) { _base -= n; return *this; }
		reverse_iterator	operator-(difference_type n) const { return reverse_iterator(_base + n); }
		reverse_iterator&	operator-=(difference_type n) { _base += n; return *this; }
	};

	template <class IterL, class IterR>
	bool operator==(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <class IterL, class IterR>
	bool operator!=(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
	{ return lhs.base() != rhs.base(); }

	template <class IterL, class IterR>
	bool operator<(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
	{ return lhs.base() > rhs.base(); }

	template <class IterL, class IterR>
	bool operator<=(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template <class IterL, class IterR>
	bool operator>(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <class IterL, class IterR>
	bool operator>=(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rhs)
	{ return rhs + n; }

	template <class IterL, class IterR>
	typename reverse_iterator<IterL>::difference_type operator-(const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
	{ return rhs.base() - lhs.base(); }

	/* vector_iterator */
	// =random access iterator
	template <typename T>
	class vector_iterator
	{
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;

	private:
		pointer _ptr;

	public:
		vector_iterator() : _ptr(NULL) {}
		vector_iterator(pointer p) : _ptr(p) {}
		~vector_iterator() {}
		vector_iterator(const vector_iterator &other) : _ptr(other._ptr) {}

		vector_iterator &operator=(const vector_iterator &rhs)
		{
			_ptr = rhs._ptr;
			return *this;
		}

		operator vector_iterator<const value_type>() const
		{ return vector_iterator<const value_type>(_ptr); }

		pointer base(void) const { return _ptr; }

		reference			operator*() const { return *_ptr; }
		pointer				operator->() const { return &(operator*()); }
		reference			operator[](difference_type n) const { return _ptr[n]; }
		vector_iterator&	operator++() { ++_ptr; return *this; }
		vector_iterator		operator++(int) { vector_iterator tmp(*this); ++_ptr; return tmp; }
		vector_iterator&	operator--() { --_ptr; return *this; }
		vector_iterator		operator--(int) { vector_iterator tmp(*this); --_ptr; return tmp; }
		vector_iterator		operator+(difference_type n) const { return _ptr + n; }
		vector_iterator&	operator+=(difference_type n) { _ptr += n; return *this; }
		vector_iterator		operator-(difference_type n) const { return _ptr - n; }
		vector_iterator&	operator-=(difference_type n) { _ptr -= n; return *this; }
	};

	template <class IterL, class IterR>
	bool operator==(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <class IterL, class IterR>
	bool operator!=(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs)
	{ return lhs.base() != rhs.base(); }

	template <class IterL, class IterR>
	bool operator<(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <class IterL, class IterR>
	bool operator<=(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template <class IterL, class IterR>
	bool operator>(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs)
	{ return lhs.base() > rhs.base(); }

	template <class IterL, class IterR>
	bool operator>=(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template <class Iter>
	vector_iterator<Iter> operator+(typename vector_iterator<Iter>::difference_type n, const vector_iterator<Iter>& rhs)
	{ return rhs + n; }

	template <class IterL, class IterR>
	typename vector_iterator<IterL>::difference_type operator-(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs)
	{ return lhs.base() - rhs.base(); }


	/* tree_iterator */
	// =bidirectional iterator
	template <typename T, typename NodeType>
	class tree_iterator
	{
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ptrdiff_t						difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;

		typedef NodeType						node_type;
		typedef NodeType*						node_pointer;
	
	private:
		node_pointer _ptr;
	
	public:
		tree_iterator() : _ptr(NULL) {}
		tree_iterator(node_pointer p) : _ptr(p) {}
		~tree_iterator() {}
		tree_iterator(const tree_iterator& other) : _ptr(other._ptr) {}

		tree_iterator &operator=(const tree_iterator &rhs)
		{
			_ptr = rhs._ptr;
			return *this;
		}

		operator tree_iterator<const value_type, node_type>() const
		{ return tree_iterator<const value_type, node_type>(_ptr); }

		node_pointer base(void) const { return _ptr; }

		reference		operator*() const {return _ptr->value;}
		pointer			operator->() const {return &(this->operator*());}
		tree_iterator&	operator++() { _ptr = get_next_node(_ptr); return *this; }
		tree_iterator	operator++(int) { tree_iterator tmp(*this); ++(*this); return tmp; }
		tree_iterator&	operator--() { _ptr = get_prev_node(_ptr); return *this; }
		tree_iterator	operator--(int) { tree_iterator tmp(*this); --(*this); return tmp; }
	
	private:
		node_pointer get_next_node(node_pointer node)
		{
			if (!node->parent)
				return node;
			if (node->right)
			{
				node = node->right;
				while (node->left)
					node = node->left;
			}
			else
			{
				node_pointer tmp;
				do
				{
					tmp = node;
					node = node->parent;
				}
				while (node && node->left != tmp);
			}
			return node;
		}

		node_pointer get_prev_node(node_pointer node)
		{
			if (!node->parent)
			{
				while (node->right)
					node = node->right;
				return node;
			}
			if (node->left)
			{
				node = node->left;
				while (node->right)
					node = node->right;
			}
			else
			{
				node_pointer tmp;
				do
				{
					tmp = node;
					node = node->parent;
				}
				while (node && node->right != tmp);
			}
			return node;
		}

		friend bool operator==(const tree_iterator& lhs, const tree_iterator& rhs)
		{ return lhs._ptr == rhs._ptr; }
		friend bool operator!=(const tree_iterator& lhs, const tree_iterator& rhs)
		{ return lhs._ptr != rhs._ptr; }
	};
}

#endif
