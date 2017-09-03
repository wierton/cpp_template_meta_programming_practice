#include <iostream>

template<class T1, class T2>
struct is_same : std::integral_constant<bool, false> { };

template<class T>
struct is_same<T, T> : std::integral_constant<bool, true> { };


template<class T>
struct is_integral {
	static constexpr bool value = 
		is_same<T, char>::value
		|| is_same<T, short>::value
		|| is_same<T, long>::value
		|| is_same<T, int>::value
		|| is_same<T, long long>::value
		|| is_same<T, unsigned char>::value
		|| is_same<T, unsigned short>::value
		|| is_same<T, unsigned long>::value
		|| is_same<T, unsigned int>::value
		|| is_same<T, unsigned long long>::value;
};

template<class T>
struct is_float {
	static constexpr bool value =
		is_same<T, float>::value || is_same<T, double>::value;
};


template<class T>
struct is_array {
	static constexpr bool value = false;
};

template<class T>
struct is_array<T []> {
	static constexpr bool value = true;
};

template<class T>
struct is_void : std::integral_constant<bool, is_same<T, void>::value> {};


template<class T>
struct is_pointer : std::integral_constant<bool, false> { };

template<class T>
struct is_pointer<T*> : std::integral_constant<bool, true> {};

int main() {
#define print(...) std::cout << #__VA_ARGS__ << ":\t" << (__VA_ARGS__) << std::endl
	std::cout << "============== is_same ==============\n";
	print(is_same<int, int>::value);
	print(is_same<int, int>::value);
	print(is_same<float, int>::value);
	print(is_same<float, float>::value);

	std::cout << "============== is_integral ==============\n";
	print(is_integral<float>::value);
	print(is_integral<int>::value);
	print(is_integral<unsigned int>::value);
	print(is_integral<unsigned short>::value);
	print(is_integral<unsigned long long int>::value);
	print(is_integral<int>::value);
	print(is_integral<int>::value);

	std::cout << "============== is_float ==============\n";
	print(is_float<float>::value);
	print(is_float<int>::value);

	std::cout << "============== is_array ==============\n";
	print(is_array<int [2]>::value);
	print(is_array<float [3]>::value);

	std::cout << "============== is_pointer ==============\n";
	print(is_pointer<int*>::value);
	print(is_pointer<float*>::value);
	print(is_pointer<int>::value);
	print(is_pointer<float>::value);

	std::cout << "============== is_void ==============\n";
	print(is_void<void>::value);
	print(is_void<int>::value);

	return 0;

#undef print
}
