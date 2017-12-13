#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>
#include <cassert>
#include <string>

#define dynamic_assert(cond, ...) assert(cond);

template<class T=int>
constexpr T const_max(T a, T b) {
	return a > b ? a : b;
}

template<class T=int>
constexpr T const_min(T a, T b) {
	return a < b ? a : b;
}

template<class... TS> struct MaxSize;

template<class T, class... Left>
struct MaxSize<T, Left...> {
private:
	static constexpr unsigned cur_size = sizeof(T);
	static constexpr unsigned left_size = MaxSize<Left...>::value;
public:
	static constexpr unsigned value = const_max(cur_size, left_size);
};

template<>
struct MaxSize<> {
private:
	static constexpr unsigned cur_size = 0;
	static constexpr unsigned left_size = 0;
public:
	static constexpr unsigned value = 0;
};

template<class... TS> struct MaxAlign;

template<class T, class... Left>
struct MaxAlign<T, Left...> {
private:
	static constexpr unsigned cur_align = alignof(T);
	static constexpr unsigned left_align = MaxAlign<Left...>::value;
public:
	static constexpr unsigned value = const_max(cur_align, left_align);
};

template<>
struct MaxAlign<> {
private:
	static constexpr unsigned cur_align = 0;
	static constexpr unsigned left_align = 0;
public:
	static constexpr unsigned value = 0;
};

template<class T, class... TS> struct IndexOf;

template<class T>
struct IndexOf<T> {
	static constexpr unsigned exist = 0;
	static constexpr unsigned value = 0;
};

template<class T, class FirstT, class... TS>
struct IndexOf<T, FirstT, TS...> {
	static constexpr unsigned exist = std::is_same<T, FirstT>::value || IndexOf<T, TS...>::exist;
	static constexpr unsigned value =
		exist ? 1 + IndexOf<T, TS...>::value : 0;
};


template<unsigned k, class... T> struct SelectType;

template<>
struct SelectType<0> {
};

template<unsigned k, class T, class... TS>
struct SelectType<k, T, TS...> {
	using type = typename std::conditional<k == 0, T, typename SelectType<k - 1, TS...>::type>::type;
};

template<class T>
void destructor(uint8_t buf[]) { 
	reinterpret_cast<T *>(buf)->~T();
};

template<class T>
void copy(uint8_t rbuf[], const uint8_t obuf[]) { 
	new(rbuf) T(*reinterpret_cast<const T*>(obuf));
};

template<class T>
void move(uint8_t rbuf[], uint8_t obuf[]) { 
	new(rbuf) T(std::move(*reinterpret_cast<T*>(obuf)));
};

template<class... TS>
class Variant {
private:
	static constexpr auto alignment() { return MaxAlign<TS...>::value; }
	static constexpr auto size() { return MaxSize<TS...>::value; }

	size_t id;
	alignas(alignment()) uint8_t data[size()];

	using destructor_t = void (*)(uint8_t buf[]);
	using move_func_t = void (*)(uint8_t rbuf[], uint8_t obuf[]);
	using copy_func_t = void (*)(uint8_t rbuf[], const uint8_t obuf[]);

	static constexpr destructor_t destroy_func[] = { destructor<TS>... };
	static constexpr copy_func_t copy_func[] = { copy<TS>... };
	static constexpr move_func_t move_func[] = { move<TS>... };
public:

	Variant() { id = 0; }
	Variant(const Variant &other) {
		if(id) { this->~Variant(); }
		if(other.id) {
			id = other.id;
			copy_func[other.id - 1](data, other.data);
		}
	}

	Variant(Variant &&other) {
		if(id) { this->~Variant(); }
		if(other.id) {
			id = other.id;
			move_func[other.id - 1](data, other.data);
		}
	}

	Variant &operator=(const Variant &other) {
		if(id) { this->~Variant(); }
		if(other.id) {
			id = other.id;
			copy_func[other.id - 1](data, other.data);
		}
		return *this;
	}

	Variant &operator=(Variant &&other) {
		if(id) { this->~Variant(); }
		if(other.id) {
			id = other.id;
			move_func[other.id - 1](data, other.data);
		}
		return *this;
	}

	template<class T>
	Variant(T && v) {
		static_assert(IndexOf<std::remove_reference_t<T>, TS...>::value, "T not in type list\n");
		id = IndexOf<T, TS...>::value;
		new(data) std::remove_reference_t<T>(std::forward<T>(v));
	}

	template<class T>
	Variant & operator= (T && v) {
		static_assert(IndexOf<std::remove_reference_t<T>, TS...>::value, "T not in type list\n");
		destroy_func[id - 1](data);
		id = IndexOf<T, TS...>::value;
		new(data) std::remove_reference_t<T>(std::forward<T>(v));
		return *this;
	}

	template<unsigned k>
	typename SelectType<k, TS...>::type & get() {
		return *reinterpret_cast<typename SelectType<k, TS...>::type *>(data);
	}

	template<class T>
	std::remove_reference_t<T> & get() {
		static_assert(IndexOf<T, TS...>::value, "T not in type list\n");
		dynamic_assert(has<T>());
		return *reinterpret_cast<T *>(data);
	}

	template<class T>
	bool has() {
		static_assert(IndexOf<T, TS...>::value, "T not in type list\n");
		return IndexOf<T, TS...>::value == id;
	}

	~Variant() {
		if(id) destroy_func[id - 1](data);
		id = 0;
	}
};

template<class... TS>
constexpr typename Variant<TS...>::destructor_t Variant<TS...>::destroy_func[];

template<class... TS>
constexpr typename Variant<TS...>::copy_func_t Variant<TS...>::copy_func[];

template<class... TS>
constexpr typename Variant<TS...>::move_func_t Variant<TS...>::move_func[];

class A {
public:
	A() { std::cout << "make A\n"; }
	A(const A&a) { std::cout << "copy A\n"; }
	A(A&&a) { std::cout << "move A\n"; }
	~A() { std::cout << "del A\n"; }
};

int main() {
	std::vector<Variant<int, A, std::string>> v;
	v.reserve(100);

	A a;
	int i;

	A &ref_a = a;
	int &ref_i = i;

	A &&rref_a = A();
	int &&rref_i = 3;

#define EXEC(...) do { std::cout << __LINE__ << ": "; __VA_ARGS__ } while(0)
	EXEC(v.push_back(std::string(":<{[]}>:")););
	EXEC(std::cout << v.back().has<std::string>() << std::endl;);
	EXEC(std::cout << v.back().get<std::string>() << std::endl;);
	EXEC(v.push_back(std::move(a)););
	EXEC(v.push_back(i););
	EXEC(v.push_back(A()););
	EXEC(v.push_back(3););
	EXEC(v.push_back(ref_a););
	EXEC(v.push_back(ref_i););
	EXEC(v.push_back(rref_a););
	EXEC(v.push_back(rref_i););

	return 0;
}
