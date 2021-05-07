#include "gtest/gtest.h"
#include "LinkedList.h"

TEST(sumTest, TestEmptyList) 
{
	LinkedList ll;
	int attempt = sum(ll.head);
	int solution = 0;
	EXPECT_EQ(attempt, solution);
}

TEST(sumTest, TestNotEmpty) {
	LinkedList ll1;
	ll1.add(1);
	ll1.add(2);
	ll1.add(3);
	ll1.add(4);
	ll1.add(5);
	int attempt = sum(ll1.head);
	int solution = 15;
	EXPECT_EQ(attempt, solution);

	LinkedList ll2;
	ll2.add(0);
	ll2.add(0);
	ll2.add(0);
	ll2.add(0);
	ll2.add(0);
	ll2.add(0);
	attempt = sum(ll2.head);
	solution = 0;
	EXPECT_EQ(attempt, solution);

	LinkedList ll3;
	ll3.add(-1);
	ll3.add(-3);
	ll3.add(-5);
	ll3.add(-7);
	ll3.add(-9);
	ll3.add(0);
	attempt = sum(ll3.head);
	solution = -25;
	EXPECT_EQ(attempt, solution);
}
