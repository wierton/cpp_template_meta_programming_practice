#include <iostream>

#include "traits.h"

int main() {
#define print(...) std::cout << #__VA_ARGS__ << ":\t" << (__VA_ARGS__) << std::endl
	print(traits::format<decltype(nullptr)>::to_string());
	return 0;
}
