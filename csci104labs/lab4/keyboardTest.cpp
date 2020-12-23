#include "gtest/gtest.h"
#include "keyboard.h"

using namespace std;

TEST(KeyboardTest, basic) 
{
	EXPECT_EQ(0, calculateTime("abcdefghijklmnopqrstuvwxyz", "a"));
}

TEST(KeyboardTest, kind_of_basic) 
{
	EXPECT_EQ(4, calculateTime("abcdefghijklmnopqrstuvwxyz", "cba"));
	EXPECT_EQ(39, calculateTime("pqrstuvwxyzabcdefghijklmno", "csci"));
	EXPECT_EQ(61, calculateTime("pqrstuvwxyzabcdefghijklmno", "camels"));
}

TEST(KeyboardTest, not_basic) 
{
	EXPECT_EQ(334, calculateTime("abcdefghijklmnopqrstuvwxyz", "pneumonoultramicroscopicsilicovolcanoconiosis"));
	EXPECT_EQ(299, calculateTime("pqrstuvwxyzabcdefghijklmno", "antidisestablishmentarianism"));
	EXPECT_EQ(121, calculateTime("abcdefghijklmnopqrstuvwxyz", "sesquipedalian"));
	EXPECT_EQ(409, calculateTime("pqrstuvwxyzabcdefghijklmno", "hippopotomonstrosesquippedaliophobia"));
}
