#include <iostream>
#include <sstream>
#include "traits.h"


template<class... Args>
void print(Args... args) {
	std::initializer_list<int> {(std::cout << args << " ", 0)...};
}

template<class... Args>
void println(Args... args) {
	print(args...);
	std::cout << std::endl;
}


inline void streamprint(std::ostream &os, const char * fmt) {
	while(*fmt) {
		os << *fmt;
		fmt ++;
	}
}

template<class T, class... Args>
void streamprint(std::ostream &os, const char * fmt, T firstArg, Args... restArgs) {
	while(*fmt) {
		if(*fmt == '%') {
			fmt ++;
			if(*fmt == '%') {
				os << '%';
				fmt ++;
				continue;
			} else {
				os << firstArg;
				streamprint(os, fmt, restArgs...);
				return;
			}
		}
		os << *fmt;
		fmt ++;
	}
}

template<class... Args>
void log(const char *fmt, Args... args) {
	streamprint(std::cout, fmt, args...);
}

template<class... Args>
void sprint(std::string &sout, const char *fmt, Args... args) {
	std::ostringstream os;
	streamprint(os, fmt, args...);
	sout = std::move(os.str());
}

int main() {
	print(1, 2, 3, 4, 5);
	log("\n132 is % and % %%\n", 123, 789);

	std::string s;
	std::ostringstream sout;
	sout << "hello world";
	sout.flush();
	log("s is '%','%', type:'%'\n", s, sout.str());
	sprint(s, "s is '%','%', type:'%'\n", s, sout.str());
	log("sprint %", s);
	return 0;
}
