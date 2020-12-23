CXX = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: color

color: color.cpp
	$(CXX) $(CPPFLAGS) color.cpp -o color

clean:
		rm -f *.o color
