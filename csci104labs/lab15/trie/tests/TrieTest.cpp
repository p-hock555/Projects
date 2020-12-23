#include "gtest/gtest.h"
#include "../trie.h"

#include <vector>
#include <iostream>
#include <random>
#include <set>

using namespace std;

string gen_random() {
	string temp;
	int len = rand() % 10;
    for (int i = 0; i < len; ++i) {
        temp += rand() % 2 + '0';
    }

    return temp;
}

void allPermutationsHelper(string curr, int counter, set<string>& all) {
	if(counter == 0){
		all.insert(curr);
		return;
	}
	counter--;
	string withZero = curr + "0";
	string withOne = curr + "1";
	allPermutationsHelper(curr, counter, all);
	allPermutationsHelper(withZero, counter, all);
	allPermutationsHelper(withOne, counter, all);
}

set<string> allPermutations(int length) {
	set<string> container;
	allPermutationsHelper("", length, container);
	container.erase(container.find(""));
	return container;
}

bool check_trie(int num, set<string>& contains, Trie& test) {
	set<string> notInTrie = allPermutations(num);
	for(string str : contains) {
		if(notInTrie.find(str) != notInTrie.end()) notInTrie.erase(notInTrie.find(str));
	}
	for(string str : contains) {
		if(!test.exists(str)) return false;
	}
	for(string str : notInTrie) {
		if(test.exists(str)) return false;
	}
	return true;
}

TEST(TrieTest, TestInsertBasicInsert) {
	Trie test;
	test.insert("0");
    ASSERT_TRUE(test.exists("0"));
    ASSERT_FALSE(test.exists("1"));
    ASSERT_FALSE(test.exists("01"));
    ASSERT_FALSE(test.exists("10"));
    ASSERT_FALSE(test.exists("00"));
}

TEST(TrieTest, TestInsertBasicLength2) {
	Trie test;
	test.insert("01");
    ASSERT_TRUE(test.exists("01"));
    ASSERT_FALSE(test.exists("011"));
    ASSERT_FALSE(test.exists("0"));
    ASSERT_FALSE(test.exists("1"));
    ASSERT_FALSE(test.exists("00"));
}

TEST(TrieTest, TestInsertKindaLong) {

	Trie test;
	set<string> contains;
	test.insert("10101");
	contains.insert("10101");
	test.insert("0001");
	contains.insert("0001");

	ASSERT_TRUE(check_trie(6, contains, test));
}

TEST(TrieTest, TestInsertStress) {
	Trie test;
	set<string> contains;
	for(int i = 0; i < 10; i++) {
		string random = gen_random();
		//cout << "inserting: " << random << endl;
		test.insert(random);
		contains.insert(random);
	}

	ASSERT_TRUE(check_trie(11, contains, test));
}

TEST(TrieTest, TestInsertSUPERSTRESS_AGHHHHHHHHH) {

	Trie test;
	set<string> contains;
	for(int i = 0; i < 50; i++) {
		string random = gen_random();
		//cout << "inserting: " << random << endl;
		test.insert(random);
		contains.insert(random);
	}

	ASSERT_TRUE(check_trie(11, contains, test));
}



