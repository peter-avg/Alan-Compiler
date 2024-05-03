OBJS =  parser/parser.tab.c lexer/lex.yy.c ast/printOn.cpp ast/semantic.cpp\
		symbol/symbol.cpp errors/errors.cpp \
		correcting/correcting.cpp types/types.cpp library/library.cpp
CC = g++
CPP = c++14
REMOVE = rm -r *.dSYM 

.PHONY: clean main

default: alan

lexer/lex.yy.c: ./lexer/lexer.l ./lexer/lexer.h
	flex ./lexer/lexer.l

parser/parser.tab.c: ./parser/parser.y
	bison -d ./parser/parser.y

alan: lexer/lex.yy.c parser/parser.tab.c $(OBJS) 
	$(CC) $(OBJS) -o alan

clean: 
	Remove-Item -Force alan


