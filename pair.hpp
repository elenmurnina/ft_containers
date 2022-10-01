#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		T1	first;
		T2	second;

		pair(): first(), second() {
		}

		pair(const T1 &a, const T2 &b): first(a), second(b) {
		}

		template<class U1, class U2>
		pair(const pair<U1, U2> &pair): first(pair.first), second(pair.second) {
		}
	};

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 a, T2 b) {
		return pair<T1, T2>(a, b);
	}

	template<class T1, class T2>
	bool operator == (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		if (a.first == b.first && a.second == b.second) {
			return true;
		} else {
			return false;
		}
	}

	template<class T1, class T2>
	bool operator != (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		if (a.first != b.first || a.second != b.second) {
			return true;
		} else {
			return false;
		}
	}

	template<class T1, class T2>
	bool operator < (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return (a.first < b.first || (!(b.first < a.first) && a.second < b.second));
	}

	template<class T1, class T2>
	bool operator > (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return b < a;
	}

	template<class T1, class T2>
	bool operator <= (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return !(b < a);
	}

	template<class T1, class T2>
	bool operator >= (const pair<T1, T2> &a, const pair<T1, T2> &b) {
		return !(a < b);
	}
}

#endif
