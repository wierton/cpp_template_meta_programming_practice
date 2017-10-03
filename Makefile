.PHONY: run

# CXXFILES := practice_2.cpp
# CXXFILES := traits.cpp
CXXFILES := print.cpp
TARGET := a.out

$(TARGET): $(CXXFILES)
	g++ -ggdb -std=c++17 $^ -o $@

run:$(TARGET)
	@./$(TARGET)

clean:
	@rm -rf $(TARGET)
