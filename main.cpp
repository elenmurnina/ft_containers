#include <iostream>
#include <vector>

#include "vector.hpp"

template<class T>
static void print_vector(const ft::vector<T> &v) {
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl << std::endl;
}

static void vector_test() {
	clock_t vector_start = clock();

	ft::vector<int> v1(0);
	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 empty: " << (v1.empty() == 1 ? "true" : "false") << std::endl << std::endl;

	for (int i = 0; i < 16; i++) {
		v1.push_back(i * 2);
	}
	std::cout << "v1: ";
	print_vector(v1);

	ft::vector<int>::iterator a = v1.begin();
	while (a != v1.end()) {
		*a /= 2;
		a++;
	}
	std::cout << "v1 / 2 : ";
	print_vector(v1);

	ft::vector<int>::reverse_iterator b = v1.rbegin();
	std::cout << "v1 reverse_iterator: ";
	while (b != v1.rend()) {
		std::cout << *b << " ";
		b++;
	}
	std::cout << std::endl << std::endl;

	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 empty: " << (v1.empty() == 1 ? "true" : "false") << std::endl << std::endl;


	ft::vector<int> v2(v1.rbegin(), v1.rend());
	std::cout << "v2 (reversed v1): ";
	print_vector(v2);

	std::cout << "v1[4]: " << v1.at(4) << std::endl;
	try {
		std::cout << "v1[20]: " << v1.at(20) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "v1[4]: " << v1[4] << std::endl;
	std::cout << "v1 front: " << v1.front() << std::endl;
	std::cout << "v1 back: " << v1.back() << std::endl;
	std::cout << "v1 data: " << *v1.data() << std::endl << std::endl;

	v1.clear();
	std::cout << "v1 empty after clear: " << (v1.empty() == 1 ? "true" : "false") << std::endl;

	v1.insert(v1.begin(), v2.begin() + 5, v2.end());
	std::cout << "v1 insert from v2: ";
	print_vector(v1);

	v1.erase(v1.begin() + 1);
	std::cout << "v1 after erasing 1 element: ";
	print_vector(v1);

	v1.push_back(100);
	std::cout << "v1 push_back 100: ";
	print_vector(v1);
	v1.pop_back();
	std::cout << "v1 pop_back: ";
	print_vector(v1);

	v1.resize(20, 0);
	std::cout << "v1 after resizing to 20: ";
	print_vector(v1);

	std::cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << std::endl;
	std::cout << "v1 < v2: " << (v1 < v2 ? "true" : "false") << std::endl;

	std::vector<int> p;
	for (int i = 0; i < 100000; i++) {
		p.push_back(i);
	}

	clock_t vector_end = clock();
	printf("Execution time for my vector: %.2fms\n",
		   (double) (vector_end - vector_start) / CLOCKS_PER_SEC * 1000);
}

template<class T>
static void print_stl_vector(const std::vector <T> &v) {
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl << std::endl;
}

static void stl_vector_test() {
	clock_t vector_start = clock();

	std::vector<int> v1;
	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 empty: " << (v1.empty() == 1 ? "true" : "false") << std::endl << std::endl;

	for (int i = 0; i < 16; i++) {
		v1.push_back(i * 2);
	}
	std::cout << "v1: ";
	print_stl_vector(v1);

	std::vector<int>::iterator a = v1.begin();
	for (; a != v1.end(); a++) {
		*a /= 2;
	}
	std::cout << "v1 / 2 : ";
	print_stl_vector(v1);

	std::vector<int>::reverse_iterator b = v1.rbegin();
	std::cout << "v1 reverse_iterator: ";
	for (; b != v1.rend(); b++) {
		std::cout << *b << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 empty: " << (v1.empty() == 1 ? "true" : "false") << std::endl << std::endl;


	std::vector<int> v2(v1.rbegin(), v1.rend());
	std::cout << "v2 (reversed v1): ";
	print_stl_vector(v2);

	std::cout << "v1[4]: " << v1.at(4) << std::endl;
	try {
		std::cout << "v1[20]: " << v1.at(20) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "v1[4]: " << v1[4] << std::endl;
	std::cout << "v1 front: " << v1.front() << std::endl;
	std::cout << "v1 back: " << v1.back() << std::endl;
	std::cout << "v1 data: " << *v1.data() << std::endl << std::endl;

	v1.clear();
	std::cout << "v1 empty after clear: " << (v1.empty() == 1 ? "true" : "false") << std::endl;

	v1.insert(v1.begin(), v2.begin() + 5, v2.end());
	std::cout << "v1 insert from v2: ";
	print_stl_vector(v1);

	v1.erase(v1.begin() + 1);
	std::cout << "v1 after erasing 1 element: ";
	print_stl_vector(v1);

	v1.push_back(100);
	std::cout << "v1 push_back 100: ";
	print_stl_vector(v1);
	v1.pop_back();
	std::cout << "v1 pop_back: ";
	print_stl_vector(v1);

	v1.resize(20, 0);
	std::cout << "v1 after resizing to 20: ";
	print_stl_vector(v1);

	std::cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << std::endl;
	std::cout << "v1 < v2: " << (v1 < v2 ? "true" : "false") << std::endl;

	std::vector<int> p;
	for (int i = 0; i < 100000; i++) {
		p.push_back(i);
	}

	clock_t vector_end = clock();
	printf("Execution time for stl vector: %.2fms\n",
		   (double) (vector_end - vector_start) / CLOCKS_PER_SEC * 1000);
}

int main() {
	std::cout << "----- VECTOR TEST -----\n" << std::endl;
	vector_test();
	std::cout << std::endl << std::endl;

	std::cout << "----- STL VECTOR TEST -----\n" << std::endl;
	stl_vector_test();
	std::cout << std::endl << std::endl;
}