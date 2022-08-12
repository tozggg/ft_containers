#ifndef AVLTREE_HPP
# define AVLTREE_HPP

# include <memory>
# include <limits>
# include <algorithm>
# include "utils.hpp"
# include "iterator.hpp"

namespace ft
{
	/* tree node */
	template <typename T>
	struct tree_node
	{
		typedef T			value_type;
		typedef tree_node	node_type;
		typedef tree_node*	node_pointer;

		node_pointer	parent;
		node_pointer	left;
		node_pointer	right;
		value_type		value;
		bool			is_sentinel;

		tree_node() : parent(NULL), left(NULL), right(NULL), value(value_type()), is_sentinel(false) {}
		tree_node(const value_type& v) : parent(NULL), left(NULL), right(NULL), value(v), is_sentinel(false) {}
	};
	

	/* avl tree */
	template <typename T, typename Compare, typename Alloc>
	class tree
	{
	public:
		typedef T														value_type;
		typedef Compare													value_compare;
		typedef tree_node<value_type>									node_type;
		typedef typename node_type::node_pointer						node_pointer;
		typedef typename Alloc::template rebind<node_type>::other		allocator_type;
		typedef	typename ft::tree_iterator<value_type, node_type>       iterator;
		typedef typename ft::tree_iterator<const value_type, node_type> const_iterator;
		typedef std::size_t												size_type;
		typedef std::ptrdiff_t											difference_type;
	
	private:
		value_compare	_comp;
		allocator_type	_alloc;
		node_pointer	_sentinel;
		node_pointer	_root;
		size_type		_size;

	public:
		/* constructor */
		tree(const value_compare& comp, const allocator_type& alloc)
		: _comp(comp), _alloc(alloc), _root(NULL), _size(0)
		{
			_sentinel = _alloc.allocate(1);
			_alloc.construct(_sentinel, node_type());
			_sentinel->is_sentinel = true;
		}

		tree(const tree& other)
		: _comp(other._comp), _alloc(other._alloc), _root(NULL), _size(0)
		{
			_sentinel = _alloc.allocate(1);
			_alloc.construct(_sentinel, node_type());
			insert(other.begin(), other.end());
			_sentinel->is_sentinel = true;
		}

		/* destructor */
		~tree()
		{
			clear();
			_alloc.destroy(_sentinel);
			_alloc.deallocate(_sentinel, 1);
		}

		/* assignment operator */
		tree& operator=(const tree& t)
		{
			if (this != &t)
			{
				clear();
				insert(t.begin(), t.end());
			}
			return *this;
		}

		/* iterators */
		iterator		begin()
		{
			node_pointer node;

			if(_size == 0)
				return iterator(_sentinel);
			node = _root;
			while (node->left)
				node = node->left;
			return iterator(node);
		}

		const_iterator	begin() const
		{
			node_pointer node;

			if(_size == 0)
				return const_iterator(_sentinel);
			node = _root;
			while (node->left)
				node = node->left;
			return const_iterator(node);
		}

		iterator		end() { return iterator(_sentinel); }
		const_iterator	end() const { return const_iterator(_sentinel); }

		/* capacity */
		bool		empty() const { return _size == 0 ? true : false; }
		
		size_type	size() const {return _size;}

		size_type	max_size() const
		{ return std::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type>::max()); }

		/* modifiers */
		ft::pair<iterator, bool> insert(const value_type& val)
		{
			node_pointer node;

			if (_size == 0)
			{
				set_root(val);
				return ft::make_pair(iterator(_root), true);
			}
			iterator it = find(val);
			if (it != end())
				return ft::make_pair(it, false);
			node = insert_node(val);
			insert_rebalance(node->parent);
			return ft::make_pair(iterator(node), true);
		}
		
		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			return insert(val).first;
		}

		template <typename InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; it++)
				insert(*it);
		}

		size_type erase(iterator position)
		{
			node_pointer node;
			node_pointer ancestor;

			if (_size == 0 || position == end())
				return 0;
			for (ancestor = position.base(); ancestor->parent; ancestor = ancestor->parent) {}
			if (ancestor != _sentinel)
				return 0;
			node = position.base();
			if (!node->left && !node->right)
				node = delete_node_leaf(node);
			else if (node->left && node->right)
				node = delete_node_2child(node);
			else
				node = delete_node_1child(node);
			erase_rebalance(node);
			return 1;
		}

		void erase(iterator first, iterator last)
		{	
			for (iterator it = first; it != last;)
				erase(it++);
		}

		void swap(tree& x)
		{
			value_compare	tmp_comp = _comp;
			allocator_type	tmp_alloc = _alloc;
			node_pointer	tmp_sentinel = _sentinel;
			node_pointer	tmp_root = _root;
			size_type		tmp_size = _size;

			_comp = x._comp;
			_alloc = x._alloc;
			_sentinel = x._sentinel;
			_root = x._root;
			_size = x._size;

			x._comp = tmp_comp;
			x._alloc = tmp_alloc;
			x._sentinel = tmp_sentinel;
			x._root = tmp_root;
			x._size = tmp_size;
		}

		void clear()
		{
			if (_size == 0)
				return ;
			destroy(_root);
			_sentinel->left = NULL;
			_sentinel->right = NULL;
			_root = NULL;
			_size = 0;
		}

		/* operations */
		iterator		find(const value_type& val)
		{
			node_pointer node;

			if (_size == 0)
				return end();
			node = _root;
			while (node)
			{
				if (_comp(val, node->value))
					node = node->left;
				else if (_comp(node->value, val))
					node = node->right;
				else
					return iterator(node);
			}
			return end();
		}

		const_iterator	find(const value_type& val) const
		{
			node_pointer node;

			if (_size == 0)
				return end();
			node = _root;
			while (node)
			{
				if (_comp(val, node->value))
					node = node->left;
				else if (_comp(node->value, val))
					node = node->right;
				else
					return const_iterator(node);
			}
			return end();
		}

		 size_type		count(const value_type& val) const
		 {
			 if (find(val) == end())
			 	return 0;
			return 1;
		 }

		iterator		lower_bound(const value_type& val)
		{
			node_pointer res = _sentinel;
			node_pointer node;

			node = _root;
			while (node)
			{
				if (_comp(val, node->value))
				{
					res = node;
					node = node->left;
				}
				else if (_comp(node->value, val))
					node = node->right;
				else
					return iterator(node);
			}
			return iterator(res);
		}

		const_iterator		lower_bound(const value_type& val) const
		{
			node_pointer res = _sentinel;
			node_pointer node;

			node = _root;
			while (node)
			{
				if (_comp(val, node->value))
				{
					res = node;
					node = node->left;
				}
				else if (_comp(node->value, val))
					node = node->right;
				else
					return const_iterator(node);
			}
			return const_iterator(res);
		}

		iterator		upper_bound(const value_type& val)
		{
			node_pointer res = _sentinel;
			node_pointer node;

			node = _root;
			while (node)
			{
				if (_comp(val, node->value))
				{
					res = node;
					node = node->left;
				}
				else
					node = node->right;
			}
			return iterator(res);
		}

		const_iterator		upper_bound(const value_type& val) const
		{
			node_pointer res = _sentinel;
			node_pointer node;

			node = _root;
			while (node)
			{
				if (_comp(val, node->value))
				{
					res = node;
					node = node->left;
				}
				else
					node = node->right;
			}
			return const_iterator(res);
		}

		ft::pair<iterator, iterator> equal_range (const value_type& val)
		{ return ft::make_pair(lower_bound(val), upper_bound(val)); }

		ft::pair<const_iterator, const_iterator> equal_range (const value_type& val) const
		{ return ft::make_pair(lower_bound(val), upper_bound(val)); }

		/* allocator */
		allocator_type get_allocator() const { return _alloc; }

	private:
		/* private memeber function */
		void	set_root(const value_type& val)
		{
			_root = _alloc.allocate(1);
			_alloc.construct(_root, node_type(val));
			_sentinel->left = _root;
			_sentinel->right = _root;
			_root->parent = _sentinel;
			++_size;
		}

		node_pointer insert_node(const value_type& val)
		{
			node_pointer node;
			node_pointer tmp;

			node = _alloc.allocate(1);
			_alloc.construct(node, node_type(val));
			tmp = _root;
			while (tmp)
			{
				if (_comp(val, tmp->value))
				{
					if (tmp->left)
						tmp = tmp->left;
					else
					{
						tmp->left = node;
						break ;
					}
				}
				else if (_comp(tmp->value, val))
				{
					if (tmp->right)
						tmp = tmp->right;
					else
					{
						tmp->right = node;
						break ;
					}
				}
			}
			node->parent = tmp;
			++_size;
			return node;
		}
		
		node_pointer delete_node_leaf(const node_pointer& node)
		{
			node_pointer parent = node->parent;

			if (parent->left == node)
				parent->left = NULL;
			else
				parent->right = NULL;
			
			if (node == _root)
			{
				_root = NULL;
				_sentinel->left = NULL;
				_sentinel->right = NULL;
			}
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			--_size;
			return parent;
		}

		node_pointer delete_node_1child(const node_pointer& node)
		{
			node_pointer parent = node->parent;
			node_pointer child = node->left ? node->left : node->right;

			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
			child->parent = parent;
			
			if (node == _root)
			{
				_root = child;
				_sentinel->left = child;
				_sentinel->right = child;
			}
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			--_size;
			return parent;
		}
		
		node_pointer delete_node_2child(const node_pointer& node)
		{
			node_pointer parent = node->parent;
			node_pointer alter;

			for (alter = node->right; alter->left; alter = alter->left) {}
			
			if (alter != node->right)
			{
				alter->parent->left = alter->right;
				if (alter->right)
					alter->right->parent = alter->parent;
				
				alter->right = node->right;
				node->right->parent = alter;
			}

			if (parent->left == node)
				parent->left = alter;
			else
				parent->right = alter;
			alter->parent = parent;

			alter->left = node->left;
			node->left->parent = alter;
			
			if (node == _root)
			{
				_root = alter;
				_sentinel->left = alter;
				_sentinel->right = alter;
			}
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			--_size;
			return parent;
		}

		int		get_height(node_pointer node)
		{
			int left;
			int right;

			if (!node)
				return -1;
			left = get_height(node->left) + 1;
			right = get_height(node->right) + 1;
			return (left > right ? left : right);
		}

		int		balance_factor(node_pointer node)
		{
			int left;
			int right;

			left = get_height(node->left);
			right = get_height(node->right);
			return (left - right);
		}

		void	rotate_ll(node_pointer node)
		{
			node_pointer parent = node->parent;
			node_pointer left = node->left;
			node_pointer left_right = node->left->right;

			if (parent->right == node)
				parent->right = left;
			else
				parent->left = left;
			left->parent = parent;

			left->right = node;
			node->parent = left;

			node->left = left_right;
			if (left_right)
				left_right->parent = node;

			if (node == _root)
			{
				_root = left;
				_sentinel->left = left;
				_sentinel->right = left;
			}
		}

		void	rotate_rr(node_pointer node)
		{
			node_pointer parent = node->parent;
			node_pointer right = node->right;
			node_pointer right_left = node->right->left;

			if (parent->right == node)
				parent->right = right;
			else
				parent->left = right;
			right->parent = parent;

			right->left = node;
			node->parent = right;

			node->right = right_left;
			if (right_left)
				right_left->parent = node;

			if (node == _root)
			{
				_root = right;
				_sentinel->left = right;
				_sentinel->right = right;
			}
		}

		void	insert_rebalance(node_pointer node)
		{
			int bf;

			while (node != _sentinel)
			{
				bf = balance_factor(node);
				if (bf > 1)
				{
					if (balance_factor(node->left) < 0)
						rotate_rr(node->left);
					rotate_ll(node);
					break ;
				}
				if (bf < -1)
				{
					if (balance_factor(node->right) > 0)
						rotate_ll(node->right);
					rotate_rr(node);
					break ;
				}
				node = node->parent;
			}
		}

		void	erase_rebalance(node_pointer node)
		{
			int bf;

			while (node != _sentinel)
			{
				bf = balance_factor(node);
				if (bf > 1)
				{
					if (balance_factor(node->left) < 0)
						rotate_rr(node->left);
					rotate_ll(node);
				}
				if (bf < -1)
				{
					if (balance_factor(node->right) > 0)
						rotate_ll(node->right);
					rotate_rr(node);
				}
				node = node->parent;
			}
		}

		void	destroy(node_pointer node)
		{
			if (!node)
				return ;
			destroy(node->left);
			destroy(node->right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}
	};
}

#endif
