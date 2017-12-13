#include <iostream>
#include <utility>
#include <cassert>

template<unsigned N, class... TList>
struct TypeAt;

template<unsigned N, class T, class... TList>
struct TypeAt<N, T, TList...> {
	using type = typename TypeAt<N - 1, TList...>::type;
};

template<class T, class... TList>
struct TypeAt<0, T, TList...> {
	using type = T;
};

template<unsigned N>
struct TypeAt<N> {
	/* error */
};

template<class T, class... TList>
class Tuple {
	T v;
	Tuple<TList...> right;

	template<unsigned N, class U, class... UList>
	friend struct TupleGet;
public:
	Tuple(T&& v, TList&&...right) :
		v(std::forward<T>(v)),
		right(std::forward<TList>(right)...)
	{ }

};

template<class T>
class Tuple<T> {
	T v;
	template<unsigned N, class U, class... UList>
	friend struct TupleGet;
public:
	Tuple(T && v) :
		v(std::forward<T>(v))
	{ }
};


template<unsigned N, class T, class... TList>
struct TupleGet {
	static typename TypeAt<N, T, TList...>::type &
	get(Tuple<T, TList...>& tuple) {
		return TupleGet<N - 1, TList...>::get(tuple.right);
	}
};

template<class T, class... TList>
struct TupleGet<0, T, TList...> {
	static T& get(Tuple<T, TList...>& tuple) {
		return tuple.v;
	}
};


template<unsigned N, class T, class... TList>
typename TypeAt<N, T, TList...>::type &
get(Tuple<T, TList...>& tuple) {
	return TupleGet<N, T, TList...>::get(tuple);
}

template<class... TList>
constexpr Tuple<TList...> make_tuple(TList && ... values) {
	return Tuple<TList...> { std::forward<TList>(values)... };
}

int main() {
	static_assert(std::is_same<TypeAt<0, int>::type, int>::value, "");
	static_assert(std::is_same<TypeAt<1, int, char>::type, char>::value, "");
	static_assert(std::is_same<TypeAt<2, short, char, int>::type, int>::value, "");

	Tuple<int, const char*> tup = {1, ""};
	assert(get<0>(tup) == 1);
	assert(get<1>(tup)[0] == 0);

	get<0>(tup) = 2;
	assert(get<0>(tup) == 2);

	get<1>(tup) = "123";
	assert(get<1>(tup)[0] == '1');

	auto a = make_tuple(1, 2, "123");
	assert(get<0>(a) == 1);
	assert(get<1>(a) == 2);
	assert(get<2>(a)[0] == '1');

	return 0;
}
