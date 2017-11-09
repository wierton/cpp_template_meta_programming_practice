#include <vector>
#include <utility>
#include <iostream>

class Copy {
	std::string s;
public:
	Copy();
	Copy(const std::string &s);
	Copy(const Copy &other);
	Copy(Copy && other);
	~Copy();

	Copy & operator=(const Copy & other);
	Copy & operator=(Copy && other);

	void set(std::string &&s);

	friend std::ostream & operator << (std::ostream &os, const Copy & c);
};

std::ostream & operator << (std::ostream &os, const Copy & c) {
	os << c.s;
}

void Copy::set(std::string &&s) {
	this->s = std::move(s);
}

Copy::Copy() {
}

Copy::Copy(const std::string &s) :
	s(s) {
	std::cout << "call constructor..." << std::endl;
}

Copy::Copy(const Copy &other) :
	s(other.s) {
	std::cout << "call copy constructor..." << s << std::endl;
}

Copy::Copy(Copy &&other) :
	s(std::move(other.s)) {
	std::cout << "call move constructor..." << s << std::endl;
}

Copy & Copy::operator=(const Copy &other) {
	s = other.s;
	std::cout << "call copy assign..." << s << std::endl;
}

Copy & Copy::operator=(Copy &&other) {
	s = std::move(other.s);
	std::cout << "call move assign..." << s << std::endl;
}

Copy::~Copy() {
	std::cout << "call deconstructor..." << s << std::endl;
	s.std::string::~string();
}

int main() {
	Copy cc(std::string("123456"));
	std::vector<Copy> v;

	std::cout << "------------------------\n";
	std::cout << "move(c)..." << std::endl;
	Copy c(std::move(cc));

	std::cout << "------------------------\n";
	std::cout << "push_back(c)..." << std::endl;
	v.push_back(c);

	std::cout << "------------------------\n";
	c.set(std::string("abcdef"));
	std::cout << "push_back(move(c))..." << std::endl;
	v.push_back(std::move(c));

	std::cout << "------------------------\n";
	std::cout << "c now is '" << c << "'" << std::endl;

	std::cout << "------------------------\n";
	std::vector<Copy> vv(std::move(v));
	std::cout << "v.size = " << v.size() << std::endl;
	std::cout << "vv.size = " << vv.size() << std::endl;

	return 0;
}
