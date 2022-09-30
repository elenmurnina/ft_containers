#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils/enable_if.hpp"
#include "utils/equal.hpp"
#include "utils/is_integral.hpp"
#include "utils/iterator.hpp"
#include "utils/other_utils.hpp"
#include "utils/pair.hpp"
#include "utils/reverse_iterator.hpp"

namespace ft {

	template < class T, class Allocator = std::allocator <T> >
	class vector {
	public:
		typedef T													value_type;
		typedef Allocator											allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef RandomAccessIterator<T>								iterator;
		typedef RandomAccessConstIterator<T>						const_iterator;
		typedef	RandomAccessReverseIterator<T>						reverse_iterator;
		typedef	RandomAccessConstReverseIterator<T>					const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type					size_type;

		vector();
		explicit vector(const allocator_type &allocator = allocator_type()):
				_alloc(allocator), _start(u_nullptr), _end(u_nullptr), _end_capacity(u_nullptr) {
		}

		explicit vector(size_type size, const value_type &val = value_type(),
						const allocator_type &allocator = allocator_type()):
						_alloc(allocator), _start(u_nullptr), _end(u_nullptr), _end_capacity(u_nullptr) {
			_start = _alloc.allocate(size);
			_end_capacity = _start + size;
			_end = _start;
			while (size > 0) {
				_alloc.construct(_end, val);
				_end++;
				size--;
			}
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				typename enable_if<!is_integral<InputIterator>::value,
					InputIterator>::type* = u_nullptr): _alloc(alloc) {
			bool is_valid;
			if (!(is_valid = is_ft_iterator_tagged<typename iterator_traits<InputIterator>::iterator_category >::value))
				throw (InvalidIteratorException<typename is_ft_iterator_tagged<typename iterator_traits<InputIterator>::iterator_category >::type>());

			difference_type size = distance(first, last);
			_start = _alloc.allocate(size);
			_end_capacity = _start + size;
			_end = _start;
			while (size > 0) {
				_alloc.construct(_end, *first);
				*first++;
				_end++;
				size--;
			}
		}

		vector (const vector &x): _alloc(x._alloc), _start(u_nullptr), _end(u_nullptr), _end_capacity(u_nullptr) {
			this->insert(this->begin(), x.begin(), x.end());
		}

		~vector() {
			this->clear();
			_alloc.deallocate(_start, this->capacity());
		}

		vector	&operator = (const vector &other) {
			if (other == *this) {
				return *this;
			}
			this->clear();
			this->insert(this->end(), other.begin(), other.end());
			return *this;
		}

		// Iterators
		iterator begin() {
			return _start;
		}

		iterator end() {
			if (this->empty()) {
				return this->begin();
			} else {
				return _end;
			}
		}

		reverse_iterator rbegin() {
			return reverse_iterator(this->end());
		}

		reverse_iterator rend() {
			return reverse_iterator(this->begin());
		}

		const_iterator	begin() const {
			return _start;
		}

		const_iterator	end() const {
			if (this->empty()) {
				return this->begin();
			} else {
				return _end;
			}
		}

		const_reverse_iterator rbegin() const {
			return reverse_iterator(this->end());
		}

		const_reverse_iterator rend() const {
			return reverse_iterator(this->begin());
		}

		// Capacity
		size_type size() const {
			return this->_end - this->_start;
		}

		size_type max_size() const {
			return allocator_type().max_size();
		}

		void resize(size_type count, T value = T()) {
			if (count > this->max_size()) {
				throw (std::length_error("vector::resize"));
			} else if (count < this->size()) {
				while (this->size() > count) {
					_alloc.destroy(_end);
					_end--;
				}
			} else {
				this->insert(this->end(), count - this->size(), value);
			}
		}

		size_type capacity() const {
			return this->_end_capacity - this->_start;
		}

		bool empty() const {
			return size() == 0;
		}

		void reserve(size_type new_capacity) {
			if (new_capacity > this->max_size()) {
				throw (std::length_error("vector::reserve"));
			} else if (new_capacity > this->capacity()) {
				pointer prev_start = _start;
				pointer prev_end = _end;
				size_type prev_size = this->size();
				size_type prev_capacity = this->capacity();

				_start = _alloc.allocate(new_capacity);
				_end_capacity = _start + new_capacity;
				_end = _start;
				while (prev_start != prev_end) {
					_alloc.construct(_end, *prev_start);
					_end++;
					prev_start++;
				}
				_alloc.deallocate(prev_start - prev_size, prev_capacity);
			}
		}

		// Element access
		reference operator [] (size_type pos) {
			return *(_start + pos);
		}

		const_reference operator [] (size_type pos) const {
			return *(_start + pos);
		}

		reference at(size_type pos) {
			checkRange(pos);
			return (*this)[pos];
		}

		const_reference at(size_type pos) const {
			checkRange(pos);
			return (*this)[pos];
		}

		reference front() {
			return *_start;
		}

		const_reference front() const {
			return *_start;
		}

		reference back() {
			return *(_end - 1);
		}

		const_reference back() const {
			return *(_end - 1);
		}

		T 		*data();
		const T	*data() const;

		// Modifiers
		template<class T, class Allocator>
		void vector<T, Allocator>::assign(size_type count, const T &value) {
			T *tmp	= _alloc.allocate(count);
			size_type i = 0;

			try {
				for (; i < count; ++i)
					_alloc.construct(tmp + i, value);
			} catch (...) {
				for (; i > 0; --i)
					_alloc.destroy(tmp + i - 1);
				_alloc.deallocate(tmp, count);
				throw ;
			}

			for (i = 0; i < _size; ++i)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
			_data = tmp;
			_size = count;
			_capacity = count;
		}

		template <class T, class Allocator>
		template < class InputIt >
		void vector<T, Allocator>::assign(typename ft::enable_if<!ft::is_integral<InputIt>::value,
				InputIt>::type first, InputIt last) {
			difference_type	diff = ft::distance(first, last);
			T*				tmp = _alloc.allocate(diff);
			size_type		i = 0;

			try
			{
				for (; first != last; ++first, ++i)
					_alloc.construct(tmp + i, *first);
			}
			catch (...)
			{
				for (; i > 0; --i)
					_alloc.destroy(tmp + i - 1);
				_alloc.deallocate(tmp, diff);
				throw ;
			}

			for (i = 0; i < _size; ++i)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
			_data = tmp;
			_size = diff;
			_capacity = diff;
		}


		void push_back(const T &value) {
			 if (_end == _end_capacity) {
				 int next_capacity = 1;
				 if (this->size() > 0) {
					 next_capacity = this->size() * 2;
				 }
				 this->reserve(next_capacity);
			 }
			 _alloc.construct(_end, value);
			 _end++;
		 }

		void pop_back() {
			_alloc.destroy(&this->back());
			_end--;
		}

		iterator insert(iterator pos, const T &value) {
			size_type pos_len = &(*pos) - _start;
			if (size_type(_end_capacity - _end) >= this->size() + 1) {
				for (size_type i = 0; i < pos_len; i++) {
					_alloc.construct(_end - i, *(_end - i - 1));
				}
				_end++;
				_alloc.construct(&(*pos), value);
			} else {
				pointer new_start = pointer();
				pointer new_end = pointer();
				pointer new_end_capacity = pointer();

				int next_capacity = 1;
				if (this->size() > 0) {
					next_capacity = this->size() * 2;
				}
				new_start = _alloc.allocate(next_capacity);
				new_end = new_start + this->size() + 1;
				new_end_capacity = new_start + next_capacity;

				for (size_type i = 0; i < pos_len; i++) {
					_alloc.construct(new_start + i, *(_start + i));
				}
				_alloc.construct(new_start + pos_len, value);
				for (size_type i = 0; i < this->size() - pos_len; i++) {
					_alloc.construct(new_end - i - 1, *(_end - i - 1));
				}

				for (size_type i = 0; i < this->size(); i++) {
					_alloc.destroy(_start + i);
				}
				if (_start) {
					_alloc.deallocate(_start, this->capacity());
				}

				_start = new_start;
				_end = new_end;
				_end_capacity = new_end_capacity;
			}
			return iterator(_start + pos_len);
		}

		void insert(iterator pos, size_type count, const T &value) {
			if (count == 0) {
				return;
			}
			if (count > this->max_size()) {
				throw std::length_error("vector::insert (fill)");
			}
			size_type pos_len = &(*pos) - _start;
			if (size_type(_end_capacity - _end) >= count) {
				for (size_type i = 0; i < this->size() - pos_len; i++) {
					_alloc.construct(_end - i + (count - 1), *(_end - i - 1));
				}
				_end += count;
				while (count) {
					_alloc.construct(&(*pos) + (count - 1), value);
					count--;
				}
			} else {
				pointer new_start = pointer();
				pointer new_end = pointer();
				pointer new_end_capacity = pointer();

				int next_capacity = 1;
				if (this->capacity() > 0) {
					next_capacity = this->size() * 2;
				}
				new_start = _alloc.allocate(next_capacity);
				new_end_capacity = new_start + next_capacity;

				if (new_end_capacity - new_start < this->size() + count) {
					if (new_start) {
						_alloc.deallocate(new_start, new_start - new_end_capacity);
					}
					next_capacity = this->size() + count;
					new_start = _alloc.allocate(next_capacity);
					new_end = new_start + this->size() + count;
					new_end_capacity = new_start + next_capacity;
				}

				new_end = new_start + this->size() + count;

				for (int i = 0; i < (&(*pos) - _start); i++) {
					_alloc.construct(new_start + i, *(_start + i));
				}
				for (size_type i = 0; i < count; i++) {
					_alloc.construct(new_start + pos_len + i, value);
				}
				for (size_type i = 0; i < (this->size() - pos_len); i++) {
					_alloc.construct(new_end - i - 1, *(_end - i - 1));
				}
				for (size_type i = 0; i < this->size(); i++) {
					_alloc.destroy(_start + i);
				}
				_alloc.deallocate(_start, this->capacity());

				_start = new_start;
				_end = new_end;
				_end_capacity = new_end_capacity;
			}
		}

		template <class InputIterator>
		void insert (iterator pos, InputIterator first, InputIterator last,
					 typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) {
			bool is_valid;
			if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value)) {
				throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
			}

			size_type dist = distance(first, last);
			if (size_type(_end_capacity - _end) >= dist) {
				for(size_type i = 0; i < this->size() - (&(*pos) - _start); i++) {
					_alloc.construct(_end - i + (dist - 1), *(_end - i - 1));
				}
				_end += dist;
				while (&(*first) != &(*last)) {
					_alloc.construct(&(*pos), *first);
					first++;
					pos++;
				}
			} else {
				pointer new_start = pointer();
				pointer new_end = pointer();
				pointer new_end_capacity = pointer();

				new_start = _alloc.allocate(this->size() * 2);
				new_end = new_start + this->size() + dist;
				new_end_capacity = new_start + (this->size() * 2);

				if (new_end_capacity - new_start < this->size() + dist) {
					if (new_start) {
						_alloc.deallocate(new_start, new_end_capacity - new_start);
					}
					new_start = _alloc.allocate (this->size() + dist);
					new_end = new_start + this->size() + dist;
					new_end_capacity = new_end;
				}

				for (int i = 0; i < &(*pos) - _start; i++) {
					_alloc.construct(new_start + i, *(_start + i));
				}
				for (int i = 0; &(*first) != &(*last); i++) {
					_alloc.construct(new_start + (&(*pos) - _start) + i, *first);
					first++;
				}
				for (size_type i = 0; i < this->size() - (&(*pos) - _start); i++) {
					_alloc.construct(new_start + (&(*pos) - _start) + dist + i, *(_start + (&(*pos) - _start) + i));
				}

				for (size_type i = 0; i < this->size(); i++) {
					_alloc.destroy(_start + i);
				}
				_alloc.deallocate(_start, this->capacity());

				_start = new_start;
				_end = new_end;
				_end_capacity = new_end_capacity;
			}
		}

		iterator erase(iterator pos) {
			pointer p_pos = &(*pos);
			_alloc.destroy(&(*pos));
			if (&(*pos) + 1 == _end) {
				_alloc.destroy(&(*pos));
			} else {
				for (int i = 0; i < _end - &(*pos) - 1; i++) {
					_alloc.construct(&(*pos) + i, *(&(*pos) + i + 1));
					_alloc.destroy(&(*pos) + i + 1);
				}
			}
			_end--;
			return iterator(p_pos);
		}

		iterator erase(iterator first, iterator last) {
			pointer p_first = &(*first);
			while (&(*first) != &(*last)) {
				_alloc.destroy(&(*first));
				first++;
			}
			for (int i = 0; i < _end - &(*last); i++) {
				_alloc.construct(p_first + i, *(&(*last) + i));
				_alloc.destroy(&(*last) + i);
			}
			_end -= (&(*last) - p_first);
			return iterator(p_first);
		}

		void swap(vector &other) {
			if (other == *this) {
				return;
			}

			pointer save_start = other._start;
			pointer save_end = other._end;
			pointer save_end_capacity = other._end_capacity;
			allocator_type save_alloc = other._alloc;

			other._start = this->_start;
			other._end = this->_end;
			other._end_capacity = this->_end_capacity;
			other._alloc = this->_alloc;

			this->_start = save_start;
			this->_end = save_end;
			this->_end_capacity = save_end_capacity;
			this->_alloc = save_alloc;
		}

		void clear() {
			int save_size = this->size();
			for (int i = 0; i < save_size; i++) {
				_end--;
				_alloc.destroy(_end);
			}
		}

		// Allocator
		allocator_type get_allocator() const;

	private:
		allocator_type  _alloc;
		pointer         _start;
		pointer         _end;
		pointer         _end_capacity;

		void checkRange(const size_type &count) const {
			if (count >= this->size()) {
				throw (std::out_of_range("vector::checkRange: count (which is "
										 + to_string(count) + ") >= this->size() (which is "
										 + to_string(this->size()) + ")"));
			}
		}
	};

	// Non-member function

	template <class T, class Allocator>
	bool operator == (const ft::vector<T, Allocator> &a, const ft::vector<T, Allocator> &b) {
		if (a.size() != b.size()) {
			return false;
		}
		typename ft::vector<T>::const_iterator first1 = a.begin();
		typename ft::vector<T>::const_iterator first2 = b.begin();
		while (first1 != a.end()) {
			if (first2 == b.end() || *first1 != *first2) {
				return false;
			}
			first1++;
			first2++;
		}
		return true;
	}

	template <class T, class Allocator>
	bool operator != (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return !(a == b);
	}

	template <class T, class Allocator>
	bool operator < (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	template <class T, class Allocator>
	bool operator <= (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return !(b < a);
	}

	template <class T, class Allocator>
	bool operator >  (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return b < a;
	}

	template <class T, class Allocator>
	bool operator >= (const vector<T, Allocator> &a, const vector<T, Allocator> &b) {
		return !(a < b);
	}

	template <class T, class Allocator>
	void swap(vector<T,Allocator> &a, vector<T,Allocator> &b) {
		a.swap(b);
	}
}

#endif