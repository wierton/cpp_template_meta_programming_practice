.PHONY: run

# CXXFILES := practice_2.cc
# CXXFILES := traits.cc
# CXXFILES := print.cc
CXXFILES := forward.cc
TARGET := a.out

$(TARGET): $(CXXFILES)
	g++ -ggdb -std=c++17 $^ -o $@

run:$(TARGET)
	@./$(TARGET)

clean:
	@rm -rf $(TARGET)
