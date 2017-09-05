#include <iostream>

template<class... Args>
void print(Args... args) {
	std::initializer_list<int> {(std::cout << args << " ", 0)...};
}

template<class... Args>
void println(Args... args) {
	print(args...);
	std::cout << std::endl;
}

struct TrueType { bool value = true; };
struct FalseType { bool value = false; };

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

/* assume the retType of WHILE is Stmt */
template<template<class> class Cond, class Stmt>
struct WHILE {
	template<class Stmt_>
	struct STOP {
		typedef Stmt_ retType;
	};

	typedef typename IF< Cond<Stmt>::retValue,
		WHILE<Cond, typename Stmt::NEXT>,
		STOP<Stmt>>::retType::retType retType;
};


/* calculate: sum(n, e) = 1^e + 2^e + ... + n^e, use while-loop */

template<unsigned n, unsigned e>
struct Sum {
	template<unsigned p, unsigned n_>
	struct pow : std::integral_constant<unsigned, p * pow<p, n_ - 1>::value> {};
	template<unsigned p>
	struct pow<p, 0> : std::integral_constant<unsigned, 1> {};

	template<unsigned i>
	struct pow_e {
		static constexpr unsigned value = pow<i, e>::value;
	};

	/* use while-loop */
	template<class Stmt>
	struct Cond {
		static constexpr unsigned retValue = Stmt::ri <= n;
	};

	template<unsigned i, unsigned sum>
	struct Stmt {
		typedef Stmt<i + 1, sum + pow_e<i>::value> NEXT;

		static constexpr unsigned ri = i;
		static constexpr unsigned value = sum;
	};

	static constexpr unsigned value = WHILE<Cond, Stmt<1, 0>>::retType::value;
};

/* sum all prime integer in [1, n] */
template<unsigned n>
struct isPrime {
};

int main() {
	/* sum(n, e) = 1^e + 2^e + ... + n^e, use while-loop */
	std::cout << Sum<4, 2>::value << std::endl;
	return 0;
}
