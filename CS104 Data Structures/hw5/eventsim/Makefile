CXX = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: eventsim

eventsim: input_reader.o derived_events.o streetgrid.o eventsim.o
	$(CXX) $(CPPFLAGS) input_reader.o derived_events.o streetgrid.o eventsim.o -o eventsim

input_reader.o: input_reader.cpp input_reader.h
	$(CXX) $(CPPFLAGS) -c input_reader.cpp -o input_reader.o

streetgrid.o: streetgrid.cpp streetgrid.h derived_events.h
	$(CXX) $(CPPFLAGS) -c streetgrid.cpp -o streetgrid.o

derived_events.o: derived_events.cpp derived_events.h streetgrid.h
	$(CXX) $(CPPFLAGS) -c derived_events.cpp -o derived_events.o

eventsim.o: eventsim.cpp heap.h
	$(CXX) $(CPPFLAGS) -c eventsim.cpp -o eventsim.o

clean:
	rm -f *.o eventism
