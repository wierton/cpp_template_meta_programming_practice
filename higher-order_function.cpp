#include <iostream>

#include "traits.h"

template<class T>
struct F {
	static void apply(T arg) {
		std::cout << "apply to " << traits::type_descriptor<T>::formatToString() << std::endl;
	}
};
