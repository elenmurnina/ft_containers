#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "red_black_tree_utils.hpp"
#include "iterator_traits.hpp"

namespace ft {

	struct input_iterator_tag {
	};

	struct output_iterator_tag {
	};

	struct forward_iterator_tag:
			public input_iterator_tag {
	};

	struct bidirectional_iterator_tag:
			public forward_iterator_tag {
	};

	struct random_access_iterator_tag:
			public bidirectional_iterator_tag {
	};

	template<class Category,
			class T,
			class Distance = std::ptrdiff_t,
			class Pointer = T *,
			class Reference = T &>
	struct iterator {
		typedef Category	iterator_category;
		typedef T 			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	// RandomAccessIterator
	template <class T>
	class RandomAccessIterator:
			public ft::iterator<std::random_access_iterator_tag, T> {
	public:
		typedef typename ft::iterator<std::random_access_iterator_tag, T>   iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator>::reference			reference;
		typedef typename ft::iterator_traits<iterator>::pointer				pointer;

		RandomAccessIterator(): ptr(NULL) {
		};

		RandomAccessIterator(T *ptr): ptr(ptr) {
		};

		RandomAccessIterator(const RandomAccessIterator &other) {
			*this = other;
		};

		RandomAccessIterator &operator = (const RandomAccessIterator &other) {
			ptr = other.ptr;
			return *this;
		};

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

		RandomAccessIterator& operator += (difference_type n) {
			ptr += n;
			return *this;
		}

		RandomAccessIterator operator + (difference_type n) {
			RandomAccessIterator result = *this;
			result += n;
			return result;
		}

		RandomAccessIterator& operator -= (difference_type n) {
			ptr -= n;
			return *this;
		}

		RandomAccessIterator operator - (difference_type n) {
			RandomAccessIterator copy = *this;
			copy -= n;
			return copy;
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

	template <class T>
	class RandomAccessConstIterator:
			public ft::iterator<std::random_access_iterator_tag, T,
					std::ptrdiff_t, const T *, const T &> {
	public:
		typedef typename ft::iterator<std::random_access_iterator_tag,
				T, std::ptrdiff_t, const T *, const T &>	iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator>::reference		reference;
		typedef typename ft::iterator_traits<iterator>::pointer			pointer;

		RandomAccessConstIterator(): ptr(NULL) {
		};

		RandomAccessConstIterator(T *ptr): ptr(ptr) {
		};

		RandomAccessConstIterator(const RandomAccessConstIterator &other) {
			*this = other;
		};

		RandomAccessConstIterator& operator = (const RandomAccessConstIterator &other) {
			ptr = other.ptr;
			return *this;
		};

		reference operator * () const {
			return *ptr;
		}

		pointer operator -> () const {
			return ptr;
		}

		RandomAccessConstIterator& operator ++ () {
			ptr++;
			return *this;
		}

		RandomAccessConstIterator operator ++ (int) {
			RandomAccessConstIterator result = *this;
			ptr++;
			return result;
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

		RandomAccessConstIterator& operator += (difference_type n) {
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
	template <class T>
	class RandomAccessReverseIterator:
			public ft::iterator<std::random_access_iterator_tag, T> {
	public:
		typedef typename ft::iterator<std::random_access_iterator_tag, T>   iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator>::reference			reference;
		typedef typename ft::iterator_traits<iterator>::pointer				pointer;

		RandomAccessReverseIterator(): ptr(NULL) {
		};

		RandomAccessReverseIterator(T *ptr): ptr(ptr) {
		};

		RandomAccessReverseIterator(const RandomAccessReverseIterator &other) {
			*this = other;
		};

		RandomAccessReverseIterator& operator = (const RandomAccessReverseIterator &other) {
			ptr = other.ptr;
			return *this;
		};

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

		RandomAccessReverseIterator& operator += (difference_type n) {
			ptr -= n;
			return *this;
		}

		RandomAccessReverseIterator operator + (difference_type n) {
			RandomAccessReverseIterator result = *this;
			result += n;
			return result;
		}

		RandomAccessReverseIterator& operator -= (difference_type n) {
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
								const RandomAccessReverseIterator &b)  {
			return a.ptr < b.ptr;
		}
		friend bool operator >= (const RandomAccessReverseIterator &a,
								 const RandomAccessReverseIterator &b)  {
			return a.ptr <= b.ptr;
		}
		friend bool operator < (const RandomAccessReverseIterator &a,
								const RandomAccessReverseIterator &b)  {
			return a.ptr > b.ptr;
		}
		friend bool operator <= (const RandomAccessReverseIterator &a,
								 const RandomAccessReverseIterator &b)  {
			return a.ptr >= b.ptr;
		}

	private:
		T *ptr;
	};

	template <class T>
	class RandomAccessConstReverseIterator:
			public ft::iterator<std::random_access_iterator_tag, T,
					std::ptrdiff_t, const T *, const T &> {
	public:
		typedef typename ft::iterator<std::random_access_iterator_tag,
				T, std::ptrdiff_t, const T *, const T &>		iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator>::reference		reference;
		typedef typename ft::iterator_traits<iterator>::pointer			pointer;

		RandomAccessConstReverseIterator(): ptr(NULL) {
		};

		RandomAccessConstReverseIterator(T *ptr): ptr(ptr) {
		};

		RandomAccessConstReverseIterator(const RandomAccessConstReverseIterator &other) {
			*this = other;
		};

		RandomAccessConstReverseIterator& operator = (const RandomAccessConstReverseIterator &other) {
			ptr = other.ptr;
			return *this;
		};

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

		RandomAccessConstReverseIterator& operator += (difference_type n) {
			ptr -= n;
			return *this;
		}

		RandomAccessConstReverseIterator operator + (difference_type n) {
			RandomAccessConstReverseIterator result = *this;
			result += n;
			return result;
		}

		RandomAccessConstReverseIterator& operator -= (difference_type n) {
			ptr += n;
			return *this;
		}

		RandomAccessConstReverseIterator operator - (difference_type n) {
			RandomAccessConstReverseIterator copy = *this;
			copy -= n;
			return copy;
		}

		friend difference_type operator - (const RandomAccessConstReverseIterator &a,
										   const RandomAccessConstReverseIterator &b) {
			return b.ptr - a.ptr;
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

	// RBTreeIterator
	template <class T>
	class	RBTreeIterator:
			public ft::iterator<std::bidirectional_iterator_tag, T> {
	public:
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>   iterator;
		typedef typename ft::iterator_traits<iterator>::reference			reference;
		typedef typename ft::iterator_traits<iterator>::pointer				pointer;

		typedef RBTNode<T> Node;

	private:
		Node *ptr;

	public:
		RBTreeIterator(): ptr(NULL) {
		};

		RBTreeIterator(Node *ptr): ptr(ptr) {
		};

		RBTreeIterator(const RBTreeIterator &other): ptr(other.getptr()) {
		};

		~RBTreeIterator() {
		};

		RBTreeIterator &operator = (const RBTreeIterator &other) {
			ptr = other.ptr;
			return *this;
		};

		reference operator * () {
			return ptr->value;
		}

		pointer operator -> () {
			return &(ptr->value);
		}

		RBTreeIterator& operator ++ () {
			ptr = next_iter(ptr);
			return *this;
		}

		RBTreeIterator operator ++ (int) {
			RBTreeIterator result = *this;
			operator++();
			return result;
		}

		RBTreeIterator& operator -- () {
			ptr = prev_iter(ptr);
			return *this;
		}

		RBTreeIterator operator -- (int) {
			RBTreeIterator result = *this;
			operator -- ();
			return result;
		}

		Node *getptr() const {
			return ptr;
		}

		friend bool operator == (const RBTreeIterator &a, const RBTreeIterator &b) {
			return a.ptr == b.ptr;
		}

		friend bool operator != (const RBTreeIterator &a, const RBTreeIterator &b) {
			return a.ptr != b.ptr;
		}

	private:
		Node *next_min_elem(Node *node) {
			while (node && node->left) {
				node = node->left;
			}
			return node;
		}

		Node *prev_max_elem(Node *node) {
			while (node && node->right) {
				node = node->right;
			}
			return node;
		}

		Node *next_iter(Node *node) {
			if (node->right) {
				return next_min_elem(node->right);
			} else {
				Node *parent = node->parent;
				while (parent && node == parent->right) {
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
		}

		Node *prev_iter(Node *node) {
			if (node->left) {
				return prev_max_elem(node->left);
			} else {
				Node *parent = node->parent;
				while (parent && node == parent->left) {
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
		}
	};

	template <class T>
	class RBTreeConstIterator:
			public ft::iterator<std::bidirectional_iterator_tag, T,
					std::ptrdiff_t, const T *, const T &> {
	public:
		typedef typename ft::iterator<std::bidirectional_iterator_tag,
				T, std::ptrdiff_t, const T *, const T &>  					iterator;
		typedef typename ft::iterator_traits<iterator>::reference		reference;
		typedef typename ft::iterator_traits<iterator>::pointer			pointer;

		typedef RBTNode<T> Node;

	private:
		Node *ptr;

	public:
		RBTreeConstIterator(): ptr(NULL) {
		};

		RBTreeConstIterator(Node *ptr): ptr(ptr) {
		};

		RBTreeConstIterator(const RBTreeIterator<T> &other): ptr(other.getptr()) {
		};

		~RBTreeConstIterator() {
		};

		RBTreeConstIterator &operator = (const RBTreeIterator<T> &other) {
			ptr = other.ptr;
			return *this;
		};

		reference operator * () const {
			return ptr->value;
		}

		pointer operator -> () const {
			return &(ptr->value);
		}

		RBTreeConstIterator &operator ++ () {
			ptr = next_iter(ptr);
			return *this;
		}

		RBTreeConstIterator operator ++ (int) {
			RBTreeConstIterator result = *this;
			operator ++ ();
			return result;
		}

		RBTreeConstIterator &operator -- () {
			ptr = prev_iter(ptr);
			return *this;
		}

		RBTreeConstIterator operator -- (int) {
			RBTreeConstIterator result = *this;
			operator -- ();
			return result;
		}

		Node *getptr() const {
			return ptr;
		}

		friend bool operator == (const RBTreeConstIterator<T> &a, const RBTreeConstIterator<T> &b) {
			return a.ptr == b.ptr;
		}

		friend bool operator != (const RBTreeConstIterator<T> &a, const RBTreeConstIterator<T> &b) {
			return a.ptr != b.ptr;
		}

	private:
		Node *next_min_elem(Node *node) {
			while (node && node->left) {
				node = node->left;
			}
			return node;
		}

		Node *prev_max_elem(Node *node) {
			while (node && node->right) {
				node = node->right;
			}
			return node;
		}

		Node *next_iter(Node *node) {
			if (node->right) {
				return next_min_elem(node->right);
			} else {
				Node  *parent = node->parent;
				while (parent && node == parent->right) {
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
		}

		Node *prev_iter(Node *node) {
			if (node->left) {
				return prev_max_elem(node->left);
			} else {
				Node  *parent = node->parent;
				while (parent && node == parent->left) {
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
		}
	};

	// RBTreeReverseIterator
	template <class T>
	class RBTreeReverseIterator:
			public ft::iterator<std::bidirectional_iterator_tag, T> {
	public:
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>	iterator;
		typedef typename ft::iterator_traits<iterator>::reference			reference;
		typedef typename ft::iterator_traits<iterator>::pointer				pointer;

		typedef RBTNode<T>	Node;

	private:
		Node *ptr;

	public:
		RBTreeReverseIterator(): ptr(NULL) {
		};

		RBTreeReverseIterator(Node *ptr): ptr(ptr) {
		};

		RBTreeReverseIterator(const RBTreeReverseIterator &other): ptr(other.getptr()) {
		};

		~RBTreeReverseIterator() {
		};

		RBTreeReverseIterator& operator = (const RBTreeReverseIterator &other) {
			ptr = other.ptr;
			return *this;
		};

		reference operator * () {
			return ptr->value;
		}

		pointer operator -> () {
			return &(ptr->value);
		}

		RBTreeReverseIterator &operator ++ () {
			ptr = prev_iter(ptr);
			return *this;
		}

		RBTreeReverseIterator operator ++ (int) {
			RBTreeReverseIterator result = *this;
			operator ++ ();
			return result;
		}

		RBTreeReverseIterator &operator -- () {
			ptr = next_iter(ptr);
			return *this;
		}

		RBTreeReverseIterator operator -- (int) {
			RBTreeReverseIterator result = *this;
			operator -- ();
			return result;
		}

		Node *getptr() const {
			return ptr;
		}

		friend bool operator == (const RBTreeReverseIterator &a, const RBTreeReverseIterator &b) {
			return a.ptr == b.ptr;
		}

		friend bool operator != (const RBTreeReverseIterator &a, const RBTreeReverseIterator &b) {
			return a.ptr != b.ptr;
		}

	private:
		Node *next_min_elem(Node *node) {
			while (node && node->left) {
				node = node->left;
			}
			return node;
		}

		Node *prev_max_elem(Node *node) {
			while (node && node->right) {
				node = node->right;
			}
			return node;
		}

		Node *next_iter(Node *node) {
			if (node->right) {
				return next_min_elem(node->right);
			} else {
				Node *parent = node->parent;
				while (parent && node == parent->right) {
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
		}

		Node *prev_iter(Node *node) {
			if (node->left) {
				return prev_max_elem(node->left);
			} else {
				Node *parent = node->parent;
				while (parent && node == parent->left) {
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
		}
	};

	template <class T>
	class RBTreeConstReverseIterator:
			public ft::iterator<std::bidirectional_iterator_tag, T,
					std::ptrdiff_t, const T *, const T &> {
	public:
		typedef typename ft::iterator<std::bidirectional_iterator_tag,
				T, std::ptrdiff_t, const T *, const T &>			iterator;
		typedef typename ft::iterator_traits<iterator>::reference			reference;
		typedef typename ft::iterator_traits<iterator>::pointer				pointer;

		typedef RBTNode<T> Node;

	private:
		Node *ptr;

	public:
		RBTreeConstReverseIterator(): ptr(NULL) {
		};

		RBTreeConstReverseIterator(Node *ptr): ptr(ptr) {
		};

		RBTreeConstReverseIterator(const RBTreeConstReverseIterator &other): ptr(other.getptr()) {
		};

		~RBTreeConstReverseIterator() {
		};

		RBTreeConstReverseIterator &operator = (const RBTreeConstReverseIterator &other) {
			ptr = other.ptr;
			return *this;
		};

		reference operator * () {
			return ptr->value;
		}

		pointer operator -> () {
			return &(ptr->value);
		}

		RBTreeConstReverseIterator& operator ++ () {
			ptr = prev_iter(ptr);
			return *this;
		}

		RBTreeConstReverseIterator operator ++ (int) {
			RBTreeConstReverseIterator result = *this;
			operator ++ ();
			return result;
		}

		RBTreeConstReverseIterator& operator -- () {
			ptr = next_iter(ptr);
			return *this;
		}

		RBTreeConstReverseIterator operator -- (int) {
			RBTreeConstReverseIterator result = *this;
			operator -- ();
			return result;
		}

		Node *getptr() const {
			return ptr;
		}

		friend bool operator == (const RBTreeConstReverseIterator &a, const RBTreeConstReverseIterator &b) {
			return a.ptr == b.ptr;
		}

		friend bool operator != (const RBTreeConstReverseIterator &a, const RBTreeConstReverseIterator &b) {
			return a.ptr != b.ptr;
		}

	private:
		Node *next_min_elem(Node *node) {
			while (node && node->left) {
				node = node->left;
			}
			return node;
		}

		Node *prev_max_elem(Node *node) {
			while (node && node->right) {
				node = node->right;
			}
			return node;
		}

		Node *next_iter(Node *node) {
			if (node->right) {
				return next_min_elem(node->right);
			} else {
				Node *parent = node->parent;
				while (parent && node == parent->right) {
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
		}

		Node *prev_iter(Node *node) {
			if (node->left) {
				return prev_max_elem(node->left);
			} else {
				Node *parent = node->parent;
				while (parent && node == parent->left) {
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
		}
	};
}

#endif
