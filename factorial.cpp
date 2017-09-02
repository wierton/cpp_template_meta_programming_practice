#include <iostream>

template<unsigned n>
struct Factorial : std::integral_constant<unsigned, n * Factorial<n - 1>::value> {};

template<>
struct Factorial<0> : std::integral_constant<unsigned, 1> {};

template<unsigned n>
struct F2 {
	static unsigned constexpr value = n * F2<n - 1>::value;
};

template<>
struct F2<0> {
	static unsigned constexpr value = 1;
};

template<unsigned n>
struct F3 {
	enum { value = n * F2<n - 1>::value };
};

template<>
struct F3<0> {
	enum { value = 1 };
};

int main() {
	std::cout << Factorial<0>::value << std::endl;
	std::cout << Factorial<1>::value << std::endl;
	std::cout << Factorial<2>::value << std::endl;
	std::cout << Factorial<3>::value << std::endl;
	std::cout << Factorial<4>::value << std::endl;
	std::cout << Factorial<5>::value << std::endl;

	std::cout << F2<0>::value << std::endl;
	std::cout << F2<1>::value << std::endl;
	std::cout << F2<2>::value << std::endl;
	std::cout << F2<3>::value << std::endl;
	std::cout << F2<4>::value << std::endl;
	std::cout << F2<5>::value << std::endl;

	std::cout << F3<0>::value << std::endl;
	std::cout << F3<1>::value << std::endl;
	std::cout << F3<2>::value << std::endl;
	std::cout << F3<3>::value << std::endl;
	std::cout << F3<4>::value << std::endl;
	std::cout << F3<5>::value << std::endl;
	return 0;
}
