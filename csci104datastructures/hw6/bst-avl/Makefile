CXX = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: bst-test

bst-test: bst-test.cpp avlbst.h bst.h print_bst.h
	$(CXX) $(CPPFLAGS) bst-test.cpp -o bst-test

clean:
		rm -f *.o bst-test
