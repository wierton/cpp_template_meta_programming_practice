#include <utility>
#include <tuple>
#include <iostream>

template<size_t...I>
struct seq {
	using type = seq;
};

template<class... I>
struct concat;

template<size_t L, size_t...H>
struct concat<seq<L>, seq<H...>> : public seq<L, (H + 1)...> {
};

template<size_t N>
struct make : public concat<seq<0>, typename make<N-1>::type> {
};

template<>
struct make<1> : public seq<0> {
};

template<>
struct make<0> : public seq<> {
};


// [IMPORTANT]
// for loop based on index sequence
template<class Sequence>
struct adder_impl;

template<size_t...I>
struct adder_impl<seq<I...>> {
	template<class...TList>
	static constexpr decltype(auto) apply(std::tuple<TList...> arg) {
		return std::make_tuple( (std::get<I>(arg) + 1)... );
	}
};

template<class... TList>
constexpr std::tuple<TList...> adder(std::tuple<TList...> arg) {
	return adder_impl<typename make<sizeof...(TList)>::type>::apply(arg);
}

void adder_test() {
	constexpr std::tuple<int, int, int, int> tup(1, 2, 0, 4);
	constexpr auto new_tup = adder(tup);

	static_assert(std::get<0>(new_tup) == 2, "");
	static_assert(std::get<1>(new_tup) == 3, "");
	static_assert(std::get<2>(new_tup) == 1, "");
	static_assert(std::get<3>(new_tup) == 5, "");
}


template<size_t N, size_t F, size_t...I>
constexpr size_t get(seq<F, I...> q) {
	if constexpr (N == 0) {
		return F;
	} else {
		return get<N - 1>(seq<I...>{});
	}
}

int main() {
	auto seq10 = make<10>{};
	std::cout << get<0>(seq10) << " ";
	std::cout << get<1>(seq10) << " ";
	std::cout << get<2>(seq10) << " ";
	std::cout << get<3>(seq10) << " ";
	std::cout << get<4>(seq10) << " ";
	std::cout << get<5>(seq10) << " ";
	std::cout << get<6>(seq10) << " ";
	std::cout << get<7>(seq10) << " ";
	std::cout << get<8>(seq10) << " ";
	std::cout << get<9>(seq10) << " ";
	std::cout << "\n";
	return 0;
}
