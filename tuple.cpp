#include <iostream>


template<class T, class... TList>
struct tuple {
	T value;
	typedef tuple<TList...> LeftType;
	LeftType leftValue;
};


template<unsigned N, class T>
struct get {
	typedef get<N - 1, T::leftValue> type;

	operator(T t) {
	}
};
