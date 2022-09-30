#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

	template <class T1, class T2>
	struct pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair(): first(), second() {
		}

		template<class A, class B>
		pair(const pair<A, B> &p): first(p.first), second(p.second) {
		}

		pair(const first_type &a, const second_type &b): first(a), second(b) {
		}

		pair &operator = (const pair &other) {
			if (*this == other) {
				return *this;
			}
			this->first = other.first;
			this->second = other.second;
			return *this;
		}
	};

	template <class T1, class T2>
	bool operator == (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return a.first == b.first && a.second == b.second;
	}

	template <class T1, class T2>
	bool operator != (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return !(a == b);
	}

	template <class T1, class T2>
	bool operator < (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return (a.first < b.first || (!(b.first < a.first) && a.second < b.second));
	}

	template <class T1, class T2>
	bool operator <= (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return !(b < a);
	}

	template <class T1, class T2>
	bool operator > (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return b < a;
	}

	template <class T1, class T2>
	bool operator >= (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return !(a < b);
	}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 a, T2 b) {
		return (pair<T1, T2>(a, b));
	}
}

#endif