#include <iostream>
 
// 计算 N 的阶乘 N!
template<int N>
class aTMP{
public:
    enum { ret = N==0 ? 1 : N * aTMP<N-1>::ret }; // Lazy Instantiation，将产生无限递归!
};
 
int main(){
    std::cout << aTMP<10>::ret << '\n';
    std::cin.get();
	return 0;
}
