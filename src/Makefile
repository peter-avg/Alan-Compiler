OBJS = ./errors/errors.cpp ./lexer/lexer.cpp
CC = c++
CPP = c++11
FLAGS = -Wall -g -std=$(CPP)

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o main

clean:
	rm -f main
