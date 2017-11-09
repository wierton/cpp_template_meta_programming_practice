#include <iostream>


template<class T, class... TList>
struct tuple {
	typedef T type;
	T value;
	typedef tuple<TList...> LeftType;
	LeftType leftValue;
};

/*
a::type
a.value

a::LeftType::type
a.LeftValue.value
*/

template<unsigned N, class TList, TList &_tuple>
struct tuple_at {
	typedef tuple_at<N - 1, TList::LeftType> type;
	auto &value = tuple_at<N - 1, _tuple.leftValue>::value;
}
