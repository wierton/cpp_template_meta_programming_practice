#include <iostream>

/* FIXME!!! */

template<class T1, class T2>
struct is_same : std::integral_constant<bool, false> { };

template<class T>
struct is_same<T, T> : std::integral_constant<bool, true> { };

template<bool use_swap, class T1, class T2>
struct my_swap_impl { };

template<class T1, class T2>
struct my_swap_impl<true, T1, T2> {
	static void do_it(T1 t1, T2 t2) {
		std::cout << "call std::swap\n";
		std::swap(t1, t2);
	}
};

template<class T1, class T2>
struct my_swap_impl<false, T1, T2> {
	static void do_it(T1 t1, T2 t2) {
		std::cout << "call my_swap\n";
		T1 &t = t1;
		t1 = t2;
		t2 = t;
	};
};

template<class T1, class T2>
void my_iter_swap(T1 t1, T2 t2) {

	static constexpr bool use_swap = is_same<T1, T2>::value;

	my_swap_impl<use_swap, T1, T2>::do_it(t1, t2);
}

int main() {
	int a = 1, b = 2;
	int *pa = &a, *pb = &b;
	my_iter_swap(pa, pb);
	std::cout << a << ", " << b << std::endl;
	return 0;
}
