.PHONY: all clean distclean install-path

MAIN_PATH = ../
BIN_PATH = $(MAIN_PATH)bin/
TEST_PATH = $(MAIN_PATH)test/examples/
BUILD_PATH = $(MAIN_PATH)build/
SRC_DIR = $(MAIN_PATH)src

CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -O3 -g
SRCS = alan.cpp
OS := $(shell uname)
EXPORT_PATH = $(shell pwd)/../bin
ALAN_LIB_VARIABLE_PATH = $(shell pwd)/../bin
ifeq ($(OS),Darwin)
	CXX = g++ 
else ifeq ($(OS),Linux)
	CXX = clang++
endif

all: install-path
ifeq ($(OS),Darwin)
	$(MAKE) -C ../build/macos/ > /dev/null
else ifeq ($(OS),Linux)
	$(MAKE) -C ../build/linux/ > /dev/null
endif
	@$(CXX) $(CXXFLAGS) $(SRCS) -o ../bin/alan
	@printf "\n%.0s" {1..50}
	@echo "source ~/.bashrc or ~/.zshrc to use alan"

install-path:
	@if [ -z "$$(grep '$(EXPORT_PATH)' ~/.bashrc)" ]; then \
		echo 'export PATH="$(EXPORT_PATH):$$PATH"' >> ~/.bashrc; \
		echo 'Added $(EXPORT_PATH) to PATH in ~/.bashrc'; \
	fi
	@if [ -z "$$(grep 'ALAN_LIB_VARIABLE_PATH' ~/.bashrc)" ]; then \
		echo 'export ALAN_LIB_VARIABLE_PATH="$(ALAN_LIB_VARIABLE_PATH)"' >> ~/.bashrc; \
		echo 'Added $(ALAN_LIB_VARIABLE_PATH) to ALAN_LIB_VARIABLE_PATH in ~/.bashrc'; \
	fi
	@if [ -z "$$(grep '$(EXPORT_PATH)' ~/.zshrc)" ]; then \
		echo 'export PATH="$(EXPORT_PATH):$$PATH"' >> ~/.zshrc; \
		echo 'Added $(EXPORT_PATH) to PATH in ~/.zshrc'; \
	fi
	@if [ -z "$$(grep 'ALAN_LIB_VARIABLE_PATH' ~/.zshrc)" ]; then \
		echo 'export ALAN_LIB_VARIABLE_PATH="$(ALAN_LIB_VARIABLE_PATH)"' >> ~/.zshrc; \
		echo 'Added $(ALAN_LIB_VARIABLE_PATH) to ALAN_LIB_VARIABLE_PATH in ~/.zshrc'; \
	fi

clean:
	rm $(SRC_DIR)/library/library.a $(SRC_DIR)/library/library.o \
	$(SRC_DIR)/lexer/lexer.cpp $(SRC_DIR)/parser/parser.cpp $(SRC_DIR)/parser/parser.hpp
	rm -f $(TEST_PATH)*.imm $(TEST_PATH)*.asm $(BIN_PATH)*.imm $(BIN_PATH)*.asm
	rm -rf $(BIN_PATH)dSYM $(BIN_PATH)alan.dSYM $(BIN_PATH)alan.dSYM $(BIN_PATH)dSYM


distclean: clean
	rm -f $(BIN_PATH)alan $(BIN_PATH)comp


