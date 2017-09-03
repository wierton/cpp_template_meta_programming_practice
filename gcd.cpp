#include <iostream>


template<int m, int n>
struct GCD : std::integral_constant<int, GCD<n, m % n>::value> { };

template<int m>
struct GCD<m, 0> : std::integral_constant<int, m> { };

int main() {
	std::cout << GCD<1, 2>::value << std::endl;
	std::cout << GCD<11, 2>::value << std::endl;
	std::cout << GCD<1, 20>::value << std::endl;
	std::cout << GCD<6, 2>::value << std::endl;
	std::cout << GCD<7, 2>::value << std::endl;
	std::cout << GCD<14, 14>::value << std::endl;
	std::cout << GCD<28, 14>::value << std::endl;
	std::cout << GCD<60, 120>::value << std::endl;
	return 0;
}
