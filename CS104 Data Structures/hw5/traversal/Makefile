CXX = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: expr-tester

expr-tester: expr-tester.cpp expr-reader.o expr-ops.o
	$(CXX) $(CPPFLAGS) expr-tester.cpp expr-reader.o expr-ops.o -o expr-tester

expr-reader.o: expr-reader.cpp expr-reader.h
	$(CXX) $(CPPFLAGS) -c expr-reader.cpp -o expr-reader.o

expr-ops.o: expr-ops.cpp expr-ops.h expr-reader.h
	$(CXX) $(CPPFLAGS) -c expr-ops.cpp -o expr-ops.o

clean:
	rm -f *.o expr-tester
