#include <iostream>

template<bool cond, class T, class F>
struct IF {
};

template<class T, class F>
struct IF<false, T, F> {
	typedef F retType;
};

template<class T, class F>
struct IF<true, T, F> {
	typedef T retType;
};

template<template<class> class Cond, class Stmt>
struct WHILE {
	template<class Stmt>
	struct STOP {
		typedef Stmt retType;
	};
	
	typedef typename IF<Cond<Stmt>::retType, WHILE<Cond, typename Stmt::NEXT>, typename STOP<Stmt>::retType >::retType retType;
};

template<int n>
class Sum {
};


int main() {
	return 0;
}
