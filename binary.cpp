#include <iostream>

template<unsigned n>
struct Binary : std::integral_constant<unsigned, Binary<n / 10>::value * 2 + n % 10> {};

template<>
struct Binary<0> : std::integral_constant<unsigned, 0> {};

template<>
struct Binary<1> : std::integral_constant<unsigned, 1> {};


int main() {
	std::cout << Binary<1010011>::value << std::endl;
	std::cout << Binary<11010011>::value << std::endl;
	std::cout << Binary<11>::value << std::endl;
	return 0;
}
