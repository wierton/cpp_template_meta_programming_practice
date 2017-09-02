#include <iostream>


template<unsigned n> struct Fib : std::integral_constant<unsigned, Fib<n - 1>::value + Fib<n - 2>::value> {};

template<> struct Fib<1> : std::integral_constant<unsigned, 1> {};

template <> struct Fib<0> : std::integral_constant<unsigned, 1> {};


int main() {
	std::cout << Fib<200>::value << std::endl;
	return 0;
}
