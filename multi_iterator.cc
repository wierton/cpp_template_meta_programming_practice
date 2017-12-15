#include <stdio.h>
#include <iostream>
#include <vector>
#include <tuple>


template<class T, class U>
class MultiIterator {
	T l;
	U r;

	using TV = decltype(*std::declval<T>());
	using UV = decltype(*std::declval<U>());

public:
	MultiIterator(T l, U r) : l(l), r(r) { }

	std::tuple<TV &, UV &> operator*() {
		return {*l, *r};
	}

	MultiIterator &operator ++() {
		l ++; r ++;
		return *this;
	}

	bool operator != (const MultiIterator &other) {
		return l != other.l && r != other.r;
	}
};


template<class T, class U>
class MultiIteratorWrapper {
	T &l;
	U &r;
public:
	MultiIteratorWrapper(T &l, U &r) : l(l), r(r) { }

	MultiIterator<typename T::iterator, typename U::iterator> begin() {
		return MultiIterator(l.begin(), r.begin());
	}

	MultiIterator<typename T::iterator, typename U::iterator> end() {
		return MultiIterator(l.end(), r.end());
	}
};

template<class T, class U>
decltype(auto) make_iterator(T &l, U &r) {
	return MultiIteratorWrapper(l, r);
}

int main() {
	std::vector<int> a = {1, 2, 3, 4, 5, 6};
	std::vector<int> b = {1, 2, 3, 4, 5};

	for(auto [l, r] : make_iterator(a, b)) {
		std::cout << l << ", " << r << std::endl;
	}

	return 0;
}
