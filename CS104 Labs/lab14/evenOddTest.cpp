#include "gtest/gtest.h"
#include "evenOdd.h"
#include <iostream>

using namespace std;

TEST(EvenOdd, basic) 
{
	Node* n1 = new Node(1);
	Node* temp = oddEvenList(n1);

	ASSERT_EQ(temp->val, 1);
}


TEST(EvenOdd, segfault) 
{
	Node* n1 = nullptr;
	oddEvenList(n1);
}

TEST(EvenOdd, shorttest) 
{
	Node* n1 = new Node(1, (new Node(2, new Node (3))));
	Node* temp = oddEvenList(n1);

	vector<int> result = {1, 3, 2};

	for(unsigned int i = 0; i < result.size(); i++) {
		ASSERT_EQ(temp->val, result[i]);
		temp = temp->next;
	}
}

TEST(EvenOdd, normal) 
{
	Node* n1 = new Node(1, (new Node(2, new Node (3, new Node (4, new Node (5))))));
	Node* temp = oddEvenList(n1);

	vector<int> result = {1, 3, 5, 2, 4};

	for(unsigned int i = 0; i < result.size(); i++) {
		ASSERT_EQ(temp->val, result[i]);
		temp = temp->next;
	}
}

TEST(EvenOdd, long) 
{
	Node* n2 = new Node(6, (new Node(7, new Node (8, new Node (9, new Node (10))))));
	Node* n1 = new Node(1, (new Node(2, new Node (3, new Node (4, new Node (5, n2))))));
	Node* temp = oddEvenList(n1);

	vector<int> result = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

	for(unsigned int i = 0; i < result.size(); i++) {
		ASSERT_EQ(temp->val, result[i]);
		temp = temp->next;
	}
}
