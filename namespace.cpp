#include <iostream>
namespace name {
	extern int variable;
};


namespace name {
	int variable = 1;
};



int main() {
	std::cout << name::variable << std::endl;
	return 0;
}
