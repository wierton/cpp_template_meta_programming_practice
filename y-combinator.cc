#include <iostream>


int main() {
	/*
	auto fact = [](int n) -> int {
		return n > 0 ? n * fact(n - 1) : 1;
	};
	*/

	auto fact = [](auto f, int n) -> int {
		return n > 0 ? n * f(f, n - 1) : 1;
	};

	std::cout << fact(fact, 5) << std::endl;

	return 0;
}
