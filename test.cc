#include <iostream>
#include <random>

#include "traits.h"

class A {
public:
	A(int a, int b, const char *c) { }
};

int main() {
	A a = {1, 2, "123"};
	return 0;
}
