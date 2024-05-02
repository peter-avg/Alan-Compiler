.PHONY: all clean distclean

CXX = g++ 
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -O3 -g
SRCS = alan.cpp

all: 
	$(MAKE) -C ../build/macos/
	$(CXX) $(CXXFLAGS) $(SRCS) -o ../test/alan

clean:
	$(MAKE) clean -C ../build/macos/
	rm -f ../out.ll ../out.s ../a.out ../out
	rm -rf ../dSYM ../alan.dSYM

distclean: clean
	rm -f ../test/alan ./comp


