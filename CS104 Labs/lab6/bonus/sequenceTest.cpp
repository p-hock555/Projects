#include "gtest/gtest.h"
#include "sequence.h"

using namespace std;

TEST(SequenceTest, 2_4_6) 
{
	int input [] = { 2, 4, 6 };
	EXPECT_EQ(2, isArithmeticSequence(input, 3));
}

TEST(SequenceTest, 1_2_4_6) 
{
	int input [] = {1, 2, 4, 6};
	EXPECT_EQ(-1, isArithmeticSequence(input, 4));
}

TEST(SequenceTest, 2_4_6_9) 
{
	int input [] = {2, 4, 6, 9};
	EXPECT_EQ(-1, isArithmeticSequence(input, 4));
}

TEST(SequenceTest, 0_3_6_9) 
{
	int input [] = {0, 3, 6, 9};
	EXPECT_EQ(3, isArithmeticSequence(input, 4));
}


TEST(SequenceTest, 3_0_3_6_9_neg) 
{
	int input [] = {-3, 0, 3, 6, 9};
	EXPECT_EQ(3, isArithmeticSequence(input, 5));
}

TEST(SequenceTest, 5) 
{
	int input [] = {5};
	EXPECT_EQ(0, isArithmeticSequence(input, 1));
}

TEST(SequenceTest, empty) 
{
	int input [] = {};
	EXPECT_EQ(0, isArithmeticSequence(input, 0));
}