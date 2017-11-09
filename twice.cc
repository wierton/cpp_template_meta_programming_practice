#include <iostream>



template<class F, class X>
struct twice {
	typedef typename F<x>::type once;
	typedef once<X>::type type;
};
