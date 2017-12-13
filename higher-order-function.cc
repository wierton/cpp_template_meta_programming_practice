#include <iostream>
#include <utility>

#include "traits.h"


template<class F, class X>
struct twice {
	using once = typename F::template apply<X>::type;
	using type = typename F::template apply<once>::type;
};

struct add_pointer {
	template<class T>
	struct apply {
		using type = T *;
	};
};


template<class F, class X>
struct apply : F::template apply<X> {};

template<class F, class X>
struct twice2 : apply<F, typename apply<F, X>::type> {};


template<class X>
struct two_pointers
: twice<typename mpl::lambda<boost::add_pointer<_1>>::type, X> {};



int main() {
	static_assert(std::is_same<twice<add_pointer, int>::type, int**>::value, "");
	return 0;
}
