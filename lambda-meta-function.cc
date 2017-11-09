#include <iostream>


template<struct X>
struct add_pointer {
	struct apply {
		typedef X * type;
	};
};
