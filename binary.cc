#include <iostream>

template<unsigned n>
struct Binary : std::integral_constant<unsigned, Binary<n / 10>::value * 2 + n % 10> {};

template<>
struct Binary<0> : std::integral_constant<unsigned, 0> {};

template<>
struct Binary<1> : std::integral_constant<unsigned, 1> {};


int main() {
	std::cout << Binary<0>::value << std::endl;
	std::cout << Binary<1>::value << std::endl;
	std::cout << Binary<10>::value << std::endl;
	std::cout << Binary<11>::value << std::endl;
	std::cout << Binary<100>::value << std::endl;
	std::cout << Binary<101>::value << std::endl;
	std::cout << Binary<110>::value << std::endl;
	std::cout << Binary<111>::value << std::endl;
	std::cout << Binary<1000>::value << std::endl;
	std::cout << Binary<1010011>::value << std::endl;
	std::cout << Binary<11010011>::value << std::endl;
	return 0;
}
