#include <iostream>
#include <algorithm>

#include "bincombos.h"
#include "gtest/gtest.h"

void printVector(std::vector<std::string> input) {
	for(int i = 0; i < (int)input.size(); i++) {
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

void printError(std::vector<std::string> expected, std::vector<std::string> actual) {
	std::cout << "Expected: ";
	printVector(expected);
	std::cout << "But Found: ";
	printVector(actual);
}

bool compareVectors(std::vector<std::string>& first, std::vector<std::string>& second){
	if(first.size() != second.size()){
		printError(first, second);
		return false;
	}

	sort(first.begin(), first.end());
	sort(second.begin(), second.end());

	for(size_t i = 0; i < first.size(); i++) {
		if(first[i] != second[i])  {
			printError(first, second);
			return false;
		}
	}
	return true;
}

TEST(BinCombosTest, Zero) {
	BinaryCombos b;

	std::vector<std::string> studentVec = b.generate(0);

	EXPECT_TRUE(studentVec.empty());	
}

TEST(BinCombosTest, One) {
	BinaryCombos b;

	std::vector<std::string> studentVec = b.generate(1);
	std::vector<std::string> expectedVec = {"0", "1"};

	EXPECT_TRUE(compareVectors(expectedVec, studentVec));	
}

TEST(BinCombosTest, Three) {
	BinaryCombos b;

	std::vector<std::string> studentVec = b.generate(3);
	std::vector<std::string> expectedVec = {"000","001","010","011","100","101","110","111"};

	EXPECT_TRUE(compareVectors(expectedVec, studentVec));	
}

TEST(BinCombosTest, Large) {
	BinaryCombos b;

	std::vector<std::string> studentVec = b.generate(6);
	std::vector<std::string> expectedVec = {"000000","000001","000010","000011","000100","000101","000110","000111","001000","001001","001010","001011","001100","001101","001110","001111","010000","010001","010010","010011","010100","010101","010110","010111","011000","011001","011010","011011","011100","011101","011110","011111","100000","100001","100010","100011","100100","100101","100110","100111","101000","101001","101010","101011","101100","101101","101110","101111","110000","110001","110010","110011","110100","110101","110110","110111","111000","111001","111010","111011","111100","111101","111110","111111"};

	EXPECT_TRUE(compareVectors(expectedVec, studentVec));	
}