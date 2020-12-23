CC = g++
CPPFLAGS = -g -Wall -std=c++11
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

test: FORCE $(BIN_DIR) $(BIN_DIR)/stonesTest
	valgrind --leak-check=yes ./$(BIN_DIR)/stonesTest

$(BIN_DIR)/stonesTest: $(BIN_DIR)/stonesTest.o $(BIN_DIR)/stones.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/stonesTest.o: stonesTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/stones.o: stones.cpp stones.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

FORCE: ;

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

stonesTest: $(BIN_DIR) $(BIN_DIR)/stonesTest
	valgrind --leak-check=yes ./$(BIN_DIR)/stonesTest
