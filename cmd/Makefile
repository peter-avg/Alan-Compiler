.PHONY: all clean distclean

CXX = g++ 
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -O3 -g
SRCS = alan.cpp
OS := $(shell uname)


all: 
ifeq ($(OS),Darwin)  # macOS
	$(MAKE) -C ../build/macos/
else ifeq ($(OS),Linux)
	$(MAKE) -C ../build/linux/
endif
	$(CXX) $(CXXFLAGS) $(SRCS) -o ../bin/alan

clean:
	$(MAKE) clean -C ../build/macos/
	rm -f ../out.ll ../out.s ../a.out ../out ../bin/out.ll ../bin/out.s ../bin/a.out ../bin/out
	rm -rf ../dSYM ../alan.dSYM ../bin/alan.dSYM ../bin/dSYM

distclean: clean
	rm -f ../bin/alan ../bin/comp


