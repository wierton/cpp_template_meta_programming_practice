#include <iostream>

#include "traits.h"


/*
struct add_pointer {
	template<class X>
	struct apply {
		typedef X * type;
	};
};

template<class F, class X>
struct twice {
	typedef typename F::template apply<X>::type once;
	typedef typename F::template apply<once>::type type;
};
*/

template<class T>
struct add_pointer {
	typedef T * type;
};

template<template <class> class F, class X>
struct twice {
	typedef typename F<X>::type once;
	typedef typename F<once>::type type;
};

template<unsigned N, template <class> class F, class X>
struct times {
	typedef typename times<N - 1, F, X>::type type;
};

template<template <class> class F, class X>
struct times<1, F, X> {
	typedef typename F<X>::type type;
};


int main() {
	// static_assert(traits::is_same<twice<add_pointer, int>::type, int**>::value, "");
	static_assert(traits::is_same<twice<add_pointer, int>::type, int**>::value, "");
	return 0;
}
