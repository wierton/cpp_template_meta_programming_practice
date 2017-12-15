#ifndef TRAITS_H
#define TRAITS_H

#include <string>
#include <vector>
#include <cstddef>

namespace traits {

template<class T>
class is_class {
	using yes = char[1];
	using no = char[2];

	template<class U>
	static yes & test(void (U::*)());
	template<class U>
	static no & test(...);
public:
	enum { value = sizeof(test<T>(0)) == sizeof(yes) };
};

template<class T>
struct not_ : std::integral_constant<bool, !T::value> { };


template<class T1, class T2>
struct is_same : std::integral_constant<bool, false> { };

template<class T>
struct is_same<T, T> : std::integral_constant<bool, true> { };


template<class T>
struct is_integral {
	static constexpr bool value = 
		is_same<T, char>::value
		|| is_same<T, short>::value
		|| is_same<T, long>::value
		|| is_same<T, int>::value
		|| is_same<T, long long>::value
		|| is_same<T, unsigned char>::value
		|| is_same<T, unsigned short>::value
		|| is_same<T, unsigned long>::value
		|| is_same<T, unsigned int>::value
		|| is_same<T, unsigned long long>::value;
};

template<class T>
struct is_float {
	static constexpr bool value =
		is_same<T, float>::value || is_same<T, double>::value;
};


template<class T>
struct is_array {
	static constexpr bool value = false;
};

template<class T>
struct is_array<T []> {
	static constexpr bool value = true;
};

template<class T>
struct is_void : std::integral_constant<bool, is_same<T, void>::value> {};


template<class T>
struct is_pointer : std::integral_constant<bool, false> { };

template<class T>
struct is_pointer<T*> : std::integral_constant<bool, true> {};



/* format */
template<class T>
struct format {
	static std::string to_string() {
		return std::string("<BAD>");
	}
};

#define TYPE_DESCRIPTOR(bt)							\
template<>											\
struct format<bt> {						\
	static std::string to_string() {			\
		return std::string(#bt);					\
	}												\
};


TYPE_DESCRIPTOR(void)
TYPE_DESCRIPTOR(char)
TYPE_DESCRIPTOR(short)
TYPE_DESCRIPTOR(int)
TYPE_DESCRIPTOR(long long)
TYPE_DESCRIPTOR(long int)
TYPE_DESCRIPTOR(unsigned char)
TYPE_DESCRIPTOR(unsigned short)
TYPE_DESCRIPTOR(unsigned int)
TYPE_DESCRIPTOR(unsigned long long)
TYPE_DESCRIPTOR(signed char)
TYPE_DESCRIPTOR(nullptr_t)

#undef TYPE_DESCRIPTOR

template<class T>
struct format<T *> {
	static std::string to_string() {
		return std::string(format<T>::to_string()) + std::string(" *");
	}
};

template<class T>
struct format<const T> {
	static std::string to_string() {
		return std::string("const ") + std::string(format<T>::to_string());
	}
};

template<class T>
struct format<T []> {
	static std::string to_string() {
		return std::string(format<T>::to_string()) + std::string(" []");
	}
};

template<class T, unsigned N>
struct format<T [N]> {
	static std::string to_string() {
		return std::string(format<T>::to_string()) + std::string(" [") + std::to_string(N) + std::string("]");
	}
};

template<class T>
struct format<T &> {
	static std::string to_string() {
		return std::string(format<T>::to_string()) + std::string(" &");
	}
};

template<class T>
struct format<T &&> {
	static std::string to_string() {
		return std::string(format<T>::to_string()) + std::string(" &&");
	}
};


/* format function arguments */
template<class... Args>
struct function_arguments_descriptor {
	static std::string to_string() {
		std::vector<std::string> argsFormatStrings = std::move( std::vector<std::string> { format<Args>::to_string()... } );

		std::string retString = "(";

		if(argsFormatStrings.size() > 0)
			retString += argsFormatStrings[0];

		for(int i = 1; i < argsFormatStrings.size(); i++) {
			retString += ( ", " + argsFormatStrings[i] );
		}

		retString += ")";
		return retString;
	}
};

template<class T, class... Args>
struct format<T (*)(Args...)> {
	static std::string to_string() {
		return format<T>::to_string()  + "(*)" + function_arguments_descriptor<Args...>::to_string();
	}
};

template<class T, class... Args>
struct format<T (Args...)> {
	static std::string to_string() {
		return format<T>::to_string()  + function_arguments_descriptor<Args...>::to_string();
	}
};


};

#endif
