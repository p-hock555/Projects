CXX = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: heap-test

heap-test: heap-test.cpp heap.h
	$(CXX) $(CPPFLAGS) heap-test.cpp -o heap-test

clean:
	rm -f *.o heap-test
