#include <iostream>
#include <random>
#include <tuple>

#include "traits.h"

template<class T, size_t N>
struct TensorType {
        using type = std::vector<typename TensorType<T, N-1>::type>;
};

template<class T>
struct TensorType<T, 0> {
        using type = T;
};

template<class T, size_t N>
using Tensor = typename TensorType<T, N>::type;

template<class T>
T operator+(const T &a, const T &b) {
    auto ret = a;
    for(auto itl = ret.begin(), itr = b.begin();
        itl < ret.end() && itr < b.end();
        itl ++, itr ++)
        *itl = *itl + *itr;
    return ret;
}

class A {};

int main() {
	A a, b;
	a + b;
	return 0;
}
