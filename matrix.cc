#include <iostream>
#include <random>
#include <sstream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
#include <memory>
#include <cstdlib>
#include <cmath>
#include <type_traits>
#include <initializer_list>

std::mt19937 &random_engine() {
	static std::shared_ptr<std::mt19937> engine_ptr(nullptr);
	if(engine_ptr.get() == nullptr) {
		engine_ptr.reset(new std::mt19937(102));
	}
	return *engine_ptr;
}

double uniform_real(double st, double ed) {
	std::uniform_real_distribution<> dis(st, ed);
	return dis(random_engine());
}

int64_t uniform_int(int64_t st, int64_t ed) {
	std::uniform_int_distribution<int64_t> dis(st, ed);
	return dis(random_engine());
}


using LineType = std::vector<std::string>;
using FileType = std::vector<LineType>;
using CSVData = std::shared_ptr<FileType>;


template<class T>
using Vector = std::vector<T>;

template<class T>
using Matrix = Vector<Vector<T>>;

template<class T, unsigned N>
struct TensorType {
	using type = Vector<typename TensorType<T, N - 1>::type>;
};

template<class T>
struct TensorType<T, 1> {
	using type = Vector<T>;
};


template<class T>
inline size_t GetRow(const Matrix<T> &m) { return m.size(); }

template<class T>
inline size_t GetCol(const Matrix<T> &m) { return m[0].size(); }

template<class T>
class Iterable {
	using no = char[1];
	using yes = char[2];

	template<class C>
	static yes & test(typename C::iterator *);
	template<class C>
	static no & test(...);
public:
	static constexpr auto value =
		sizeof(test<std::remove_reference_t<T>>(0)) == sizeof(yes);
};


template<class T>
class Dimension {
	template<bool Cond, class U>
	struct DimensionImply {
		using value_type = typename std::remove_reference_t<U>::value_type;
		enum { value = 1 + Dimension<value_type>::value };
	};

	template<class U>
	struct DimensionImply<false, U> {
		enum { value = 0 };
	};
public:
	enum { value = DimensionImply<Iterable<T>::value, T>::value };
};


template<class T>
std::enable_if_t<Dimension<T>::value == 1, std::ostream &>
operator<<(std::ostream &os, const T &v) {
	auto it = v.begin();
	if(it != v.end()) os << *it;

	for(it ++; it != v.end(); it ++)
		os << "," << *it;
	return os;
}

template<class T>
std::enable_if_t<Dimension<T>::value == 2, std::ostream &>
operator<<(std::ostream &os, const T &matrix) {
	for(auto &v : matrix)
		os << v << "\n";
	return os;
}

inline void trim(std::string &s) {
	s.erase(0, s.find_first_not_of(" \n\r\t"));
	s.erase(s.find_last_not_of(" \n\r\t") + 1);
}

CSVData csv_load(const char *filename) {
	CSVData data(new FileType);
	std::ifstream ifs(filename);
	std::string line;
	while(std::getline(ifs, line)) {
		data->push_back(LineType{});
		std::istringstream iss(std::move(line));
		std::string word;
		while(std::getline(iss, word, ',')) {
			trim(word);
			data->back().push_back(std::move(word));
		}
	}
	return data;
}

template<class T>
constexpr std::enable_if_t<!Iterable<T>::value, T> sigmoid(const T &x) {
	return 1 / (1 + std::exp(-x));
}

template<class T>
constexpr std::enable_if_t<Iterable<T>::value, T> sigmoid(const T &x) {
	auto ret = x;
	for(auto &e : ret)
		e = sigmoid(e);
	return ret;
}

template<class T>
constexpr std::enable_if_t<Iterable<T>::value, T> sigmoid(T &&x) {
	for(auto &e : x)
		e = sigmoid(e);
	return x;
}



#define DEFINE_OPERATOR_FOR_ITERABLE_TYPE(ope)			\
template<class T, class U>								\
constexpr std::enable_if_t<								\
Iterable<T>::value && std::is_arithmetic<U>::value, T&>	\
operator ope (T &a, const U &b) {						\
	for(auto it = a.begin(); it < a.end(); it ++) {		\
		*it ope b;										\
	}													\
	return a;											\
}

DEFINE_OPERATOR_FOR_ITERABLE_TYPE(+=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(-=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(*=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(/=);
#undef DEFINE_OPERATOR_FOR_ITERABLE_TYPE


#define DEFINE_OPERATOR_FOR_ITERABLE_TYPE(ope)			\
template<class T, class U>								\
constexpr std::enable_if_t<								\
Iterable<T>::value && Iterable<U>::value				\
&& Dimension<T>::value == Dimension<U>::value, T&>		\
operator ope (T &a, const U &b) {						\
	for(auto itl = a.begin(), itr = b.begin();			\
			itl < a.end() && itr < b.end();				\
			itl ++, itr ++) {							\
		*itl ope *itr;									\
	}													\
	return a;											\
}

DEFINE_OPERATOR_FOR_ITERABLE_TYPE(+=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(-=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(*=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(/=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(%=);
#undef DEFINE_OPERATOR_FOR_ITERABLE_TYPE


#define DEFINE_OPERATOR_FOR_ITERABLE_TYPE(op, ope)				\
template<class T, class U>										\
std::enable_if_t<												\
( Iterable<T>::value && Iterable<U>::value						\
  && (Dimension<T>::value == Dimension<U>::value)				\
  ), typename std::conditional<(								\
	  std::is_rvalue_reference<T&&>::value						\
	  || std::is_rvalue_reference<U&&>::value					\
	  ), T&, std::remove_reference_t<T>>::type>					\
operator op (T &&a, U &&b) {									\
	if constexpr (std::is_rvalue_reference<T&&>::value) {		\
		a ope b;												\
		return a;												\
	} else if constexpr (std::is_rvalue_reference<U&&>::value) {\
		b ope a;												\
		return b;												\
	} else {													\
		std::remove_reference_t<T> ret = a;						\
		for(auto itl = ret.begin(), itr = b.begin();			\
				itl < ret.end() && itr < b.end();				\
				itl ++, itr ++) {								\
			*itl = *itl op *itr;								\
		}														\
		return ret;												\
	}															\
}

DEFINE_OPERATOR_FOR_ITERABLE_TYPE(+, +=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(-, -=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(*, *=);
DEFINE_OPERATOR_FOR_ITERABLE_TYPE(/, /=);
#undef DEFINE_OPERATOR_FOR_ITERABLE_TYPE


template<class T, class DIM>
Vector<T> zeros(DIM n) {
	Vector<T> ret(n);
	for(auto &e:ret) e = 0;
	return ret;
}

template<class T, class DIM, class...DIMS>
typename TensorType<T, sizeof...(DIMS) + 1>::type
zeros(DIM n, DIMS...dims) {
	typename TensorType<T, sizeof...(DIMS) + 1>::type ret(n);
	for(auto &e:ret) e = zeros<T>(dims...);
	return ret;
}

template<class T, class DIM>
Vector<T> ones(DIM n) {
	Vector<T> ret(n);
	for(auto &e:ret) e = 1;
	return ret;
}

template<class T, class DIM, class...DIMS>
typename TensorType<T, sizeof...(DIMS) + 1>::type
ones(DIM n, DIMS...dims) {
	typename TensorType<T, sizeof...(DIMS) + 1>::type ret(n);
	for(auto &e:ret) e = ones<T>(dims...);
	return ret;
}

template<class T, class DIM>
Vector<T> random(DIM n) {
	Vector<T> ret(n);
	for(auto &e:ret) e = uniform_real(-1, 1);
	return ret;
}

template<class T, class DIM, class...DIMS>
typename TensorType<T, sizeof...(DIMS) + 1>::type
random(DIM n, DIMS...dims) {
	typename TensorType<T, sizeof...(DIMS) + 1>::type ret(n);
	for(auto &e:ret) e = random<T>(dims...);
	return ret;
}


Vector<double> meany(const Matrix<double> &x) {
	Vector<double> ret(GetCol(x));
	for(int i = 0; i < ret.size(); i++) {
		double sum = 0;
		for(int j = 0; j < x.size(); j++) {
			sum += x[j][i];
		}
		ret[i] = sum / x.size();
	}
	return ret;
}

template<class T>
Matrix<T> dot(const Matrix<T> &a, const Matrix<T> &b) {
	assert(GetCol(a) == GetRow(b));

	auto row = GetRow(a);
	auto col = GetCol(b);
	auto cr = GetCol(a);
	auto ret = zeros<T>(row, col);
	for(int i = 0; i < GetRow(a); i++) {
		for(int j = 0; j < GetCol(b); j++) {
			for(int k = 0; k < cr; k++)
				ret[i][j] += a[i][k] * b[k][j];
		}
	}
	return ret;
}



void tests() {
	Matrix<int> a = {{1,2},{3,4}};
	Matrix<int> b = {{1,2},{3,4}};
	auto c = (a + b) + (b + a);
	std::cout << c << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
}

int main() {
	tests();
	return 0;
}
