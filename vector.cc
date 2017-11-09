#include <iostream>
#include <assert.h>
#include <algorithm>


template<class... Args>
void print(Args... args) {
	std::initializer_list<int> {(std::cout << args << " ", 0)...};
}

template<class... Args>
void println(Args... args) {
	print(args...);
	std::cout << std::endl;
}

template<typename T>
class Vector {
	T *array;
	std::size_t numOfArrayElements;
	std::size_t capacity;
public:
	enum Exception {
		ExceptionPopFromNullArray,
		ExceptionOutOfRange,
	};

	Vector();
	~Vector() noexcept;
	Vector(std::initializer_list<T> initializer) ;
	Vector(Vector &v);
	Vector(Vector &&v);
	Vector &operator=(std::initializer_list<T> initializer) noexcept;
	Vector &operator=(Vector &v) noexcept;
	Vector &operator=(Vector &&v) noexcept;
	void pushBack(T e);
	void popBack() throw(enum Exception);
	Vector<T>& lastElement() throw(enum Exception);
	T& operator[](std::size_t index) throw(enum Exception) ;
	std::size_t size(); 
};

template<class T> Vector<T>::Vector() {
	numOfArrayElements = 0;
	capacity = 42;
	array = new T[capacity];
}

template<class T> Vector<T>::~Vector() noexcept {
	std::cout << "called destructor\n";
	delete []array;
	numOfArrayElements = 0;
	capacity = 0;
}

template<class T> Vector<T>::Vector(std::initializer_list<T> initializer) {
	capacity = initializer.size();
	array = new T[initializer.size()];
	numOfArrayElements = 0;

	//for(auto val:initializer)
	//	pushBack(val);

	std::for_each(initializer.begin(), initializer.end(), [this](const int &val) { this->pushBack(val); });
}

template<class T> Vector<T>::Vector(Vector &v) {
	array = new T[v.numOfArrayElements];
	numOfArrayElements = v.numOfArrayElements;

	for(int i = 0; i < numOfArrayElements; i++) {
		array[i] = v.array[i];
	}
}

template<class T> Vector<T>::Vector(Vector &&v) {
	array = v.array;
	numOfArrayElements = v.numOfArrayElements;
	capacity = v.capacity;

	v.array = nullptr;
	v.numOfArrayElements = 0;
	v.capacity = 0;
}

template<class T> Vector<T>& Vector<T>::operator=(std::initializer_list<T> initializer) noexcept {
	delete []array;

	capacity = initializer.size();
	array = new T[initializer.size()];
	numOfArrayElements = 0;

	std::for_each(initializer.begin(), initializer.end(), [this](const int &val) { this->pushBack(val); });
	return *this;
}

template<class T> Vector<T>& Vector<T>::operator=(Vector &v) noexcept {
	delete []array;

	std::cout << "swap by copy\n";

	array = new T[v.numOfArrayElements];
	numOfArrayElements = v.numOfArrayElements;

	for(int i = 0; i < numOfArrayElements; i++) {
		array[i] = v.array[i];
	}
}

template<class T> Vector<T>& Vector<T>::operator=(Vector &&v) noexcept {
	delete []array;

	std::cout << "swap pointer\n";

	array = v.array;
	numOfArrayElements = v.numOfArrayElements;
	capacity = v.capacity;

	v.array = nullptr;
	v.numOfArrayElements = 0;
	v.capacity = 0;
}

template<class T> void Vector<T>::pushBack(T e) {
	if(__builtin_expect(numOfArrayElements < capacity, 1)) {
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

template<class T> void Vector<T>::popBack() throw(enum Exception) {
	if(numOfArrayElements <= 0)
		throw ExceptionPopFromNullArray;
	numOfArrayElements --;
}

template<class T> Vector<T>& Vector<T>::lastElement() throw(enum Exception) {
	if(numOfArrayElements <= 0)
		throw ExceptionPopFromNullArray;
	return this->array[this->numOfArrayElements - 1];
}

template<class T> T& Vector<T>::operator[](std::size_t index) throw(enum Exception) {
	if(index >= numOfArrayElements)
		throw ExceptionOutOfRange;
	return array[index];
}

template<class T> std::size_t Vector<T>::size() {
	return numOfArrayElements;
}

int main() {
	Vector<int> v1 = {0, 1, 2, 3, 4, 5};

	for(int i = 6; i < 65536; i++)
		v1.pushBack(i);
	for(int i = 0; i < 65536; i++)
		assert(v1[i] == i);

	for(int i = 0; i < 65536; i++)
		v1.popBack();

	try {
		v1.popBack();
	} catch(Vector<int>::Exception e) {
		println("caught exception by popping from null array");
	}

	try {
		v1[0] = 0;
	} catch(Vector<int>::Exception e) {
		println("caught exception by access index out of range");
	}

	/* test swap by pointer */
	v1 = {1, 2, 3, 4, 5};
	Vector<int> v2 = {5, 4, 3, 2, 1};

	Vector<int> tmp1 = std::move(v1);
	v1 = std::move(v2);
	v2 = std::move(tmp1);

	println("first element of two vectors: ", "v1[0]=", v1[0], ", v2[0]=", v2[0]);

	/* test swap by copy */
	v1 = {1, 2, 3, 4, 5};
	v2 = {5, 4, 3, 2, 1};

	Vector<int> tmp2 = v1;
	v1 = v2;
	v2 = tmp2;

	println("first element of two vectors: ", "v1[0]=", v1[0], ", v2[0]=", v2[0]);

	return 0;
}
