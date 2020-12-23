CXX = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: msort-test

msort-test: msort-test.cpp msort.h
	$(CXX) $(CPPFLAGS) msort-test.cpp -o msort-test
	
