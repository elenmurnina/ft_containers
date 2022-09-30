#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterators_traits.hpp"

namespace ft {

	template <class Iterator>
	class reverse_iterator {
	public:
		typedef Iterator    											iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

		reverse_iterator(): _elem() {
		}

		explicit reverse_iterator (iterator_type it): _elem(it) {
		}

		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter> &rev_it): _elem(rev_it.base()) {
		}

		virtual ~reverse_iterator() {
		}

		iterator_type base() const {
			return _elem;
		}

		reference operator * () const {
			iterator_type result = _elem;
			result--;
			return *result;
		}

		reverse_iterator operator + (difference_type n) const {
			return reverse_iterator(_elem - n);
		}

		reverse_iterator &operator ++ () {
			_elem--;
			return *this;
		}

		reverse_iterator operator ++ (int) {
			reverse_iterator result = *this;
			(*this)++;
			return result;
		}

		reverse_iterator &operator += (difference_type n) {
			_elem -= n;
			return *this;
		}

		reverse_iterator operator - (difference_type n) const {
			return reverse_iterator(_elem + n);
		}

		reverse_iterator &operator -- () {
			_elem++;
			return *this;
		}

		reverse_iterator operator -- (int) {
			reverse_iterator result = *this;
			(*this)--;
			return result;
		}

		reverse_iterator &operator -= (difference_type n) {
			_elem += n;
			return *this;
		}

		pointer operator -> () const {
			return &(operator*());
		}

		reference operator [] (difference_type n) const {
			return this->base()[-n - 1];
		}

	private:
		iterator_type _elem;
	};

	template <class Iterator>
	bool operator == (const reverse_iterator<Iterator> &a,
					  const reverse_iterator<Iterator> &b) {
		return a.base() == b.base();
	}

	template <class Iterator_L, class Iterator_R>
	bool operator == (const reverse_iterator<Iterator_L> &a,
					  const reverse_iterator<Iterator_R> &b) {
		return a.base() == b.base();
	}

	template <class Iterator>
	bool operator != (const reverse_iterator<Iterator> &a,
					  const reverse_iterator<Iterator> &b) {
		return a.base() != b.base();
	}

	template <class Iterator_A, class Iterator_B>
	bool operator != (const reverse_iterator<Iterator_A> &a,
					  const reverse_iterator<Iterator_B> &b) {
		return a.base() != b.base();
	}

	template <class Iterator>
	bool operator < (const reverse_iterator<Iterator> &a,
					 const reverse_iterator<Iterator> &b) {
		return a.base() > b.base();
	}

	template <class Iterator_A, class Iterator_B>
	bool operator < (const reverse_iterator<Iterator_A> &a,
					 const reverse_iterator<Iterator_B> &b) {
		return a.base() > b.base();
	}

	template <class Iterator>
	bool operator <= (const reverse_iterator<Iterator> &a,
					  const reverse_iterator<Iterator> &b) {
		return a.base() >= b.base();
	}

	template <class Iterator_A, class Iterator_B>
	bool operator <= (const reverse_iterator<Iterator_A> &a,
					  const reverse_iterator<Iterator_B> &b) {
		return a.base() >= b.base();
	}

	template <class Iterator>
	bool operator > (const reverse_iterator<Iterator> &a,
					 const reverse_iterator<Iterator> &b) {
		return a.base() < b.bash();
	}

	template <class Iterator_A, class Iterator_B>
	bool operator > (const reverse_iterator<Iterator_A> &a,
					 const reverse_iterator<Iterator_B> &b) {
		return a.base() < b.base();
	}

	template <class Iterator>
	bool operator >= (const reverse_iterator<Iterator> &a,
					  const reverse_iterator<Iterator> &b) {
		return a.base() <= b.base();
	}

	template <class Iterator_A, class Iterator_B>
	bool operator >= (const reverse_iterator<Iterator_A> &a,
					  const reverse_iterator<Iterator_B> &b) {
		return a.base() <= b.base();
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator + (typename reverse_iterator<Iterator>::difference_type n,
										   const reverse_iterator<Iterator> &rev_it) {
		return rev_it + n;
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator - (const reverse_iterator<Iterator> &a,
																	 const reverse_iterator<Iterator> &b) {
		return a.base() - b.base();
	}

	template <class Iterator_A, class Iterator_B>
	bool operator - (const reverse_iterator<Iterator_A> &a,
					 const reverse_iterator<Iterator_B> &b) {
		return a.base() - b.base();
	}
}

#endif