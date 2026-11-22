CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

all: minic

minic: parser.tab.cpp lex.yy.c src/ast.cpp src/main.cpp
	$(CXX) $(CXXFLAGS) -Isrc -I. parser.tab.cpp lex.yy.c src/ast.cpp src/main.cpp -o minic

parser.tab.cpp parser.tab.hpp: src/parser.y
	bison -d -o parser.tab.cpp src/parser.y

lex.yy.c: src/lexer.l parser.tab.hpp
	flex -o lex.yy.c src/lexer.l

clean:
	rm -f minic parser.tab.cpp parser.tab.hpp lex.yy.c

.PHONY: all clean
