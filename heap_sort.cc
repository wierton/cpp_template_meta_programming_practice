#include <iostream>


template<class T, T...values>
struct Array {
	std::make_tuple(values);
};

template<unsigned I, class T, T...values>
struct AdjustAt {
	If<ValueAt<I>::value < ValueAt<2 * I>::value>
};
