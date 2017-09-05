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
	template<class Stmt_>
	struct STOP {
		typedef Stmt retType;
	};
	
	typedef typename IF<Cond<Stmt>::retValue, WHILE<Cond, typename Stmt::NEXT>, typename STOP<Stmt>::retType >::retType retType;
};


/* calculate: sum(n, e) = 1^e + 2^e + ... + n^e, use while-loop */

template<unsigned n, unsigned e>
struct Sum {
	template<unsigned p, unsigned n>
	struct pow : std::integral_constant<unsigned, p * pow<p, n - 1>::value> {};
	template<unsigned p>
	struct pow<p, 0> : std::integral_constant<unsigned, 1> {};

	template<unsigned i>
	struct pow_e {
		static constexpr unsigned value = pow<i, e>::value;
	};

	/* use while-loop */
	template<class Stmt>
	struct Cond {
		static constexpr unsigned retValue = Stmt::i < n;
	};

	template<unsigned i, unsigned sum>
	struct Stmt {
		typedef Stmt<i, sum + pow_e<i>::value>::retType retType;

		static constexpr unsigned ri = i;
		static constexpr unsigned ret = sum;
	};

	static constexpr unsigned value = WHILE<>::value;
};


int main() {
	return 0;
}
