#include <iostream>


template<class... Args>
void print(Args... args) {
	std::initializer_list<int> {((std::cout<< args << ", "), 0)...};
	std::cout << std::endl;
}


int main() {
	print(1, 2, 3, 4);
	return 0;
}
