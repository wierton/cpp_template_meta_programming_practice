#include <iostream>


template<typename T>
bool compare(T a, T b) {
	std::cout << "call compare<T>: ";
	return a < b;
}

template<typename T, typename U>
bool compare(T a, U b) {
	std::cout << "call compare<T, U>: ";
	return a < b;
}

int main() {
	std::cout << compare(1, 2) << std::endl;
	std::cout << compare(1.5, 0.2) << std::endl;
	std::cout << compare<int, double>(1, 2) << std::endl;
	std::cout << compare<double, int>(1.5, 0.2) << std::endl;
	std::cout << compare(1.5, 2) << std::endl;
	std::cout << compare(2, 1.5) << std::endl;
	return 0;
}
