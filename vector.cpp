#include <iostream>
#include <assert.h>
#include <algorithm>


template<typename T>
class Vector {
	T *array;
	uint32_t numOfArrayElements;
	std::size_t capacity;
public:
	enum Exception {
		ExceptionPopFromNullArray,
		ExceptionOutOfRange,
	};

	Vector() {
		numOfArrayElements = 0;
		capacity = 42;
		array = new T[capacity];
	}

	Vector(std::initializer_list<T> initializer) {
		capacity = initializer.size();
		array = new T[initializer.size()];
		numOfArrayElements = 0;

		//for(auto val:initializer)
		//	pushBack(val);

		std::for_each(initializer.begin(), initializer.end(), [this](const int &val) { this->pushBack(val); });
	}

	void pushBack(T e) {
		if(numOfArrayElements < capacity) {
			array[numOfArrayElements] = e;
			numOfArrayElements ++;
		} else {
			capacity *= 2;
			T *new_array = new T[capacity * 2];
			for(int i = 0; i < capacity; i++)
				new_array[i] = array[i];
			new_array[numOfArrayElements] = e;
			numOfArrayElements ++;

			delete []array;
			array = new_array;
		}
	}

	void popBack() throw(enum Exception) {
		if(numOfArrayElements <= 0)
			throw ExceptionPopFromNullArray;
		numOfArrayElements --;
	}

	T& operator[](std::size_t index) throw(enum Exception) {
		if(index >= numOfArrayElements)
			throw ExceptionOutOfRange;
		return array[index];
	}

	std::size_t size() noexcept {
		return numOfArrayElements;
	}
};

int main() {
	Vector<int> v = {0, 1, 2, 3, 4, 5};

	for(int i = 6; i < 65536; i++)
		v.pushBack(i);
	for(int i = 0; i < 65536; i++)
		assert(v[i] == i);

	for(int i = 0; i < 65536; i++)
		v.popBack();

	try {
		v.popBack();
	} catch(Vector<int>::Exception e) {
		std::cout << e << "\n";
	}

	try {
		v[0] = 0;
	} catch(Vector<int>::Exception e) {
		std::cout << e << "\n";
	}

	return 0;
}
