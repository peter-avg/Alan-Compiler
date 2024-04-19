.PHONY: all clean 
CXX = g++ 
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -O3 -g
OBJS = alan.cpp

all: 
	$(MAKE) -C ../build/macos/ && $(CXX) $(CXXFLAGS) $(OBJS) -o ../alan && rm -r ../dSYM ../alan.dSYM

clean:
	$(MAKE) clean -C ../build/macos/ && rm -f ../alan ../out.ll ../out.s && rm -r ../dSYM ../alan.dSYM
