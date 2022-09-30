#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterators_traits.hpp"

namespace ft {

	struct input_iterator_tag {
	};
	struct output_iterator_tag {
	};
	struct forward_iterator_tag :
			public input_iterator_tag {
	};
	struct bidirectional_iterator_tag :
			public forward_iterator_tag {
	};
	struct random_access_iterator_tag :
			public bidirectional_iterator_tag {
	};

	template<class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	// RandomAccessIterator
	template<class T>
	class RandomAccessIterator:
			public ft::iterator<std::random_access_iterator_tag, T> {
	public:
		typedef typename ft::iterator<std::random_access_iterator_tag, T>	iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator>::reference			reference;
		typedef typename ft::iterator_traits<iterator>::pointer				pointer;

		RandomAccessIterator(): ptr(NULL) {
		}

		RandomAccessIterator(T *ptr): ptr(ptr) {
		}

		RandomAccessIterator(const RandomAccessIterator &other) {
			*this = other;
		}

		RandomAccessIterator &operator = (const RandomAccessIterator &other) {
			ptr = other.ptr;
			return *this;
		}

		reference operator * () {
			return *ptr;
		}

		pointer operator -> () {
			return ptr;
		}

		RandomAccessIterator &operator ++ () {
			ptr++;
			return *this;
		}

		RandomAccessIterator operator ++ (int) {
			RandomAccessIterator result = *this;
			ptr++;
			return result;
		}

		RandomAccessIterator &operator -- () {
			ptr--;
			return *this;
		}

		RandomAccessIterator operator -- (int) {
			RandomAccessIterator result = *this;
			ptr--;
			return result;
		}

		RandomAccessIterator &operator += (difference_type n) {
			ptr += n;
			return *this;
		}

		RandomAccessIterator operator + (difference_type n) {
			RandomAccessIterator result = *this;
			result += n;
			return result;
		}

		RandomAccessIterator &operator -= (difference_type n) {
			ptr -= n;
			return *this;
		}

		RandomAccessIterator operator - (difference_type n) {
			RandomAccessIterator result = *this;
			result -= n;
			return result;
		}

		friend difference_type operator - (const RandomAccessIterator &a,
										   const RandomAccessIterator &b) {
			return a.ptr - b.ptr;
		}

		friend bool operator == (const RandomAccessIterator &a,
							     const RandomAccessIterator &b) {
			return a.ptr == b.ptr;
		}

		friend bool operator != (const RandomAccessIterator &a,
							     const RandomAccessIterator &b) {
			return a.ptr != b.ptr;
		}

		friend bool operator > (const RandomAccessIterator &a,
								const RandomAccessIterator &b) {
			return a.ptr > b.ptr;
		}

		friend bool operator >= (const RandomAccessIterator &a,
							   	 const RandomAccessIterator &b) {
			return a.ptr >= b.ptr;
		}

		friend bool operator < (const RandomAccessIterator &a,
							  	const RandomAccessIterator &b) {
			return a.ptr < b.ptr;
		}

		friend bool operator <= (const RandomAccessIterator &a,
							  	 const RandomAccessIterator &b) {
			return a.ptr <= b.ptr;
		}

	private:
		T *ptr;
	};

	template<class T>
	class RandomAccessConstIterator:
			public ft::iterator<std::random_access_iterator_tag, T, std::ptrdiff_t, const T *, const T &> {

	public:
		typedef typename ft::iterator<std::random_access_iterator_tag,
				T, std::ptrdiff_t, const T *, const T &> iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<iterator>::reference reference;
		typedef typename ft::iterator_traits<iterator>::pointer pointer;

		RandomAccessConstIterator(): ptr(NULL) {
		}

		RandomAccessConstIterator(T *ptr): ptr(ptr) {
		}

		RandomAccessConstIterator(const RandomAccessConstIterator &other) {
			*this = other;
		}

		RandomAccessConstIterator &operator = (const RandomAccessConstIterator &other) {
			ptr = other.ptr;
			return *this;
		}

		reference operator * () const {
			return *ptr;
		}

		pointer operator -> () const {
			return ptr;
		}

		RandomAccessConstIterator &operator ++ () {
			ptr++;
			return *this;
		}

		RandomAccessConstIterator operator ++ (int) {
			RandomAccessConstIterator tmp = *this;
			ptr++;
			return tmp;
		}

		RandomAccessConstIterator &operator -- () {
			ptr--;
			return *this;
		}

		RandomAccessConstIterator operator -- (int) {
			RandomAccessConstIterator result = *this;
			ptr--;
			return result;
		}

		RandomAccessConstIterator &operator += (difference_type n) {
			ptr += n;
			return *this;
		}

		RandomAccessConstIterator operator + (difference_type n) {
			RandomAccessConstIterator result = *this;
			result += n;
			return result;
		}

		RandomAccessConstIterator &operator -= (difference_type n) {
			ptr -= n;
			return *this;
		}

		RandomAccessConstIterator operator - (difference_type n) {
			RandomAccessConstIterator result = *this;
			result -= n;
			return result;
		}

		friend difference_type operator - (const RandomAccessConstIterator &a,
										   const RandomAccessConstIterator &b) {
			return a.ptr - b.ptr;
		}

		friend bool operator == (const RandomAccessConstIterator &a,
								 const RandomAccessConstIterator &b) {
			return a.ptr == b.ptr;
		}

		friend bool operator != (const RandomAccessConstIterator &a,
							   	 const RandomAccessConstIterator &b) {
			return a.ptr != b.ptr;
		}

		friend bool operator > (const RandomAccessConstIterator &a,
								const RandomAccessConstIterator &b) {
			return a.ptr > b.ptr;
		}

		friend bool operator >= (const RandomAccessConstIterator &a,
							   	 const RandomAccessConstIterator &b) {
			return a.ptr >= b.ptr;
		}

		friend bool operator < (const RandomAccessConstIterator &a,
							  	const RandomAccessConstIterator &b) {
			return a.ptr < b.ptr;
		}

		friend bool operator <= (const RandomAccessConstIterator &a,
							   	 const RandomAccessConstIterator &b) {
			return a.ptr <= b.ptr;
		}

	private:
		T *ptr;
	};

	// RandomAccessReverseIterator
	template<class T>
	class RandomAccessReverseIterator:
			public ft::iterator<std::random_access_iterator_tag, T> {

	public:
		typedef typename ft::iterator<std::random_access_iterator_tag, T> iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<iterator>::reference reference;
		typedef typename ft::iterator_traits<iterator>::pointer pointer;

		RandomAccessReverseIterator(): ptr(NULL) {
		}

		RandomAccessReverseIterator(T *ptr): ptr(ptr) {
		}

		RandomAccessReverseIterator(const RandomAccessReverseIterator &other) {
			*this = other;
		}

		RandomAccessReverseIterator &operator = (const RandomAccessReverseIterator &other) {
			ptr = other.ptr;
			return *this;
		}

		reference operator * () {
			return *ptr;

		}

		pointer operator -> () {
			return ptr;
		}

		RandomAccessReverseIterator operator ++ () {
			ptr--;
			return *this;
		}

		RandomAccessReverseIterator operator ++ (int) {
			RandomAccessReverseIterator result = *this;
			ptr--;
			return result;
		}

		RandomAccessReverseIterator operator -- () {
			ptr++;
			return *this;
		}

		RandomAccessReverseIterator operator -- (int) {
			RandomAccessReverseIterator result = *this;
			ptr++;
			return result;
		}

		RandomAccessReverseIterator &operator += (difference_type n) {
			ptr -= n;
			return *this;
		}

		RandomAccessReverseIterator operator + (difference_type n) {
			RandomAccessReverseIterator result = *this;
			result += n;
			return result;
		}

		RandomAccessReverseIterator &operator -= (difference_type n) {
			ptr += n;
			return *this;
		}

		RandomAccessReverseIterator operator - (difference_type n) {
			RandomAccessReverseIterator result = *this;
			result -= n;
			return result;
		}

		friend difference_type operator - (const RandomAccessReverseIterator &a,
										   const RandomAccessReverseIterator &b) {
			return b.ptr - a.ptr;
		}

		friend bool operator == (const RandomAccessReverseIterator &a,
							   	 const RandomAccessReverseIterator &b) {
			return a.ptr == b.ptr;
		}

		friend bool operator != (const RandomAccessReverseIterator &a,
							   	 const RandomAccessReverseIterator &b) {
			return a.ptr != b.ptr;
		}

		friend bool operator > (const RandomAccessReverseIterator &a,
								const RandomAccessReverseIterator &b) {
			return a.ptr < b.ptr;
		}

		friend bool operator >= (const RandomAccessReverseIterator &a,
							   	 const RandomAccessReverseIterator &b) {
			return a.ptr <= b.ptr;
		}

		friend bool operator < (const RandomAccessReverseIterator &a,
							  	const RandomAccessReverseIterator &b) {
			return a.ptr > b.ptr;
		}

		friend bool operator <= (const RandomAccessReverseIterator &a,
							   	 const RandomAccessReverseIterator &b) {
			return a.ptr >= b.ptr;
		}

	private:
		T *ptr;
	};

	template<class T>
	class RandomAccessConstReverseIterator:
			public ft::iterator<std::random_access_iterator_tag, T, std::ptrdiff_t, const T *, const T &> {

	public:
		typedef typename ft::iterator<std::random_access_iterator_tag,
				T, std::ptrdiff_t, const T *, const T &> iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<iterator>::reference reference;
		typedef typename ft::iterator_traits<iterator>::pointer pointer;

		RandomAccessConstReverseIterator(): ptr(NULL) {
		}

		RandomAccessConstReverseIterator(T *ptr): ptr(ptr) {
		}

		RandomAccessConstReverseIterator(const RandomAccessConstReverseIterator &other) {
			*this = other;
		}

		RandomAccessConstReverseIterator &operator = (const RandomAccessConstReverseIterator &other) {
			ptr = other.ptr;
			return *this;
		}

		reference operator * () const {
			return *ptr;
		}

		pointer operator -> () const {
			return ptr;
		}

		RandomAccessConstReverseIterator operator ++ () {
			ptr--;
			return *this;
		}

		RandomAccessConstReverseIterator operator ++ (int) {
			RandomAccessConstReverseIterator result = *this;
			ptr--;
			return result;
		}

		RandomAccessConstReverseIterator operator -- () {
			ptr++;
			return *this;
		}

		RandomAccessConstReverseIterator operator -- (int) {
			RandomAccessConstReverseIterator result = *this;
			ptr++;
			return result;
		}

		RandomAccessConstReverseIterator &operator += (difference_type n) {
			ptr -= n;
			return *this;
		}

		RandomAccessConstReverseIterator operator + (difference_type n) {
			RandomAccessConstReverseIterator result = *this;
			result += n;
			return result;
		}

		RandomAccessConstReverseIterator &operator -= (difference_type n) {
			ptr += n;
			return *this;
		}

		RandomAccessConstReverseIterator operator - (difference_type n) {
			RandomAccessConstReverseIterator result = *this;
			result -= n;
			return result;
		}

		friend difference_type operator - (const RandomAccessConstReverseIterator &a,
										   const RandomAccessConstReverseIterator &b) {
			return a.ptr - b.ptr;
		}

		friend bool operator == (const RandomAccessConstReverseIterator &a,
							   	 const RandomAccessConstReverseIterator &b) {
			return a.ptr == b.ptr;
		}

		friend bool operator != (const RandomAccessConstReverseIterator &a,
							   	 const RandomAccessConstReverseIterator &b) {
			return a.ptr != b.ptr;
		}

		friend bool operator > (const RandomAccessConstReverseIterator &a,
							  	const RandomAccessConstReverseIterator &b) {
			return a.ptr < b.ptr;
		}

		friend bool operator >= (const RandomAccessConstReverseIterator &a,
							  	 const RandomAccessConstReverseIterator &b) {
			return a.ptr <= b.ptr;
		}

		friend bool operator < (const RandomAccessConstReverseIterator &a,
							  	const RandomAccessConstReverseIterator &b) {
			return a.ptr > b.ptr;
		}

		friend bool operator <= (const RandomAccessConstReverseIterator &a,
							   	 const RandomAccessConstReverseIterator &b) {
			return a.ptr >= b.ptr;
		}

	private:
		T *ptr;
	};

	template <bool is_valid, typename T>
	struct valid_iterator_tag_res {
		typedef T type; const static bool value = is_valid;
	};

	template <typename T>
	struct is_input_iterator_tagged:
			public valid_iterator_tag_res<false, T> {
	};

	template <>
	struct is_input_iterator_tagged<ft::random_access_iterator_tag>:
			public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {
	};

	template <>
	struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>:
			public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {
	};

	template <>
	struct is_input_iterator_tagged<ft::forward_iterator_tag>:
			public valid_iterator_tag_res<true, ft::forward_iterator_tag> {
	};

	template <>
	struct is_input_iterator_tagged<ft::input_iterator_tag>:
			public valid_iterator_tag_res<true, ft::input_iterator_tag> {
	};

	template <typename T>
	struct is_ft_iterator_tagged:
			public valid_iterator_tag_res<false, T> {
	};

	template <>
	struct is_ft_iterator_tagged<ft::random_access_iterator_tag>:
			public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {
	};

	template <>
	struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>:
			public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {
	};

	template <>
	struct is_ft_iterator_tagged<ft::forward_iterator_tag>:
			public valid_iterator_tag_res<true, ft::forward_iterator_tag> {
	};

	template <>
	struct is_ft_iterator_tagged<ft::input_iterator_tag>:
			public valid_iterator_tag_res<true, ft::input_iterator_tag> {
	};

	template <>
	struct is_ft_iterator_tagged<ft::output_iterator_tag>:
			public valid_iterator_tag_res<true, ft::output_iterator_tag> {
	};

	template <typename T>
	class InvalidIteratorException:
			public std::exception {
	private:
		std::string _msg;

	public:
		InvalidIteratorException () throw() {
			_msg = "Is invalid iterator tag: " + std::string(typeid(T).name());
		}

		InvalidIteratorException (const InvalidIteratorException&) throw() {
		}

		InvalidIteratorException& operator = (const InvalidIteratorException&) throw() {
		}

		virtual ~InvalidIteratorException() throw() {
		}

		virtual const char *what() const throw() {
			return _msg.c_str();
		}
	};
}

#endif