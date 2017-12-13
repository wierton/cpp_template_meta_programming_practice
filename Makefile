.PHONY: run

# CXXFILES := practice_2.cc
# CXXFILES := traits.cc
# CXXFILES := print.cc
# CXXFILES := test.cc
# CXXFILES := higher-order-function.cc
CXXFILES := tuple.cc
TARGET := a.out

$(TARGET): $(CXXFILES)
	g++ -ggdb -std=c++17 $^ -o $@

run:$(TARGET)
	@./$(TARGET)

clean:
	@rm -rf $(TARGET)
