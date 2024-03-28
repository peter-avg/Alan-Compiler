OBJS =  parser/parser.tab.c  ast/interpret.cpp ast/printOn.cpp \
		symbol/symbol.cpp errors/errors.cpp lexer/lex.yy.c \
		correcting/correcting.cpp types/types.cpp library/library.cpp 
CC = g++
CPP = c++14
REMOVE = rm -r *.dSYM

.PHONY: clean main

default: alan

lex.yy.c: ./lexer/lexer.l ./lexer/lexer.h
	flex ./lexer/lexer.l

parser.tab.c: ./parser/parser.y
	bison -d ./parser/parser.y

alan:  lex.yy.c parser.tab.c $(OBJS)
	$(CC) $(OBJS) -o alan

clean: 
	Remove-Item -Force alan

