#include "traits.h"
#include <type_traits>
#include <iostream>


template<class T>
void func(T arg) {
	// T &  arg
	// T && arg
	std::cout << traits::format<T>::to_string()
		<< "\t"
		<< traits::format<decltype(arg)>::to_string()
		<< "\n";
}

template<class T>
void func_rref(T && arg) {
	// T & && arg
	// T   && arg
	std::cout << traits::format<T>::to_string()
		<< "\t"
		<< traits::format<decltype(arg)>::to_string()
		<< "\n";
}

template<class T>
void func_lref(T & arg) {
	// T     & arg
	// T &   & arg
	// T &&  & arg
	std::cout << traits::format<T>::to_string()
		<< "\t"
		<< traits::format<decltype(arg)>::to_string()
		<< "\n";
}

// template<T> func(T &&)
// T &&         -> T
// const T &    -> const T &
// T &          -> T &

/* code in c++/utility */
template<typename _Tp>
constexpr _Tp&& std_forward(typename std::remove_reference<_Tp>::type& __t) noexcept
{ 
	std::cout << "call &  ";
	return static_cast<_Tp&&>(__t);
}

template<typename _Tp>
constexpr _Tp&& std_forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
{ 
	std::cout << "call && ";
	return static_cast<_Tp&&>(__t);
}

// forward lvalue
template<class T>
constexpr T && forward(std::remove_reference_t<T> & arg) noexcept {
	std::cout << "call &  ";
	return static_cast<T &&>(arg);
}

// forward rvalue
template<class T>
constexpr T && forward(std::remove_reference_t<T> && arg) noexcept {
	std::cout << "call && ";
	return static_cast<T &&>(arg);
}

void test_func(int & arg) { std::cout << "test_func(int &)\n"; }
void test_func(const int & arg) { std::cout << "test_func(const int &)\n"; }
void test_func(int && arg) { std::cout << "test_func(int &&)\n"; }

template<class T>
void before_forward(T && arg) {
	std::cout.width(13);
	std::cout << traits::format<T>::to_string();
	std::cout.width(13);
	std::cout << traits::format<decltype(arg)>::to_string();
	std::cout << "  ";
	test_func(forward<T>(arg));
}

template<class T>
void after_forward(T && arg) {
	std::cout.width(13);
	std::cout << traits::format<T>::to_string();
	std::cout.width(13);
	std::cout << traits::format<decltype(arg)>::to_string();
	std::cout << "  ";
	test_func(forward<T>(arg));
}

template<class T>
void my_forward(T && arg) {
	std::cout.width(13);
	std::cout << traits::format<T>::to_string();
	std::cout.width(13);
	std::cout << traits::format<decltype(arg)>::to_string();
	std::cout << "  ";
	test_func(forward<T>(arg));
}


int main() {
	const int const_lvalue = 9;
	int lvalue;
	int &lref = lvalue;
	int &&rref = 1;

	std::cout << traits::format<decltype(lvalue)>::to_string() << "\n";
	std::cout << traits::format<decltype(lref)>::to_string() << "\n";
	std::cout << traits::format<decltype(rref)>::to_string() << "\n";
	std::cout << traits::format<decltype(2)>::to_string() << "\n";

	std::cout << "native handler\n";
	std::cout << "============\n";
	test_func(lvalue);
	test_func(const_lvalue);
	test_func(std::move(lvalue));
	test_func(lref);
	test_func(rref);
	test_func(2);

	std::cout << "\n";

	std::cout << "before forward\n";
	std::cout << "============\n";
	before_forward(lvalue);
	before_forward(const_lvalue);
	before_forward(std::move(lvalue));
	before_forward(lref);
	before_forward(rref);
	before_forward(2);

	std::cout << "\n";

	std::cout << "after forward\n";
	std::cout << "============\n";
	after_forward(lvalue);
	after_forward(const_lvalue);
	after_forward(std::move(lvalue));
	after_forward(lref);
	after_forward(rref);
	after_forward(2);

	std::cout << "\n";

	std::cout << "my forward\n";
	std::cout << "============\n";
	my_forward(lvalue);
	my_forward(const_lvalue);
	my_forward(std::move(lvalue));
	my_forward(lref);
	my_forward(rref);
	my_forward(2);

	std::cout << "T" << "\t" << "typeof(arg)\n";
	std::cout << "\n";
	std::cout << "func(T arg)\n";
	std::cout << "============\n";
	func(lvalue);
	func(lref);
	func(rref);
	func(2);
	std::cout << "\n";
	std::cout << "func(T && arg)\n";
	std::cout << "============\n";
	func_rref(lvalue);
	func_rref(lref);
	func_rref(rref);
	func_rref(2);
	std::cout << "\n";
	std::cout << "func(T & arg)\n";
	std::cout << "============\n";
	func_lref(lvalue);
	func_lref(lref);
	func_lref(rref);
	std::cout << "============\n";
	return 0;
}
