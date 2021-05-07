#include "gtest/gtest.h"
#include "search.h"

using namespace std;


TEST(SearchTest, empty) 
{
	int input [] = {};
	EXPECT_EQ(false, contains(input,0, 0));
}

TEST(SearchTest, oddSize_contains) 
{
	int input [] = { 2, 4, 6 };
	EXPECT_EQ(true, contains(input,3, 4));
}

TEST(SearchTest, oddSize_not_contains) 
{
	int input [] = { 2, 4, 6 };
	EXPECT_EQ(false, contains(input,3, 3));
}


TEST(SearchTest, evenSize_no_contains) 
{
	int input [] = {3, 9, 33, 34};
	EXPECT_EQ(false, contains(input,4, 1));
}

TEST(SearchTest, evenSize_contains) 
{
	int input [] = {3, 9, 33, 34};
	EXPECT_EQ(true, contains(input,4, 34));
}

TEST(SearchTest, longTest_no_contains) 
{
	int input [] = {2, 4, 6, 9, 29, 48, 50, 54, 100, 1000, 10000, 1000001};
	EXPECT_EQ(false, contains(input,12, 0));
}

TEST(SearchTest, longTest_contains) 
{
	int input [] = {2, 4, 6, 9, 29, 48, 50, 54, 100, 1000, 10000, 1000001};
	EXPECT_EQ(true, contains(input,12, 2));
}

TEST(SearchTest, long_neg) 
{
	int input [] = {-3, 0, 3, 6, 9};
	EXPECT_EQ(true, contains(input,5, -3));
}

TEST(SearchTest, long_neg_not_contains) 
{
	int input [] = {-3, 0, 3, 6, 9};
	EXPECT_EQ(false, contains(input,5, -1));
}