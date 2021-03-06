#include <iostream>

#include "traits.h"

#include <type_traits>

class A { };
struct B { };
union C { };

int main() {
	static_assert(traits::is_class<A>::value, "");;
	static_assert(traits::is_class<B>::value, "");;
	static_assert(traits::is_class<C>::value, "");;
	static_assert(!traits::is_class<int>::value, "");;


#define print(...) std::cout << #__VA_ARGS__ << ":\t" << (__VA_ARGS__) << std::endl
	int p1[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}};
	print(traits::format<std::decay<decltype(p1)>::type>::to_string());
	std::cout << "============== is_same ==============\n";
	print(traits::is_same<int, int>::value);
	print(traits::is_same<int, int>::value);
	print(traits::is_same<float, int>::value);
	print(traits::is_same<float, float>::value);

	std::cout << "============== is_integral ==============\n";
	print(traits::is_integral<float>::value);
	print(traits::is_integral<int>::value);
	print(traits::is_integral<unsigned int>::value);
	print(traits::is_integral<unsigned short>::value);
	print(traits::is_integral<unsigned long long int>::value);
	print(traits::is_integral<int>::value);
	print(traits::is_integral<int>::value);

	std::cout << "============== is_float ==============\n";
	print(traits::is_float<float>::value);
	print(traits::is_float<int>::value);

	std::cout << "============== is_array ==============\n";
	print(traits::is_array<int [2]>::value);
	print(traits::is_array<float [3]>::value);

	std::cout << "============== is_pointer ==============\n";
	print(traits::is_pointer<int*>::value);
	print(traits::is_pointer<float*>::value);
	print(traits::is_pointer<int>::value);
	print(traits::is_pointer<float>::value);

	std::cout << "============== is_void ==============\n";
	print(traits::is_void<void>::value);
	print(traits::is_void<int>::value);

	return 0;

#undef print
}
