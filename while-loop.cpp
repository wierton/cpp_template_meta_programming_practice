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

typedef std::__bool_constant<true> TrueType;
typedef std::__bool_constant<false> FalseType;

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



/* calculate: sum(n, e) = 1^e + 2^e + ... + n^e, use while-loop */

template<int n, int e>
struct Sum {
	/* assume the retType of WHILE is Stmt */
	template<template<class> class Cond, class Stmt>
	struct WHILE {
		template<class Stmt_>
		struct STOP {
			typedef Stmt_ retType;
		};

		/* WHILE<Cond, Stmt::NEXT>::retType == Stmt
		 * STOP<Stmt>::retType == Stmt
		 */
		typedef typename IF< Cond<Stmt>::retValue,
			WHILE<Cond, typename Stmt::NEXT>,
			STOP<Stmt>>::retType::retType retType;
	};

	template<int p, int n_>
	struct pow : std::integral_constant<int, p * pow<p, n_ - 1>::value> {};
	template<int p>
	struct pow<p, 0> : std::integral_constant<int, 1> {};

	template<int i>
	struct pow_e {
		static constexpr int value = pow<i, e>::value;
	};

	/* use while-loop */
	template<class Stmt>
	struct Cond {
		static constexpr int retValue = Stmt::ri <= n;
	};

	template<int i, int sum>
	struct Stmt {
		typedef Stmt<i + 1, sum + pow_e<i>::value> NEXT;

		static constexpr int ri = i;
		static constexpr int value = sum;
	};

	static constexpr int value = WHILE<Cond, Stmt<1, 0>>::retType::value;
};

/* sum all prime integer in [1, n] */
template<int n>
struct isPrime {
	struct Break : std::integral_constant<int, 2> { };
	struct Continue : std::integral_constant<int, 1> { };
	struct End : std::integral_constant<int, 0> { };

	template<template<class> class Cond, class Stmt>
	struct WHILE_ {
		template<class T> struct STOP {
			typedef T retType;
		};

		typedef typename IF<Cond<Stmt>::value == Break::value, STOP<FalseType>,
			typename IF<
				Cond<Stmt>::value == Continue::value,
				WHILE_<Cond, typename Stmt::NEXT>,
				STOP<TrueType>
			>::retType
		>::retType::retType retType;
	};

	template<class Stmt>
	struct Cond {
		static constexpr int value = IF<Stmt::ri >= n,
							End,
							typename IF<n % Stmt::ri == 0,
									Break,
									Continue
								>::retType
						>::retType::value;
	};

	template<int i>
	struct Stmt {
		typedef Stmt<i + 1> NEXT;
		enum { ri = i };
	};

	static constexpr int value = WHILE_<Cond, Stmt<2>>::retType::value;
};

template<int n>
struct SumPrime {
	template<int i>
	struct AddWith : std::integral_constant<int, i> { };

	static constexpr int value = IF<isPrime<n>::value, AddWith<n>, AddWith<0>>::retType::value + SumPrime<n - 1>::value;
};

template<>
struct SumPrime<1> {
	static constexpr int value = 0;
};

template<>
struct SumPrime<0> {
	static constexpr int value = 0;
};

template<int n>
struct SumPrimeWhile {
	template<int i>
	struct AddWith : std::integral_constant<int, i> { };

	template<template<class> class Cond, class Stmt>
	struct WHILE {
		template<class T>
		struct STOP {
			typedef T retType;
		};

		typedef typename
			IF<Cond<Stmt>::value, WHILE<Cond, typename Stmt::NEXT>, STOP<Stmt>>::retType::retType retType;
	};

	template<class Stmt>
	struct Cond : std::__bool_constant<Stmt::ri < n> { };

	template<int i, int sum>
	struct Stmt : std::integral_constant<int, sum> {
		typedef Stmt<i + 1, sum + IF<isPrime<i>::value, AddWith<i>, AddWith<0>>::retType::value> NEXT;

		static constexpr int ri = i;
	};

	static constexpr int value = WHILE<Cond, Stmt<2, 0>>::retType::value;
};


int main() {
#define print(...) std::cout << #__VA_ARGS__ << ":\t" << (__VA_ARGS__) << std::endl
	/* sum(n, e) = 1^e + 2^e + ... + n^e, use while-loop */
	print(SumPrimeWhile<1>::value);
	print(SumPrimeWhile<2>::value);
	print(SumPrimeWhile<3>::value);
	print(SumPrimeWhile<4>::value);
	print(SumPrimeWhile<5>::value);
	print(SumPrimeWhile<6>::value);
	print(SumPrimeWhile<7>::value);
	print(SumPrimeWhile<8>::value);
	print(SumPrimeWhile<9>::value);
	print(SumPrimeWhile<10>::value);
	print(SumPrimeWhile<11>::value);
	print(SumPrimeWhile<12>::value);
	print(SumPrimeWhile<13>::value);
	print(SumPrimeWhile<14>::value);
	print(SumPrimeWhile<15>::value);
	print(SumPrimeWhile<16>::value);
	print(SumPrimeWhile<17>::value);
	print(SumPrimeWhile<18>::value);
	print(SumPrimeWhile<19>::value);
	print(SumPrimeWhile<20>::value);
	print(SumPrimeWhile<21>::value);
	print(SumPrimeWhile<22>::value);
	print(SumPrimeWhile<23>::value);
	print(SumPrimeWhile<24>::value);
	print(SumPrimeWhile<25>::value);
	print(SumPrimeWhile<26>::value);
	print(SumPrimeWhile<27>::value);
	print(SumPrimeWhile<28>::value);
	print(SumPrimeWhile<29>::value);
	print(SumPrimeWhile<30>::value);
	print(SumPrimeWhile<31>::value);
	print(SumPrimeWhile<32>::value);
	print(SumPrimeWhile<33>::value);
	print(SumPrimeWhile<34>::value);
	print(SumPrimeWhile<35>::value);
	print(SumPrimeWhile<36>::value);
	print(SumPrimeWhile<37>::value);
	print(SumPrimeWhile<38>::value);
	print(SumPrimeWhile<39>::value);
	print(SumPrimeWhile<40>::value);
	print(SumPrimeWhile<41>::value);
	print(SumPrimeWhile<42>::value);
	print(SumPrimeWhile<43>::value);
	print(SumPrimeWhile<44>::value);
	print(SumPrimeWhile<45>::value);
	print(SumPrimeWhile<46>::value);
	print(SumPrimeWhile<47>::value);
	print(SumPrimeWhile<48>::value);
	print(SumPrimeWhile<49>::value);
	print(SumPrimeWhile<50>::value);
	print(SumPrimeWhile<51>::value);
	print(SumPrimeWhile<52>::value);
	print(SumPrimeWhile<53>::value);
	print(SumPrimeWhile<54>::value);
	print(SumPrimeWhile<55>::value);
	print(SumPrimeWhile<56>::value);
	print(SumPrimeWhile<57>::value);
	print(SumPrimeWhile<58>::value);
	print(SumPrimeWhile<59>::value);
	print(SumPrimeWhile<60>::value);
	print(SumPrimeWhile<61>::value);
	print(SumPrimeWhile<62>::value);
	print(SumPrimeWhile<63>::value);
	print(SumPrimeWhile<64>::value);
	print(SumPrimeWhile<65>::value);
	print(SumPrimeWhile<66>::value);
	print(SumPrimeWhile<67>::value);
	print(SumPrimeWhile<68>::value);
	print(SumPrimeWhile<69>::value);
	print(SumPrimeWhile<70>::value);
	print(SumPrimeWhile<71>::value);
	print(SumPrimeWhile<72>::value);
	print(SumPrimeWhile<73>::value);
	print(SumPrimeWhile<74>::value);
	print(SumPrimeWhile<75>::value);
	print(SumPrimeWhile<76>::value);
	print(SumPrimeWhile<77>::value);
	print(SumPrimeWhile<78>::value);
	print(SumPrimeWhile<79>::value);
	print(SumPrimeWhile<80>::value);
	print(SumPrimeWhile<81>::value);
	print(SumPrimeWhile<82>::value);
	print(SumPrimeWhile<83>::value);
	print(SumPrimeWhile<84>::value);
	print(SumPrimeWhile<85>::value);
	print(SumPrimeWhile<86>::value);
	print(SumPrimeWhile<87>::value);
	print(SumPrimeWhile<88>::value);
	print(SumPrimeWhile<89>::value);
	print(SumPrimeWhile<90>::value);
	print(SumPrimeWhile<91>::value);
	print(SumPrimeWhile<92>::value);
	print(SumPrimeWhile<93>::value);
	print(SumPrimeWhile<94>::value);
	print(SumPrimeWhile<95>::value);
	print(SumPrimeWhile<96>::value);
	print(SumPrimeWhile<97>::value);
	print(SumPrimeWhile<98>::value);
	print(SumPrimeWhile<99>::value);
	print(SumPrimeWhile<100>::value);
	print(SumPrimeWhile<101>::value);
	print(SumPrimeWhile<102>::value);
	/*
	print(Sum<4, 2>::value);
	print(SumPrime<1>::value);
	print(SumPrime<2>::value);
	print(SumPrime<3>::value);
	print(SumPrime<4>::value);
	print(SumPrime<5>::value);
	print(SumPrime<6>::value);
	print(SumPrime<7>::value);
	print(SumPrime<8>::value);
	print(SumPrime<9>::value);
	print(SumPrime<10>::value);
	print(SumPrime<11>::value);
	print(SumPrime<12>::value);
	print(SumPrime<13>::value);
	print(SumPrime<14>::value);
	print(SumPrime<15>::value);
	print(SumPrime<16>::value);
	print(SumPrime<17>::value);
	print(SumPrime<18>::value);
	print(SumPrime<19>::value);
	print(SumPrime<20>::value);
	print(SumPrime<21>::value);
	print(SumPrime<22>::value);
	print(SumPrime<23>::value);
	print(SumPrime<24>::value);
	print(SumPrime<25>::value);
	print(SumPrime<26>::value);
	print(SumPrime<27>::value);
	print(SumPrime<28>::value);
	print(SumPrime<29>::value);
	print(SumPrime<30>::value);
	print(SumPrime<31>::value);
	print(SumPrime<32>::value);
	print(SumPrime<33>::value);
	print(SumPrime<34>::value);
	print(SumPrime<35>::value);
	print(SumPrime<36>::value);
	print(SumPrime<37>::value);
	print(SumPrime<38>::value);
	print(SumPrime<39>::value);
	print(SumPrime<40>::value);
	print(SumPrime<41>::value);
	print(SumPrime<42>::value);
	print(SumPrime<43>::value);
	print(SumPrime<44>::value);
	print(SumPrime<45>::value);
	print(SumPrime<46>::value);
	print(SumPrime<47>::value);
	print(SumPrime<48>::value);
	print(SumPrime<49>::value);
	print(SumPrime<50>::value);
	print(SumPrime<51>::value);
	print(SumPrime<52>::value);
	print(SumPrime<53>::value);
	print(SumPrime<54>::value);
	print(SumPrime<55>::value);
	print(SumPrime<56>::value);
	print(SumPrime<57>::value);
	print(SumPrime<58>::value);
	print(SumPrime<59>::value);
	print(SumPrime<60>::value);
	print(SumPrime<61>::value);
	print(SumPrime<62>::value);
	print(SumPrime<63>::value);
	print(SumPrime<64>::value);
	print(SumPrime<65>::value);
	print(SumPrime<66>::value);
	print(SumPrime<67>::value);
	print(SumPrime<68>::value);
	print(SumPrime<69>::value);
	print(SumPrime<70>::value);
	print(SumPrime<71>::value);
	print(SumPrime<72>::value);
	print(SumPrime<73>::value);
	print(SumPrime<74>::value);
	print(SumPrime<75>::value);
	print(SumPrime<76>::value);
	print(SumPrime<77>::value);
	print(SumPrime<78>::value);
	print(SumPrime<79>::value);
	print(SumPrime<80>::value);
	print(SumPrime<81>::value);
	print(SumPrime<82>::value);
	print(SumPrime<83>::value);
	print(SumPrime<84>::value);
	print(SumPrime<85>::value);
	print(SumPrime<86>::value);
	print(SumPrime<87>::value);
	print(SumPrime<88>::value);
	print(SumPrime<89>::value);
	print(SumPrime<90>::value);
	print(SumPrime<91>::value);
	print(SumPrime<92>::value);
	print(SumPrime<93>::value);
	print(SumPrime<94>::value);
	print(SumPrime<95>::value);
	print(SumPrime<96>::value);
	print(SumPrime<97>::value);
	print(SumPrime<98>::value);
	print(SumPrime<99>::value);
	print(SumPrime<100>::value);
	print(SumPrime<101>::value);
	print(SumPrime<102>::value);

	print(isPrime<1>::value);
	print(isPrime<2>::value);
	print(isPrime<3>::value);
	print(isPrime<4>::value);
	print(isPrime<5>::value);
	print(isPrime<6>::value);
	print(isPrime<7>::value);
	print(isPrime<8>::value);
	print(isPrime<9>::value);
	print(isPrime<10>::value);
	print(isPrime<11>::value);
	print(isPrime<12>::value);
	print(isPrime<13>::value);
	print(isPrime<14>::value);
	print(isPrime<15>::value);
	print(isPrime<16>::value);
	print(isPrime<17>::value);
	print(isPrime<18>::value);
	print(isPrime<19>::value);
	print(isPrime<20>::value);
	print(isPrime<21>::value);
	print(isPrime<22>::value);
	print(isPrime<23>::value);
	print(isPrime<24>::value);
	print(isPrime<25>::value);
	print(isPrime<26>::value);
	print(isPrime<27>::value);
	print(isPrime<28>::value);
	print(isPrime<29>::value);
	print(isPrime<30>::value);
	print(isPrime<31>::value);
	print(isPrime<32>::value);
	print(isPrime<33>::value);
	print(isPrime<34>::value);
	print(isPrime<35>::value);
	print(isPrime<36>::value);
	print(isPrime<37>::value);
	print(isPrime<38>::value);
	print(isPrime<39>::value);
	print(isPrime<40>::value);
	print(isPrime<41>::value);
	print(isPrime<42>::value);
	print(isPrime<43>::value);
	print(isPrime<44>::value);
	print(isPrime<45>::value);
	print(isPrime<46>::value);
	print(isPrime<47>::value);
	print(isPrime<48>::value);
	print(isPrime<49>::value);
	print(isPrime<50>::value);
	print(isPrime<51>::value);
	print(isPrime<52>::value);
	print(isPrime<53>::value);
	print(isPrime<54>::value);
	print(isPrime<55>::value);
	print(isPrime<56>::value);
	print(isPrime<57>::value);
	print(isPrime<58>::value);
	print(isPrime<59>::value);
	print(isPrime<60>::value);
	print(isPrime<61>::value);
	print(isPrime<62>::value);
	print(isPrime<63>::value);
	print(isPrime<64>::value);
	print(isPrime<65>::value);
	print(isPrime<66>::value);
	print(isPrime<67>::value);
	print(isPrime<68>::value);
	print(isPrime<69>::value);
	print(isPrime<70>::value);
	print(isPrime<71>::value);
	print(isPrime<72>::value);
	print(isPrime<73>::value);
	print(isPrime<74>::value);
	print(isPrime<75>::value);
	print(isPrime<76>::value);
	print(isPrime<77>::value);
	print(isPrime<78>::value);
	print(isPrime<79>::value);
	print(isPrime<80>::value);
	print(isPrime<81>::value);
	print(isPrime<82>::value);
	print(isPrime<83>::value);
	print(isPrime<84>::value);
	print(isPrime<85>::value);
	print(isPrime<86>::value);
	print(isPrime<87>::value);
	print(isPrime<88>::value);
	print(isPrime<89>::value);
	print(isPrime<90>::value);
	print(isPrime<91>::value);
	print(isPrime<92>::value);
	print(isPrime<93>::value);
	print(isPrime<94>::value);
	print(isPrime<95>::value);
	print(isPrime<96>::value);
	print(isPrime<97>::value);
	print(isPrime<98>::value);
	print(isPrime<99>::value);
	print(isPrime<100>::value);
	print(isPrime<101>::value);
	print(isPrime<102>::value);
	*/
#undef print
	return 0;
}
