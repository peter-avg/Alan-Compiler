OBJS = ./errors/errors.cpp ./lexer/lexer.cpp ./library/library.cpp ./parser/parser.cpp
CC = g++
CPP = c++11
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

alan: lexer.cpp parser.cpp errors.cpp library.cpp 
	$(CC) $(FLAGS) $(OBJS) -o alan

clean:
	rm -f alan
