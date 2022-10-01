#ifndef FT_UTILS_HPP
#define FT_UTILS_HPP

#include "iterator.hpp"

namespace ft {
	template<class T>
	void swap(T &a, T &b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

	template<class InputIteratorA, class InputIteratorB>
	bool equal(InputIteratorA first1, InputIteratorA last1, InputIteratorB first2) {
		while (first1 != last1) {
			if (*first1 != *first2) {
				return false;
			}
			first1++;
			first2++;
		}
		return true;
	}

	template<class InputIteratorA, class InputIteratorB>
	bool lexicographical_compare(InputIteratorA first1, InputIteratorA last1,
								 InputIteratorB first2, InputIteratorB last2) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				return true;
			}
			if (*first2 < *first1) {
				return false;
			}
			first1++;
			first2++;
		}
		return first1 == last1 && first2 != last2;
	}

	namespace detail {
		template<class Iterator>
		typename ft::iterator_traits<Iterator>::difference_type
		do_distance(Iterator first, Iterator last, std::input_iterator_tag) {
			typename std::iterator_traits<Iterator>::difference_type result = 0;
			while (first != last) {
				++first;
				++result;
			}
			return result;
		}

		template<class Iterator>
		typename ft::iterator_traits<Iterator>::difference_type
		do_distance(Iterator first, Iterator last, std::random_access_iterator_tag) {
			return last - first;
		}
	}

	template<class Iterator>
	typename ft::iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last) {
		return detail::do_distance(first, last,
								   typename ft::iterator_traits<Iterator>::iterator_category());
	}
}

#endif
