#ifndef OTHER_UTILS_HPP
#define OTHER_UTILS_HPP

#include <iosfwd>
#include <sstream>

namespace ft {

	static class nullptr_t {
	public:
		template<class T>
		explicit operator T*() const {
			return 0;
		}

		template<class C, class T>
		explicit operator T C::*() const {
			return 0;
		}

	private:
		void operator & () const;
	} u_nullptr = {};

	template<typename T>
	std::string to_string(T n) {
		std::ostringstream ss;
		ss << n;
		return ss.str();
	}

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last) {
		typename ft::iterator_traits<InputIterator>::difference_type result = 0;
		while (first != last) {
			first++;
			result++;
		}
		return result;
	}
}

#endif