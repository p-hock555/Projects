CC = g++
CPPFLAGS = -g -Wall -std=c++11
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

test: FORCE $(BIN_DIR) $(BIN_DIR)/levelOrderTest $(BIN_DIR)/evenOddTest 
	 ./$(BIN_DIR)/levelOrderTest
	 ./$(BIN_DIR)/evenOddTest

$(BIN_DIR)/levelOrderTest: $(BIN_DIR)/levelOrderTest.o $(BIN_DIR)/levelOrder.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/levelOrderTest.o: levelOrderTest.cpp levelOrder.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/levelOrder.o: levelOrder.cpp levelOrder.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/evenOddTest: $(BIN_DIR)/evenOddTest.o $(BIN_DIR)/evenOdd.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/evenOddTest.o: evenOddTest.cpp evenOdd.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/evenOdd.o: evenOdd.cpp evenOdd.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

FORCE: ;

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

levelOrderTest: $(BIN_DIR) $(BIN_DIR)/levelOrderTest
	 ./$(BIN_DIR)/levelOrderTest

evenOddTest: $(BIN_DIR) $(BIN_DIR)/evenOddTest
	 ./$(BIN_DIR)/evenOddTest
