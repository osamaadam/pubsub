targets = main

cppComp = $(CROSS_TOOL)g++

flags = -Wall -Werror -std=c++17

all: clean $(targets)

$(targets):
	$(cppComp) $(flags) $@.cpp -o $@

clean:
	rm -f $(targets)
format:
	clang-format --style=file -i *.cpp *.hpp