#include <utility>
#include <vector>
#include <tuple>
#include <array>
#include <iostream>


template<class...ITList>
class MultiIterator {
	std::tuple<ITList...> itlist;
public:

	MultiIterator(std::tuple<ITList...> itlist) :
		itlist(itlist)
	{
	}

	MultiIterator(ITList... itlist) :
		itlist(itlist...)
	{
	}

	template<size_t...I>
	decltype(auto) deref_impl(std::index_sequence<I...> seq) {
		return std::tuple<decltype(*std::declval<ITList>())&...> { *std::get<I>(itlist)... };
	}

	decltype(auto) operator *() {
		return deref_impl(std::make_index_sequence<sizeof...(ITList)> {});
	}

	template<size_t... I>
	decltype(auto) self_inc_impl(std::index_sequence<I...> seq) {
		auto ignore = std::array<int, sizeof...(I)> {
			( (++ std::get<I>(itlist)), 0 )...
		};
	}

	MultiIterator &operator ++() {
		self_inc_impl(std::make_index_sequence<sizeof...(ITList)> {});
	}

	template<size_t... I>
	decltype(auto) not_equal_impl(std::index_sequence<I...> seq, const MultiIterator &other) {
		std::array<bool, sizeof...(ITList)> arr { (std::get<I>(itlist) != std::get<I>(other.itlist)) ... };

		if constexpr(sizeof...(I) == 0) {
			return false;
		} else {
			bool result = arr[0];
			for(auto i = 1; i < arr.size(); i++)
				result = result && arr[i];
			return result;
		}
	}

	bool operator !=(const MultiIterator &other) {
		return not_equal_impl(std::make_index_sequence<sizeof...(ITList)>{}, other);
	}
};

template<class...ContainerList>
class MultiContainer {
	std::tuple<ContainerList &...> containers;
public:
	MultiContainer(ContainerList &... containers) :
		containers(containers...)
	{
	}

	template<size_t...I>
	decltype(auto) begin_impl(std::index_sequence<I...> seq) {
		return MultiIterator((std::get<I>(containers)).begin() ...);
	}

	decltype(auto) begin() {
		return begin_impl(std::make_index_sequence<sizeof...(ContainerList)> {});
	}

	template<size_t...I>
	decltype(auto) end_impl(std::index_sequence<I...> seq) {
		return MultiIterator((std::get<I>(containers)).end() ...);
	}

	decltype(auto) end() {
		return end_impl(std::make_index_sequence<sizeof...(ContainerList)> {});
	}
};


void test() {
	int a = 0, b = 1, c = 2;

	std::tuple<int&,int&,int&> tup(a, b, c);
	auto [x, y, z] = tup;

	x = 3; y = 4; z = 5;

	std::cout << "----begin----\n";
	std::cout << a << " " << b << " " << c << "\n";
	std::cout << x << " " << y << " " << z << "\n";
	std::cout << "----end----\n";
}

void test_one() {
	std::vector<int> va = {1, 2, 3, 4, 5};
	std::cout << "----begin----\n";
	for(auto &a : va) {
		std::cout << a ++ << std::endl;
	}
	std::cout << "----\n";
	for(auto a : va) {
		std::cout << a << std::endl;
	}
	std::cout << "----end----\n";
}

int main() {
	test();
	test_one();

	std::vector<int> va = {1, 2, 3, 4, 5};
	std::vector<int> vb = {2, 3, 4, 5, 6, 7};
	std::vector<int> vc = {2, 3, 4, 5};
	for(auto [a, b, c] : MultiContainer(va, vb, vc)) {
		std::cout << a ++ << "," << b ++ << "," << c ++ << std::endl;
	}
	std::cout << "----\n";
	for(auto [a, b, c] : MultiContainer(va, vb, vc)) {
		std::cout << a << "," << b << "," << c << std::endl;
	}
	return 0;
}

