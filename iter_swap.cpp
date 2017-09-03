#include <iostream>



template<class T1, class T2>
void iter_swap<T1, T2>(T1 t1, T2 t2) {

	template<bool use_swap> struct swap_impl { };

	constexpr use_swap = is_same<t1, t2>;

	template<>
	struct swap_impl<true> {
		static void do_it(T1 t1, T2 t2) {
			std::swap(t1, t2);
		}
	};

	template<>
	struct swap_impl<false> {
		static void do_it(T1 t1, T2 t2) {
			T1 &t = t1;
			t1 = t2;
			t2 = t;
		};
	};

	swap_impl<use_swap>::do_it(t1, t2);
}
