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
	struct BreakType : std::integral_constant<int, 2> { };
	struct ContinueType : std::integral_constant<int, 1> { };
	struct EndType : std::integral_constant<int, 0> { };

	template<template<class> class Cond, class Stmt>
	struct WHILE_ {
		template<class T> struct STOP {
			typedef T retType;
		};

		typedef typename IF<Cond<Stmt>::value == BreakType::value, STOP<FalseType>,
			typename IF<
				Cond<Stmt>::value == ContinueType::value,
				WHILE_<Cond, typename Stmt::NEXT>,
				STOP<TrueType>
			>::retType
		>::retType::retType retType;
	};

	template<class Stmt>
	struct Cond {
		enum { value = IF<Stmt::ri >= n,
							EndType,
							typename IF<n % Stmt::ri == 0,
									BreakType,
									ContinueType
								>::retType
						>::retType::value
		};
	};

	template<int i>
	struct Stmt {
		typedef Stmt<i + 1> NEXT;
		enum { ri = i };
	};

	static constexpr int value = WHILE_<Cond, Stmt<2>>::retType::value;
};

int main() {
	/* sum(n, e) = 1^e + 2^e + ... + n^e, use while-loop */
	std::cout << "1: " << Sum<4, 2>::value << std::endl;
	std::cout << "2: " << isPrime<2>::value << std::endl;
	std::cout << "3: " << isPrime<3>::value << std::endl;
	std::cout << "4: " << isPrime<4>::value << std::endl;
	std::cout << "5: " << isPrime<5>::value << std::endl;
	std::cout << "6: " << isPrime<6>::value << std::endl;
	std::cout << "7: " << isPrime<7>::value << std::endl;
	std::cout << "8: " << isPrime<8>::value << std::endl;
	std::cout << "9: " << isPrime<9>::value << std::endl;
	std::cout << "10: " << isPrime<10>::value << std::endl;
	std::cout << "11: " << isPrime<11>::value << std::endl;
	std::cout << "12: " << isPrime<12>::value << std::endl;
	std::cout << "13: " << isPrime<13>::value << std::endl;
	std::cout << "14: " << isPrime<14>::value << std::endl;
	std::cout << "15: " << isPrime<15>::value << std::endl;
	std::cout << "16: " << isPrime<16>::value << std::endl;
	std::cout << "17: " << isPrime<17>::value << std::endl;
	std::cout << "18: " << isPrime<18>::value << std::endl;
	std::cout << "19: " << isPrime<19>::value << std::endl;
	std::cout << "20: " << isPrime<20>::value << std::endl;
	std::cout << "21: " << isPrime<21>::value << std::endl;
	std::cout << "22: " << isPrime<22>::value << std::endl;
	std::cout << "23: " << isPrime<23>::value << std::endl;
	std::cout << "24: " << isPrime<24>::value << std::endl;
	std::cout << "25: " << isPrime<25>::value << std::endl;
	std::cout << "26: " << isPrime<26>::value << std::endl;
	std::cout << "27: " << isPrime<27>::value << std::endl;
	std::cout << "28: " << isPrime<28>::value << std::endl;
	std::cout << "29: " << isPrime<29>::value << std::endl;
	std::cout << "30: " << isPrime<30>::value << std::endl;
	std::cout << "31: " << isPrime<31>::value << std::endl;
	std::cout << "32: " << isPrime<32>::value << std::endl;
	std::cout << "33: " << isPrime<33>::value << std::endl;
	std::cout << "34: " << isPrime<34>::value << std::endl;
	std::cout << "35: " << isPrime<35>::value << std::endl;
	std::cout << "36: " << isPrime<36>::value << std::endl;
	std::cout << "37: " << isPrime<37>::value << std::endl;
	std::cout << "38: " << isPrime<38>::value << std::endl;
	std::cout << "39: " << isPrime<39>::value << std::endl;
	std::cout << "40: " << isPrime<40>::value << std::endl;
	std::cout << "41: " << isPrime<41>::value << std::endl;
	std::cout << "42: " << isPrime<42>::value << std::endl;
	std::cout << "43: " << isPrime<43>::value << std::endl;
	std::cout << "44: " << isPrime<44>::value << std::endl;
	std::cout << "45: " << isPrime<45>::value << std::endl;
	std::cout << "46: " << isPrime<46>::value << std::endl;
	std::cout << "47: " << isPrime<47>::value << std::endl;
	std::cout << "48: " << isPrime<48>::value << std::endl;
	std::cout << "49: " << isPrime<49>::value << std::endl;
	std::cout << "50: " << isPrime<50>::value << std::endl;
	std::cout << "51: " << isPrime<51>::value << std::endl;
	std::cout << "52: " << isPrime<52>::value << std::endl;
	std::cout << "53: " << isPrime<53>::value << std::endl;
	std::cout << "54: " << isPrime<54>::value << std::endl;
	std::cout << "55: " << isPrime<55>::value << std::endl;
	std::cout << "56: " << isPrime<56>::value << std::endl;
	std::cout << "57: " << isPrime<57>::value << std::endl;
	std::cout << "58: " << isPrime<58>::value << std::endl;
	std::cout << "59: " << isPrime<59>::value << std::endl;
	std::cout << "60: " << isPrime<60>::value << std::endl;
	std::cout << "61: " << isPrime<61>::value << std::endl;
	std::cout << "62: " << isPrime<62>::value << std::endl;
	std::cout << "63: " << isPrime<63>::value << std::endl;
	std::cout << "64: " << isPrime<64>::value << std::endl;
	std::cout << "65: " << isPrime<65>::value << std::endl;
	std::cout << "66: " << isPrime<66>::value << std::endl;
	std::cout << "67: " << isPrime<67>::value << std::endl;
	std::cout << "68: " << isPrime<68>::value << std::endl;
	std::cout << "69: " << isPrime<69>::value << std::endl;
	std::cout << "70: " << isPrime<70>::value << std::endl;
	std::cout << "71: " << isPrime<71>::value << std::endl;
	std::cout << "72: " << isPrime<72>::value << std::endl;
	std::cout << "73: " << isPrime<73>::value << std::endl;
	std::cout << "74: " << isPrime<74>::value << std::endl;
	std::cout << "75: " << isPrime<75>::value << std::endl;
	std::cout << "76: " << isPrime<76>::value << std::endl;
	std::cout << "77: " << isPrime<77>::value << std::endl;
	std::cout << "78: " << isPrime<78>::value << std::endl;
	std::cout << "79: " << isPrime<79>::value << std::endl;
	std::cout << "80: " << isPrime<80>::value << std::endl;
	std::cout << "81: " << isPrime<81>::value << std::endl;
	std::cout << "82: " << isPrime<82>::value << std::endl;
	std::cout << "83: " << isPrime<83>::value << std::endl;
	std::cout << "84: " << isPrime<84>::value << std::endl;
	std::cout << "85: " << isPrime<85>::value << std::endl;
	std::cout << "86: " << isPrime<86>::value << std::endl;
	std::cout << "87: " << isPrime<87>::value << std::endl;
	std::cout << "88: " << isPrime<88>::value << std::endl;
	std::cout << "89: " << isPrime<89>::value << std::endl;
	std::cout << "90: " << isPrime<90>::value << std::endl;
	std::cout << "91: " << isPrime<91>::value << std::endl;
	std::cout << "92: " << isPrime<92>::value << std::endl;
	std::cout << "93: " << isPrime<93>::value << std::endl;
	std::cout << "94: " << isPrime<94>::value << std::endl;
	std::cout << "95: " << isPrime<95>::value << std::endl;
	std::cout << "96: " << isPrime<96>::value << std::endl;
	std::cout << "97: " << isPrime<97>::value << std::endl;
	std::cout << "98: " << isPrime<98>::value << std::endl;
	std::cout << "99: " << isPrime<99>::value << std::endl;
	std::cout << "100: " << isPrime<100>::value << std::endl;
	std::cout << "101: " << isPrime<101>::value << std::endl;
	std::cout << "102: " << isPrime<102>::value << std::endl;
	return 0;
}
