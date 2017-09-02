.PHONY: run


CXXFILES := smq_regex.cpp
TARGET := a.out

$(TARGET): $(CXXFILES)
	g++ -ggdb -std=c++17 $^ -o $@

run:$(TARGET)
	@./$(TARGET)
