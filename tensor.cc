#include <iostream>
#include <cstdint>
#include <cassert>
#include <utility>


template<class T, size_t N>
class TupleImply {
	T v;
	TupleImply<T, N - 1> right;
public:

	template<class U, class... UList>
	TupleImply(U && v, UList... right) :
		v(std::forward<U>(v)),
		right(std::forward<UList>(right)...)
	{ }
};

template<class T>
class TupleImply<T, 1> {
	T v;
public:
	TupleImply(T && v) :
		v(std::forward<T>(v))
	{ }
};

template<size_t N>
class Shape {
	size_t *st, *ed;
	bool can_release;

	template<size_t I>
	void copy() {
		static_assert(I == N, "");
	}

	template<size_t I, class T, class... TList>
	void copy(T v, TList... values) {
		static_assert(I < N, "");
		st[I] = v;
		copy<I + 1, TList...>(values...);
	}
public:
	using value_type = size_t;
	using iterator = size_t *;
	using const_iterator = const iterator;

	~Shape() noexcept {
		if(can_release) delete []st;
	}

	Shape() : st(new size_t[N]), can_release(true) {
		ed = st + N;
	}

	Shape(size_t *st, size_t *ed) : st(st), ed(ed), can_release(false) { }

	template<class... TList>
	Shape(TList... values) :
		Shape()
	{
		copy<0, TList...>(values...);
	}

	Shape(const Shape &other) :
		Shape()
	{
		std::copy(other.st, other.ed, st);
	}

	Shape(Shape && other) :
		st(other.st),
		ed(other.ed),
		can_release(other.can_release)
	{
		other.st = nullptr;
		other.ed = nullptr;
		other.can_release = false;
	}

	Shape &operator=(const Shape &other) {
		if(this != &other)
			std::copy(st, ed, other.st);
		return *this;
	}

	Shape &operator=(Shape &&other) {
		if(this != &other) {
			delete []st;

			st = other.st;
			ed = other.ed;
			can_release = other.can_release;

			other.st = nullptr;
			other.ed = nullptr;
			other.can_release = false;
		}
		return *this;
	}

	size_t &operator[] (const size_t idx) const {
		return st[idx];
	}

	size_t size_all() const {
		if(st == ed) return 0;
		size_t ret = 1;
		std::cout << "size_all" << std::endl;
		for(auto it = st; it < ed; it++) {
			std::cout << *it << "," << it << "," << ed << std::endl;
			auto new_ret = ret * (*it);
			assert(ret <= new_ret);
			ret = new_ret;
		}
		return ret;
	}

	size_t size() const {
		return reinterpret_cast<long int>(ed - st);
	}
	iterator begin() const { return st; }
	iterator end() const { return ed; }
};


template<class T, size_t N>
class Tensor {
	Shape<N> shape;
	T *data;
public:
	Tensor(Shape<N> && shape) : shape(shape) {
		data = new T [shape.size_all()];
	}

};


int main() {
	Shape<5> _1 = {1, 2, 3, 4, 5};
	std::cout << _1.size() << std::endl;
	assert(_1.size() == 5);
	assert(_1.size_all() == 120);
	assert(_1[0] == 1);
	assert(_1[1] == 2);
	assert(_1[2] == 3);
	assert(_1[3] == 4);
	assert(_1[4] == 5);

	{
		/* copy */
		auto _2 = _1;
		_2[0] = 2;

		assert(_1.size() == 5);
		assert(_1.size_all() == 120);
		assert(_1[0] == 1);
		assert(_1[1] == 2);
		assert(_1[2] == 3);
		assert(_1[3] == 4);
		assert(_1[4] == 5);

		assert(_2.size() == 5);
		assert(_2.size_all() == 240);
		assert(_2[0] == 2);
		assert(_2[1] == 2);
		assert(_2[2] == 3);
		assert(_2[3] == 4);
		assert(_2[4] == 5);
	}

	{
		/* move */
		auto _2 = std::move(_1);
		_2[0] = 2;

		assert(_1.size() == 0);
		assert(_1.size_all() == 0);

		assert(_2.size() == 5);
		assert(_2.size_all() == 240);
		assert(_2[0] == 2);
		assert(_2[1] == 2);
		assert(_2[2] == 3);
		assert(_2[3] == 4);
		assert(_2[4] == 5);
	}

	return 0;
}
