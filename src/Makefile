OBJS = ./errors/errors.cpp ./lexer/lexer.cpp ./library/library.cpp ./parser/parser.cpp ./correcting/correcting.cpp ./types/types.cpp ./symbol/symbol.cpp ./ast/ast.cpp
CC = g++
CPP = c++14
FLAGS = -Wfatal-errors -std=$(CPP) -fsanitize=address -fno-omit-frame-pointer
REMOVE = rm -r *.dSYM

.PHONY: clean main

default: alan

lexer.cpp: ./lexer/lexer.l ./lexer/lexer.h
	flex -o ./lexer/lexer.cpp ./lexer/lexer.l

parser.cpp: ./parser/parser.y
	bison -d -Wcounterexamples -o ./parser/parser.cpp ./parser/parser.y

errors.cpp: ./errors/errors.hpp

library.cpp: ./library/library.hpp

correcting.cpp: ./correcting/correcting.hpp

types.cpp: ./types/types.hpp

symbol.cpp: ./symbol/symbol.hpp

ast.cpp: ./ast/ast.hpp

alan: lexer.cpp parser.cpp errors.cpp library.cpp correcting.cpp types.cpp symbol.cpp ast.cpp
	$(CC) $(FLAGS) $(OBJS) -o alan

clean:
	rm -f alan
