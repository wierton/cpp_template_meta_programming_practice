#include <iostream>

/* for test */
template<class T1, class T2>
struct is_same : std::__bool_constant<false> { };

template<class T>
struct is_same<T, T> : std::__bool_constant<true> { };


/*
 * 2-0. write a unary function add_const_ref<T>, return T if T is a reference type, return const T & otherwise.
 */
template<class T>
struct add_const_ref {
	typedef const T & type;
};

template<class T>
struct add_const_ref<T &> {
	typedef T & type;
};

void test_add_const_ref() {
	static_assert(is_same<add_const_ref<int>::type, const int &>::value, "add_const_ref<int>::type != const int &");
	static_assert(is_same<add_const_ref<int &>::type, int &>::value, "add_const_ref<int &>type != int &");
}

/*
 * 2-1. write a three variable function replace_type<c, x, y>,
 * it receive any compound type c as its first arguments and
 * replace type x by y for all x appears in c
 * note: you can limit the number of function arguments to 2
 * */
template<class T, class X, class Y, bool cond>
struct replace_type_impl {};

template<class T, class X, class Y>
struct replace_type {
	typedef typename replace_type_impl<T, X, Y, is_same<T, X>::value>::type type;
};

template<class T, class X, class Y>
struct replace_type_impl<T, X, Y, true> {
	typedef Y type;
};

template<class T, class X, class Y>
struct replace_type_impl<T *, X, Y, false> {
	typedef typename replace_type<T, X, Y>::type * type;
};

template<class T, class X, class Y>
struct replace_type_impl<T &, X, Y, false> {
	typedef typename replace_type<T, X, Y>::type & type;
};

template<class T, class X, class Y>
struct replace_type_impl<T &&, X, Y, false> {
	typedef typename replace_type<T, X, Y>::type && type;
};

template<class T, class X, class Y>
struct replace_type_impl<T [], X, Y, false> {
	typedef typename replace_type<T, X, Y>::type type[];
};

template<class T, class X, class Y, unsigned N>
struct replace_type_impl<T [N], X, Y, false> {
	typedef typename replace_type<T, X, Y>::type type[N];
};

template<class T, class X, class Y, class V>
struct replace_type_impl<T (*)(V), X, Y, false> {
	typedef typename replace_type<T, X, Y>::type (*type) (typename replace_type<V, X, Y>::type);
};

template<class T, class X, class Y, class V1, class V2>
struct replace_type_impl<T (*)(V1, V2), X, Y, false> {
	typedef typename replace_type<T, X, Y>::type (*type) (typename replace_type<V1, X, Y>::type, typename replace_type<V2, X, Y>::type);
};

void test_replace_type() {
	static_assert(is_same<replace_type<int *, int, char const>::type, const char *>::value, "int * --> const char *");
	static_assert(is_same<replace_type<int [], int, char const>::type, const char []>::value, "int [] --> const char []");
	static_assert(is_same<replace_type<int [4], int, char const>::type, const char [4]>::value, "int [4] --> const char [4]");
	static_assert(is_same<replace_type<int (*)(int, int), int, char const>::type, const char (*)(const char, const char)>::value, "int (*)(int, int) --> const char (*)(const char, const char)");
}

int main() {
	test_add_const_ref();
	return 0;
}
