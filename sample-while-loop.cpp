#include <iostream>

template <bool c, typename Then, typename Else> struct IF {};
template <typename Then, typename Else> struct IF<true, Then, Else> {
	typedef Then reType;
};


template <typename Then, typename Else> struct IF<false, Then, Else> {
	typedef Else reType;
};

// 隐含要求： Condition 返回值 ret，Statement 有类型 Next
template <template <typename> class Condition, typename Statement>
struct WHILE {
	template <typename Statement_>
	struct STOP {
		typedef Statement_ reType;
	};

	typedef typename IF<Condition<Statement>::ret,
			WHILE<Condition, typename Statement::Next>,
			STOP<Statement>>::reType::reType reType;
};

// 计算 1^e+2^e+...+n^e
template <int n, int e> struct sum_pow {
	template <int i, int e_> struct pow_e {
		enum { ret = i * pow_e<i, e_ - 1>::ret };
	};

	template <int i> struct pow_e<i, 0> {
		enum { ret = 1 };
	};

	// 计算 i^e，嵌套类使得能够定义嵌套模板元函数，private 访问控制隐藏实现细节
	template <int i> struct pow {
		enum { ret = pow_e<i, e>::ret };
	};

	template <typename stat> struct cond {
		enum { ret = (stat::ri <= n) };
	};

	template <int i, int sum> struct stat {
		typedef stat<i + 1, sum + pow<i>::ret> Next;
		enum { ri = i, ret = sum };
	};

	enum { ret = WHILE<cond, stat<1, 0>>::reType::ret };
};

int main() {
	std::cout << sum_pow<10, 2>::ret << '\n';
	return 0;
}
