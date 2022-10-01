#ifndef SET_HPP
#define SET_HPP

#include "red_black_tree.hpp"
#include "utils.hpp"
#include "pair.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

	template<class Key,
			class Compare = std::less <Key>,
			class Allocator = std::allocator <Key>
	>
	class set {
	public:
		typedef Key key_type;
		typedef Key value_type;
		typedef std::size_t size_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

		typedef typename ft::RBTree<Key, Compare, Allocator>::iterator iterator;
		typedef typename ft::RBTree<Key, Compare, Allocator>::const_iterator const_iterator;
		typedef typename ft::RBTree<Key, Compare, Allocator>::reverse_iterator reverse_iterator;
		typedef typename ft::RBTree<Key, Compare, Allocator>::const_reverse_iterator const_reverse_iterator;

		typedef typename iterator_traits<iterator>::difference_type difference_type;

		class value_compare : std::binary_function<value_type, value_type, bool> {
		protected:
			Compare comp;

			value_compare(Compare c) : comp(c) {
			}

		public:
			bool operator()(const value_type &a, const value_type &b) const {
				return comp(a.first, b.first);
			}
		};

	private:
		ft::RBTree<Key, Compare, Allocator> _tree;

	public:
		set() : _tree() {
		}

		explicit set(const Compare &comp, const Allocator &alloc = Allocator()) : _tree(comp, alloc) {
		}

		set(const set &other) : _tree(other._tree) {
		}

		template<class InputIterator>
		set(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
				InputIterator>::type first, InputIterator last,
			const Compare &comp = Compare(), const Allocator &alloc = Allocator()) {
			while (first != last) {
				_tree.insert(*first, Insert);
				first++;
			}
		}

		~set() {
		}

		set &operator=(const set &other) {
			_tree = other._tree;
			return *this;
		}

		allocator_type get_allocator() const {
			return _tree.get_allocator();
		}

		bool empty() const {
			return _tree.empty();
		}

		size_type size() const {
			return _tree.size();
		}

		size_type max_size() const {
			return _tree.max_size();
		}

		iterator begin() {
			return _tree.begin();
		}

		const_iterator begin() const {
			return _tree.begin();
		}

		iterator end() {
			return _tree.end();
		}

		const_iterator end() const {
			return _tree.end();
		}

		reverse_iterator rbegin() {
			return _tree.rbegin();
		}

		const_reverse_iterator rbegin() const {
			return _tree.rbegin();
		}

		reverse_iterator rend() {
			return _tree.rend();
		}

		const_reverse_iterator rend() const {
			return _tree.rend();
		}

		ft::pair<iterator, bool> insert(const value_type &value) {
			return _tree.insert(value, Insert);
		}

		iterator insert(iterator hint, const value_type &value) {
			return _tree.insert(hint, value);
		}

		template<class InputIterator>
		void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
				InputIterator>::type first, InputIterator last) {
			_tree.insert(first, last);
		}

		void erase(iterator pos) {
			_tree.erase(pos);
		}

		void erase(iterator first, iterator last) {
			_tree.erase(first, last);
		}

		size_type erase(const value_type &key) {
			return _tree.erase(key);
		}

		iterator find(const value_type &key) {
			return _tree.find(key);
		}

		const_iterator find(const value_type &key) const {
			return _tree.find(key);
		}

		ft::pair<iterator, iterator> equal_range(const value_type &key) {
			return _tree.equal_range(key);
		}

		ft::pair<const_iterator, const_iterator> equal_range(const value_type &key) const {
			return _tree.equal_range(key);
		}

		iterator lower_bound(const value_type &key) {
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound(const value_type &key) const {
			return _tree.lower_bound(key);
		}

		iterator upper_bound(const value_type &key) {
			return _tree.upper_bound(key);
		}

		const_iterator upper_bound(const value_type &key) const {
			return _tree.upper_bound(key);
		}

		void swap(set &other) {
			_tree.swap(other._tree);
		}

		size_type count(const Key &key) const {
			if (_tree.find(key) == _tree.end()) {
				return 0;
			} else {
				return 1;
			}
		}

		void clear() {
			_tree.clear();
		}

		key_compare key_comp() const {
			return key_compare();
		}

		value_compare value_comp() const {
			return value_compare(key_compare());
		}

	};

	template<class T, class Compare, class Allocator>
	bool operator==(const set<T, Compare, Allocator> &a, const set<T, Compare, Allocator> &b) {
		if (a.size() != b.size()) {
			return false;
		} else {
			return ft::equal(a.begin(), a.end(), b.begin());
		}
	}

	template<class T, class Compare, class Allocator>
	bool operator!=(const set<T, Compare, Allocator> &a, const set<T, Compare, Allocator> &b) {
		return !(a == b);
	}

	template<class T, class Compare, class Allocator>
	bool operator<(const set<T, Compare, Allocator> &a, const set<T, Compare, Allocator> &b) {
		return ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	template<class T, class Compare, class Allocator>
	bool operator<=(const set<T, Compare, Allocator> &a, const set<T, Compare, Allocator> &b) {
		return !(b < a);
	}

	template<class T, class Compare, class Allocator>
	bool operator>(const set<T, Compare, Allocator> &a, const set<T, Compare, Allocator> &b) {
		return b < a;
	}

	template<class T, class Compare, class Allocator>
	bool operator>=(const set<T, Compare, Allocator> &a, const set<T, Compare, Allocator> &b) {
		return !(a < b);
	}
}

#endif
