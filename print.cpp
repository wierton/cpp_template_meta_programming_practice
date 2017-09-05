#include <iostream>


template<class... Args>
void print(Args... args) {
	std::initializer_list<int> {(std::cout << args << " ", 0)...};
}

template<class... Args>
void println(Args... args) {
	print(args...);
	std::cout << std::endl;
}


int main() {
	println(1, 2, 3, 4);
	return 0;
}
