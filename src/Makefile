OBJS = ./errors/errors.cpp ./lexer/lexer.cpp ./library/library.cpp \
	   ./parser/parser.cpp ./correcting/correcting.cpp ./types/types.cpp \
	   ./symbol/symbol.cpp ./ast/ast.cpp ./ast/interpret.cpp
CC = g++
CPP = c++14
FLAGS = -Wfatal-errors -std=$(CPP)
REMOVE = rm -r *.dSYM

.PHONY: clean main

default: alan

lexer.cpp: ./lexer/lexer.l ./lexer/lexer.h
	flex -o ./lexer/lexer.cpp ./lexer/lexer.l

parser.cpp: ./parser/parser.y
	bison -d -Wcounterexamples -o ./parser/parser.cpp ./parser/parser.y

alan: $(OBJS) lexer.cpp parser.cpp
	$(CC) $(FLAGS) $(OBJS) -o alan

clean:
	rm -f alan
