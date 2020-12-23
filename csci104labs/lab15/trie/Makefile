CC = g++
CPPFLAGS = -g -Wall -std=c++11
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all test tests: $(BIN_DIR) $(BIN_DIR)/TrieTest
	valgrind --leak-check=yes ./$(BIN_DIR)/TrieTest

TrieTest: $(BIN_DIR) $(BIN_DIR)/TrieTest
	valgrind --leak-check=yes ./$(BIN_DIR)/TrieTest

$(BIN_DIR)/TrieTest: $(TEST_DIR)/TrieTest.cpp $(BIN_DIR)/trie.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/trie.o: trie.cpp trie.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean test

clean:
	rm -rf $(BIN_DIR)
