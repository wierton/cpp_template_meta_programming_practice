#include <iostream>

template<bool COND, class T, class F>
struct {
};

template<class T, class F>
struct<false, T, F> {
	typedef F RET;
};

template<class T, class F>
struct<true, T, F> {
	typedef T RET;
};

template<class COND, class STATEMENT>
struct WHILE {
	IF<COND, WHILE<COND, STATEMENT>::>
};
