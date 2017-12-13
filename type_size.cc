#include <iostream>


template<class First, class... Rest>
struct Sum {
	enum { size = Sum<First>::size + Sum<Rest...>::size };
};

template<class Last>
struct Sum<Last> {
	enum { size = sizeof(Last) };
};


int main() {
	std::cout << Sum<int>::size << std::endl;
	// std::cout << Sum<int, double>::size << std::endl;
	// std::cout << Sum<int, "">::size << std::endl;
	return 0;
}
