SRC_DIR := ../../src
MAIN_DIR := ../..
LIB_DIR := $(SRC_DIR)/library
CMD_DIR := $(MAIN_DIR)/cmd

CC := g++
CXXFLAGS := -Wfatal-errors -std=c++14
LLVM_FLAGS := $(shell llvm-config --ldflags --libs)

OBJS := $(SRC_DIR)/parser/parser.cpp $(SRC_DIR)/symbol/symbol.cpp $(SRC_DIR)/errors/errors.cpp \
        $(SRC_DIR)/lexer/lexer.cpp $(SRC_DIR)/correcting/correcting.cpp $(SRC_DIR)/types/types.cpp \
        $(SRC_DIR)/ast/printOn.cpp $(SRC_DIR)/ast/semantic.cpp $(SRC_DIR)/ast/interpret.cpp \
        $(SRC_DIR)/IR/IR.cpp $(SRC_DIR)/IR/gen.cpp

.PHONY: all clean
all: comp $(SRC_DIR)/library/library.a

comp: $(OBJS) $(SRC_DIR)/lexer/lexer.cpp $(SRC_DIR)/parser/parser.cpp $(SRC_DIR)/library/library.a
	$(CC) $(OBJS) $(LLVM_FLAGS) $(CXXFLAGS) $(LIB_DIR)/library.a -o $(CMD_DIR)/$@

$(SRC_DIR)/library/library.a: $(SRC_DIR)/library/library.o
	ar rcs $@ $^

$(SRC_DIR)/lexer/lexer.cpp: $(SRC_DIR)/lexer/lexer.l $(SRC_DIR)/lexer/lexer.h
	flex -o $@ $<

$(SRC_DIR)/parser/parser.cpp: $(SRC_DIR)/parser/parser.y
	bison -d -o $@ $<

$(SRC_DIR)/library/library.o: $(SRC_DIR)/library/library.cpp
	$(CC) -c $< -o $@

clean:
	rm -rf $(CMD_DIR)/comp $(SRC_DIR)/library/library.a $(SRC_DIR)/library/library.o \
	$(SRC_DIR)/lexer/lexer.cpp $(SRC_DIR)/parser/parser.cpp $(SRC_DIR)/parser/parser.hpp

