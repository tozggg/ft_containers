#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	/* enable_if */
	template <bool Cond, typename T = void>
	struct enable_if { };

	template <typename T>
	struct enable_if<true, T> { typedef T type; };


	/* is_integral */
	struct true_type
	{
		static const bool value = true;
		operator bool() const { return value; }
	};
	struct false_type
	{
		static const bool value = false;
		operator bool() { return value; }
	};

	template<typename T>
	struct is_integral : public false_type {};

	template<>	struct is_integral<bool> : public true_type {};
	template<>	struct is_integral<char> : public true_type {};
	template<>	struct is_integral<wchar_t> : public true_type {};
	template<>	struct is_integral<signed char> : public true_type {};
	template<>	struct is_integral<short> : public true_type {};
	template<>	struct is_integral<int> : public true_type {};
	template<>	struct is_integral<long> : public true_type {};
	template<>	struct is_integral<unsigned char> : public true_type {};
	template<>	struct is_integral<unsigned short> : public true_type {};
	template<>	struct is_integral<unsigned int> : public true_type {};
	template<>	struct is_integral<unsigned long> : public true_type {};


	/* equal */
	template <typename InputIterator1, typename InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}


	/* lexicographical_compare */
	template <typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,\
								InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <typename InputIterator1, typename InputIterator2, typename Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,\
								InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}


	/* pair */
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair() : first(), second() {}
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}
		template<typename U, typename V>
		pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

		pair& operator=(const pair& pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return *this;
		}
	};

	template <typename T1, typename T2>
	bool operator==(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
	{ return p1.first == p2.first && p1.second == p2.second; }

	template <typename T1, typename T2>
	bool operator!=(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
	{ return !(p1 == p2); }

	template <typename T1, typename T2>
	bool operator<(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
	{ return (p1.first < p2.first) || (!(p1.first > p2.first) && p1.second < p2.second); }

	template <typename T1, typename T2>
	bool operator<=(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
	{ return !(p2 < p1); }

	template <typename T1, typename T2>
	bool operator>(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
	{ return p2 < p1; }

	template <typename T1, typename T2>
	bool operator>=(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
	{ return !(p1 < p2); }
	
	
	/* make_pair */
	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{ return (pair<T1, T2>(x, y)); }


	/* less */
	template <typename T>
	struct less
	{
		bool operator()(const T &lhs, const T &rhs) const
		{
			return lhs < rhs;
		}
	};
}

#endif
