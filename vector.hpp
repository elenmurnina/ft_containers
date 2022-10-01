#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef value_type								&reference;
		typedef const value_type						&const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef ft::RandomAccessIterator<T>				iterator;
		typedef ft::RandomAccessConstIterator<T>		const_iterator;
		typedef	ft::RandomAccessReverseIterator<T>		reverse_iterator;
		typedef	ft::RandomAccessConstReverseIterator<T>	const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef std::size_t								size_type;

		vector();
		explicit vector(const Allocator &alloc);
		explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator());

		template<class InputIterator>
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			   InputIterator last, const Allocator &alloc = Allocator());

		vector(const vector &other);
		~vector();
		vector	&operator = (const vector &other);

		// Iterators
		iterator				begin();
		iterator				end();
		reverse_iterator		rbegin();
		reverse_iterator		rend();
		const_iterator			begin() const;
		const_iterator			end() const;
		const_reverse_iterator	rbegin() const;
		const_reverse_iterator	rend() const;

		// Capacity
		size_type	size() const;
		size_type	max_size() const;
		void		resize(size_type count, T value = T());
		size_type	capacity() const;
		bool 		empty() const;
		void		reserve(size_type new_capacity);

		// Element access
		reference			operator [] (size_type position);
		const_reference		operator [] (size_type position) const;
		reference			at(size_type position);
		const_reference		at(size_type position) const;
		reference			front();
		const_reference		front() const;
		reference			back();
		const_reference		back() const;
		T					*data();
		const T				*data() const;

		// Modifiers
		void		assign(size_type count, const T &value);
		template<class InputIterator>
		void		assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
				InputIterator>::type first, InputIterator last);
		void		push_back(const T &value);
		void		pop_back();
		iterator	insert(iterator position, const T &value);
		void		insert(iterator pos, size_type count, const T &value);
		template <class InputIterator>
		void		insert(typename vector<T, Allocator>::iterator pos,
						   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
						   InputIterator last);
		iterator 	erase(iterator position);
		iterator 	erase(iterator first, iterator last);
		void		swap(vector &other);
		void		clear();

		//Allocator
		allocator_type get_allocator() const;

	private:
		T			*_data;
		size_type	_size;
		size_type	_capacity;
		Allocator	_alloc;
	};

	template<class T, class Allocator>
	vector<T, Allocator>::vector(): _size(0), _capacity(0), _alloc() {
		_data = _alloc.allocate(0);
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(const Allocator& alloc): _size(0), _capacity(0), _alloc(alloc) {
		_data = _alloc.allocate(0);
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(vector<T, Allocator>::size_type count, const T &value, const Allocator &alloc):
			_size(count), _capacity(count), _alloc(alloc) {
		size_type i = 0;
		_data = _alloc.allocate(_capacity);

		try {
			for (; i < count; i++) {
				_alloc.construct(_data + i, value);
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(_data + i - 1);
			}
			_alloc.deallocate(_data, _capacity);
			throw;
		}
	}

	template<class T, class Allocator>
	template<class InputIterator>
	vector<T, Allocator>::vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
			InputIterator>::type first, InputIterator last, const Allocator &alloc):
			_size(0), _capacity(0), _alloc(alloc) {
		difference_type diff = ft::distance(first, last);
		size_type i = 0;
		_data = _alloc.allocate(diff);

		try {
			for (; first != last; i++) {
				_alloc.construct(_data + i, *first);
				first++;
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(_data + i - 1);
			}
			_alloc.deallocate(_data, diff);
			throw;
		}
		_size = diff;
		_capacity = diff;
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(const vector &other):
			_size(other._size), _capacity(other._capacity), _alloc(other._alloc) {
		size_type i = 0;
		_data = _alloc.allocate(_capacity);

		try {
			for (; i < _size; i++) {
				_alloc.construct(_data + i, other._data[i]);
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(_data + i - 1);
			}
			_alloc.deallocate(_data, _capacity);
			throw;
		}
	}

	template<class T, class Allocator>
	vector<T, Allocator>::~vector() {
		for (size_type i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
	}

	template<class T, class Allocator>
	vector<T, Allocator> &vector<T, Allocator>::operator = (const vector &other) {
		T *copy = _alloc.allocate(other._capacity);
		size_type i = 0;

		try {
			for (; i < other._size; i++) {
				_alloc.construct(copy + i, other._data[i]);
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(copy + i - 1);
			}
			_alloc.deallocate(copy, _capacity);
			throw;
		}

		for (i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
		_data = copy;
		_size = other._size;
		_capacity = other._capacity;
		return *this;
	}

	// Iterators
	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator	vector<T, Allocator>::begin() {
		return iterator(_data);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::end() {
		return iterator(_data + _size);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() {
		return reverse_iterator(_data + _size - 1);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend() {
		return reverse_iterator(_data - 1);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const {
		return const_iterator(_data);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const {
		return const_iterator(_data + _size);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const {
		return const_reverse_iterator(_data + _size - 1);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const {
		return const_reverse_iterator(_data - 1);
	}

	// Capacity
	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const {
		return _size;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const {
		return allocator_type().max_size();
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::resize(size_type count, T value) {
		size_type i;
		if (count < _size) {
			for (i = count; i < _size; i++) {
				_alloc.destroy(_data + i);
			}
		} else if (count > _size) {
			for (i = _size; i < count; i++) {
				try {
					push_back(value);
				} catch (...) {
					for (size_type j = _size; j < i; j++) {
						_alloc.destroy(_data + j);
					}
					throw;
				}
			}
		}
		_size = count;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const {
		return _capacity;
	}

	template<class T, class Allocator>
	bool vector<T, Allocator>::empty() const {
		return _size == 0;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::reserve(size_type new_capacity) {
		if (new_capacity > max_size()) {
			throw std::length_error("Error: size can't be greater than max_size.");
		}
		if (new_capacity > _capacity) {
			T *new_storage = _alloc.allocate(new_capacity);
			size_type i = 0;

			try {
				for (; i < _size; i++) {
					_alloc.construct(new_storage + i, _data[i]);
				}
			} catch (...) {
				for (; i > 0; i--) {
					_alloc.destroy(new_storage + i - 1);
				}
				_alloc.deallocate(new_storage, new_capacity);
				throw;
			}

			for (i = 0; i < _size; i++) {
				_alloc.destroy(_data + i);
			}
			_alloc.deallocate(_data, _capacity);
			_data = new_storage;
			_capacity = new_capacity;
		}
	}

	// Element access
	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::operator [] (size_type position) {
		return _data[position];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator [] (size_type position) const {
		return _data[position];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type position) {
		if (position>= _size) {
			throw std::out_of_range("vector");
		}
		return _data[position];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type position) const {
		if (position>= _size) {
			throw std::out_of_range("vector");
		}
		return _data[position];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
		return _data[0];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const {
		return _data[0];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
		return _data[_size - 1];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const {
		return _data[_size - 1];
	}

	template<class T, class Allocator>
	T *vector<T, Allocator>::data() {
		return _data;
	}

	template<class T, class Allocator>
	const T *vector<T, Allocator>::data() const {
		return _data;
	}

	// Modifiers
	template<class T, class Allocator>
	void vector<T, Allocator>::assign(size_type count, const T &value) {
		T *copy = _alloc.allocate(count);
		size_type i = 0;

		try {
			for (; i < count; i++) {
				_alloc.construct(copy + i, value);
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(copy + i - 1);
			}
			_alloc.deallocate(copy, count);
			throw;
		}

		for (i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
		_data = copy;
		_size = count;
		_capacity = count;
	}

	template <class T, class Allocator>
	template <class InputIterator>
	void vector<T, Allocator>::assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
			InputIterator>::type first, InputIterator last) {
		difference_type	diff = ft::distance(first, last);
		T *tmp = _alloc.allocate(diff);
		size_type i = 0;

		try {
			for (; first != last; i++) {
				_alloc.construct(tmp + i, *first);
				first++;
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(tmp + i - 1);
			}
			_alloc.deallocate(tmp, diff);
			throw;
		}

		for (i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
		_data = tmp;
		_size = diff;
		_capacity = diff;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::push_back(const T &value) {
		if (_capacity == 0 || _size == _capacity) {
			size_type new_capacity = 1;
			if (_capacity > 0) {
				new_capacity = _capacity << 1;
			}
			T *tmp = _alloc.allocate(new_capacity);
			size_type i = 0;

			try {
				for (; i < _size; i++) {
					_alloc.construct(tmp + i, _data[i]);
				}
			} catch (...) {
				for (; i > 0; i--) {
					_alloc.destroy(tmp + i - 1);
				}
				_alloc.deallocate(tmp, new_capacity);
				throw;
			}

			for (i = 0; i < _size; i++) {
				_alloc.destroy(_data + i);
			}
			_alloc.deallocate(_data, _capacity);
			_data = tmp;
			_capacity = new_capacity;
		}
		_alloc.construct(_data + _size, value);
		_size++;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::pop_back() {
		_alloc.destroy(_data + _size);
		_size--;
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(typename vector<T, Allocator>::iterator position,
																		 const T &value) {
		size_type count = position - begin();
		size_type new_capacity = _capacity;
		size_type i;

		if (_size == _capacity) {
			new_capacity = _capacity << 1;
		}
		T *tmp = _alloc.allocate(new_capacity);

		try {
			for (i = 0; i < count; i++) {
				_alloc.construct(tmp + count, _data[i]);
			}
			_alloc.construct(tmp + count, value);
			for (; i < _size; i++) {
				_alloc.construct(tmp + i + 1, _data[i]);
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(tmp + i - 1);
			}
			_alloc.deallocate(tmp, new_capacity);
			throw;
		}

		for (i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
		_data = tmp;
		_size++;
		_capacity = new_capacity;
		return vector<T, Allocator>::iterator(_data + count);
	}

	template <class T, class Allocator>
	void vector<T, Allocator>::insert(typename vector<T, Allocator>::iterator position,
									  size_type count, const T &value) {
		size_type new_capacity = _capacity;
		if (_size + count > _capacity) {
			new_capacity = _capacity << 1;
			while (new_capacity < _capacity + count) {
				new_capacity <<= 1;
			}
		}
		T *tmp = _alloc.allocate(new_capacity);
		size_type num = position - begin();
		size_type i = 0;

		try {
			for (; i < num; i++) {
				_alloc.construct(tmp + i, _data[i]);
			}
			for (; i < num + count; i++) {
				_alloc.construct(tmp + i, value);
			}
			for (; i < _size + count; i++) {
				_alloc.construct(tmp + i, _data[i - count]);
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(tmp + i - 1);
			}
			_alloc.deallocate(tmp, new_capacity);
			throw;
		}

		for (i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
		_data = tmp;
		_size += count;
		_capacity = new_capacity;
	}

	template <class T, class Allocator>
	template<class InputIterator>
	void vector<T, Allocator>::insert(typename vector<T, Allocator>::iterator position,
									  typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
									  InputIterator last) {
		size_type diff = ft::distance(first, last);
		size_type new_capacity = _capacity;
		if (_size + diff > _capacity) {
			new_capacity = _capacity << 1;
			while (new_capacity < _capacity + diff) {
				new_capacity <<= 1;
			}
		}
		T *tmp = _alloc.allocate(new_capacity);
		size_type count = position - begin();
		size_type i = 0;

		try {
			for (; i < count; i++) {
				_alloc.construct(tmp + i, _data[i]);
			}
			for (; i < count + diff; i++) {
				_alloc.construct(tmp + i, *first);
				first++;
			}
			for (; i < _size + diff; i++) {
				_alloc.construct(tmp + i, _data[i - diff]);
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(tmp + i - 1);
			}
			_alloc.deallocate(tmp, new_capacity);
			throw;
		}

		for (i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
		_data = tmp;
		_size += diff;
		_capacity = new_capacity;
	}



	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(typename vector<T, Allocator>::iterator position) {
		T *tmp = _alloc.allocate(_capacity);
		size_type count = position - begin();
		size_type i = 0;

		try {
			for (; i < count; i++) {
				_alloc.construct(tmp + i, _data[i]);
			}
			for (; i < _size - 1; i++) {
				_alloc.construct(tmp + i, _data[i + 1]);
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(tmp + i - 1);
			}
			_alloc.deallocate(tmp, _capacity);
			throw;
		}

		for (i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
		_data = tmp;
		_size--;
		return iterator(_data + count);
	}

	template <class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(typename vector<T, Allocator>::iterator first,
																		typename vector<T, Allocator>::iterator last) {
		size_type count = first - begin();
		size_type diff = last - first;
		T *tmp = _alloc.allocate(_capacity);
		size_type i = 0;

		try {
			for (; i < count; i++) {
				_alloc.construct(tmp + i, _data[i]);
			}
			for (; i < _size - diff; i++) {
				_alloc.construct(tmp + i, _data[i + diff]);
			}
		} catch (...) {
			for (; i > 0; i--) {
				_alloc.destroy(tmp + i - 1);
			}
			_alloc.deallocate(tmp, _capacity);
			throw;
		}

		for (i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
		_data = tmp;
		_size -= diff;
		return iterator(_data + count);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::swap(vector &other) {
		std::swap(_data, other._data);
		std::swap(_capacity, other._capacity);
		std::swap(_size, other._size);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::clear() {
		for (size_type i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_size = 0;
	}

	// Allocator
	template<class T, class Allocator>
	typename vector<T, Allocator>::allocator_type vector<T, Allocator>::get_allocator() const {
		return _alloc;
	}

	// Non-member functions
	template<class T, class Allocator>
	bool operator == (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		if (a.size() != b.size()) {
			return false;
		}
		return ft::equal(a.begin(), a.end(), b.begin());
	}

	template<class T, class Allocator>
	bool operator != (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return !(a == b);
	}

	template <class T, class Allocator>
	bool operator < (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	template <class T, class Allocator>
	bool operator <= (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return !(b < a);
	}

	template <class T, class Allocator>
	bool operator > (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return b < a;
	}

	template <class T, class Allocator>
	bool operator >= (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return !(a < b);
	}
}

#endif
