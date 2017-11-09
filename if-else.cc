#include <iostream>


template<bool cond, class T, class F> struct IF { };

template<class T, class F> struct IF<false, T, F> { typedef F TYPE; };

template<class T, class F> struct IF<true, T, F> { typedef T TYPE; };


class CollectGC {
public:
	void collect() { std::cout << "CollectGC::collect()\n"; }
};

class MarkAndSweepGC {
public:
	void collect() { std::cout << "MakrAndSweep::collect()\n"; }
};


int main() {
	IF<true, CollectGC, MarkAndSweepGC>::TYPE gc;
	gc.collect();

	return 0;
}
