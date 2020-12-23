CXX = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: llrec-test

llrec-test: llrec-test.cpp llrec.o
	$(CXX) $(CPPFLAGS) llrec-test.cpp llrec.o -o llrec-test

llrec.o: llrec.cpp llrec.h
	$(CXX) $(CPPFLAGS) -c llrec.cpp -o llrec.o

clean:
	rm -f *.o gitint-shell
