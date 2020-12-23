CXX = g++
CPPFLAGS = -g -Wall -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: search-shell

search-shell: search-shell.cpp cmdhandler.o combiners.o handler.o md_parser.o searchui.o searcheng.o txt_parser.o util.o webpage.o
	$(CXX) $(CPPFLAGS) search-shell.cpp cmdhandler.o combiners.o handler.o md_parser.o searchui.o searcheng.o txt_parser.o util.o webpage.o -o search-shell

cmdhandler.o: cmdhandler.cpp cmdhandler.h util.h
	$(CXX) $(CPPFLAGS) -c cmdhandler.cpp -o cmdhandler.o

combiners.o: combiners.cpp searcheng.h
	$(CXX) $(CPPFLAGS) -c combiners.cpp -o  combiners.o

handler.o: handler.cpp handler.h
	$(CXX) $(CPPFLAGS) -c handler.cpp -o handler.o

md_parser.o: md_parser.cpp md_parser.h util.h
	$(CXX) $(CPPFLAGS) -c md_parser.cpp -o md_parser.o

searcheng.o: searcheng.cpp searcheng.h
	$(CXX) $(CPPFLAGS) -c searcheng.cpp -o searcheng.o

searchui.o: searchui.cpp searchui.h util.h
	$(CXX) $(CPPFLAGS) -c searchui.cpp -o searchui.o

txt_parser.o: txt_parser.cpp txt_parser.h util.h
	$(CXX) $(CPPFLAGS) -c txt_parser.cpp -o txt_parser.o

util.o: util.cpp util.h webpage.h
	$(CXX) $(CPPFLAGS) -c util.cpp -o util.o

webpage.o: webpage.cpp webpage.h util.h
	$(CXX) $(CPPFLAGS) -c webpage.cpp -o webpage.o

clean:
	rm -f *.o search-shell
