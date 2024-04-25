.PHONY: all clean distclean
CXX = g++ 
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -O3 -g
OBJS = alan.cpp
MAKE = make

all: 
	$(MAKE) -C ../build/macos/ && { $(CXX) $(CXXFLAGS) $(OBJS) -o ../alan; } && rm -rf ../dSYM ../alan.dSYM

clean:
	$(MAKE) clean -C ../build/macos/ && rm -f ../out.ll ../out.s && rm -rf ../dSYM ../alan.dSYM > /dev/null 2>&1

distclean: clean
	rm -f ../alan ./comp ../a.out ../out > /dev/null 2>&1

