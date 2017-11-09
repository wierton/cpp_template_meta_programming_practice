#include <iostream>


template<class... Args>
struct Sum;

template<class Last>
struct Sum<Last> {
	enum { size = sizeof(Last) };
};

template<class First, class... Rest>
struct Sum<First, Rest...> {
	enum { size = Sum<First>::size + Sum<Rest...>::size };
};


int main() {
	std::cout << Sum<int>::size << std::endl;
	// std::cout << Sum<int, double>::size << std::endl;
	// std::cout << Sum<int, "">::size << std::endl;
	return 0;
}
