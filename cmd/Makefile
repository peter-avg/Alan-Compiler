.PHONY: all clean distclean install-path

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
	$(MAKE) clean -C ../build/macos/
	rm -f ../out.ll ../out.s ../a.out ../out ../bin/out.ll ../bin/out.s ../bin/a.out ../bin/out
	rm -rf ../dSYM ../alan.dSYM ../bin/alan.dSYM ../bin/dSYM

distclean: clean
	rm -f ../bin/alan ../bin/comp


