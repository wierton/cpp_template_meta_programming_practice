#include <iostream>


int main() {
	/*
	auto fact = [](int n) -> int {
		return n > 0 ? n * fact(n - 1) : 1;
	};
	*/

	auto F1 = [](auto f, int n) -> int {
		return n > 0 ? n * f(f, n - 1) : 1;
	};

	auto F2 = [](auto f) -> decltype(auto) {
		return [&f](int n) -> int {
			return n > 0 ? n * f(f)(n - 1) : 1;
		};
	};

	std::cout << F1(F1, 5) << std::endl;
	std::cout << F2(F2)(5) << std::endl;

	return 0;
}
