#ifndef MAP_HPP_
# define MAP_HPP_

# include "avltree.hpp"

namespace ft
{
	template <typename Key, typename T, typename Compare = ft::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;

		class	value_compare
		{
			friend class map;
		protected:
			key_compare comp;
			value_compare (key_compare c) : comp(c) {}
		public:
			bool operator() (const value_type& x, const value_type& y) const
			{ return (comp(x.first, y.first)); }
		};

		typedef Alloc															allocator_type;
		typedef typename allocator_type::reference								reference;
		typedef typename allocator_type::const_reference						const_reference;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::const_pointer							const_pointer;
		typedef typename ft::tree<value_type, value_compare, allocator_type>	tree_type;
		typedef typename tree_type::iterator									iterator;
		typedef typename tree_type::const_iterator								const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef std::size_t														size_type;
		typedef std::ptrdiff_t													difference_type;

	private:
		key_compare		_key_comp;
		value_compare	_value_comp;
		allocator_type	_alloc;
		tree_type		_tree;
	
	public:
		/* constructor */
		map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _key_comp(comp), _value_comp(comp), _alloc(alloc), _tree(_value_comp, _alloc) {}

		template <typename InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
      	: _key_comp(comp), _value_comp(comp), _alloc(alloc), _tree(_value_comp, _alloc)
		{ insert(first, last); }

		map(const map& other)
		: _key_comp(other._key_comp), _value_comp(other._value_comp), _alloc(other._alloc), _tree(other._tree) {}

		/* destructor */
		~map() {}

		/* assignment operator */
		map& operator=(const map& m)
		{
			if (this != &m)
				_tree = m._tree;
			return *this;
		}

		/* iterators */
		iterator				begin() { return _tree.begin(); }
		const_iterator			begin() const { return (_tree.begin()); }
		iterator				end() { return _tree.end(); }
		const_iterator			end() const { return _tree.end(); }
		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

		/* capacity */
		bool		empty() const { return _tree.empty(); }
		size_type	size() const { return _tree.size(); }
		size_type	max_size() const { return _tree.max_size(); }
	
		/* element access */
		mapped_type& operator[] (const key_type& k)
		{
			ft::pair<iterator, bool> p = insert(ft::make_pair(k, mapped_type()));
			return p.first->second;
		}

		/* modifiers */
		ft::pair<iterator, bool>	insert(const value_type& val) { return _tree.insert(val); }
		iterator					insert(iterator position, const value_type& val) { return _tree.insert(position, val); }
		template <typename InputIterator>
		void						insert(InputIterator first, InputIterator last) { _tree.insert(first, last); }

		void		erase(iterator position) { _tree.erase(position); }
		size_type	erase(const key_type& k) { return _tree.erase(find(k)); }
		void		erase(iterator first, iterator last) { _tree.erase(first, last); }

		void	swap(map& x) { _tree.swap(x._tree); }
		void	clear() { _tree.clear(); }

		/* observers */
		key_compare		key_comp() const { return _key_comp; }
		value_compare	value_comp() const { return _value_comp; }

		/* operations */
		iterator		find(const key_type& k) { return _tree.find(ft::make_pair(k, mapped_type())); }
		const_iterator	find(const key_type& k) const { return _tree.find(ft::make_pair(k, mapped_type())); }

		size_type		count (const key_type& k) const { return _tree.count(ft::make_pair(k, mapped_type())); }
		
		iterator		lower_bound (const key_type& k) { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }
		const_iterator	lower_bound (const key_type& k) const { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }
		
		iterator		upper_bound (const key_type& k) { return iterator(_tree.upper_bound(ft::make_pair(k, mapped_type()))); }
		const_iterator	upper_bound (const key_type& k) const { return (_tree.upper_bound(ft::make_pair(k, mapped_type()))); }
		
		ft::pair<iterator, iterator> equal_range (const key_type& k) { return _tree.equal_range(ft::make_pair(k, mapped_type())); }
		ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const { return _tree.equal_range(ft::make_pair(k, mapped_type())); }

		/* allocator */
		allocator_type get_allocator() const { return _tree.get_allocator(); }
	};

	/* relational operators */
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return !(rhs < lhs); }
	
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return rhs < lhs; }

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs < rhs); }

	/* swap */
	template <typename Key, typename T, typename Compare, typename Alloc>
	void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
	{ lhs.swap(rhs); }
}

#endif
