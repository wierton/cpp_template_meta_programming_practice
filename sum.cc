#include <iostream>

template<typename T>
constexpr T sum(T arg) {
	return arg;
}

template<typename T, typename... Args>
constexpr T sum(T p, Args... args) {
	std::cout << "call with " << sizeof...(args) << " elements\n";
	return p + sum(args...);
}


int main() {
	std::cout << "sum is: " << sum(0, 1, 2, 3, 4) << std::endl;
	std::cout << "sum is: " << sum(0., 1., 2., 3., 4.) << std::endl;
	return 0;
}
