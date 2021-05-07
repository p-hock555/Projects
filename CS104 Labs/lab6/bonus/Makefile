CC = g++
CPPFLAGS = -g -Wall -std=c++11
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

test: FORCE $(BIN_DIR) $(BIN_DIR)/sequenceTest $(BIN_DIR)/bincombosTest $(BIN_DIR)/sumTest $(BIN_DIR)/searchTest
	 ./$(BIN_DIR)/sequenceTest
	 ./$(BIN_DIR)/bincombosTest
	 ./$(BIN_DIR)/sumTest
	 ./$(BIN_DIR)/searchTest

$(BIN_DIR)/sequenceTest: $(BIN_DIR)/sequenceTest.o $(BIN_DIR)/sequence.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/sequenceTest.o: sequenceTest.cpp sequence.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/sequence.o: sequence.cpp sequence.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/bincombosTest: $(BIN_DIR)/bincombosTest.o $(BIN_DIR)/bincombos.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/bincombosTest.o: bincombosTest.cpp bincombos.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/bincombos.o: bincombos.cpp bincombos.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/sumTest: $(BIN_DIR)/sumTest.o $(BIN_DIR)/LinkedList.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/sumTest.o: sumTest.cpp LinkedList.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/LinkedList.o: LinkedList.cpp LinkedList.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/searchTest: $(BIN_DIR)/searchTest.o $(BIN_DIR)/search.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/searchTest.o: searchTest.cpp search.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/search.o: search.cpp search.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

FORCE: ;

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

sequenceTest: $(BIN_DIR) $(BIN_DIR)/sequenceTest
	 ./$(BIN_DIR)/sequenceTest

bincombosTest: $(BIN_DIR) $(BIN_DIR)/bincombosTest
	./$(BIN_DIR)/bincombosTest

sumTest: $(BIN_DIR) $(BIN_DIR)/sumTest
	 ./$(BIN_DIR)/sumTest

searchTest: $(BIN_DIR) $(BIN_DIR)/searchTest
	 ./$(BIN_DIR)/searchTest

