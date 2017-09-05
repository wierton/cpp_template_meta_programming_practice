#include <iostream>

#include "traits.h"


int main() {
#define print(...) std::cout << #__VA_ARGS__ << ":\t" << (__VA_ARGS__) << std::endl
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
