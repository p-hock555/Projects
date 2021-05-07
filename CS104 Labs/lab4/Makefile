CC = g++
CPPFLAGS = -g -Wall -std=c++11
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

test: FORCE $(BIN_DIR) $(BIN_DIR)/keyboardTest $(BIN_DIR)/messagePrinterTest 
	 ./$(BIN_DIR)/keyboardTest
	 ./$(BIN_DIR)/messagePrinterTest

$(BIN_DIR)/keyboardTest: $(BIN_DIR)/keyboardTest.o $(BIN_DIR)/keyboard.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/keyboardTest.o: keyboardTest.cpp keyboard.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/keyboard.o: keyboard.cpp keyboard.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/messagePrinterTest: $(BIN_DIR)/messagePrinterTest.o $(BIN_DIR)/messagePrinter.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/messagePrinterTest.o: messagePrinterTest.cpp messagePrinter.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/messagePrinter.o: messagePrinter.cpp messagePrinter.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

FORCE: ;

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

keyboardTest: $(BIN_DIR) $(BIN_DIR)/keyboardTest
	 ./$(BIN_DIR)/keyboardTest

messagePrinterTest: $(BIN_DIR) $(BIN_DIR)/messagePrinterTest
	 ./$(BIN_DIR)/messagePrinterTest

searchTest: $(BIN_DIR) $(BIN_DIR)/searchTest
	 ./$(BIN_DIR)/searchTest

