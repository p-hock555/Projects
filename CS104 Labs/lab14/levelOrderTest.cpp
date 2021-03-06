#include "gtest/gtest.h"
#include "levelOrder.h"

using namespace std;

TEST(LevelOrder, basic) 
{
	vector<vector<int>> a;
	vector<vector<int>> b = levelOrder(nullptr);
	EXPECT_EQ(a, b);
}

TEST(LevelOrder, Simple) {
    //leaf nodes
    //1 3 5 7
    Node n1(1);
    Node n3(3);
    Node n5(5);
    Node n7(7);

    //2 6
    Node n2(&n1, &n3, 2);
    Node n6(&n5, &n7, 6);

    //4
    Node n4(&n2, &n6, 4);

    vector<vector<int>> a = { { 4 }, { 2, 6 }, { 1, 3, 5, 7 } };
	vector<vector<int>> b = levelOrder(&n4);
	EXPECT_EQ(a, b);
}

TEST(LevelOrder, AnotherSimple) {

    Node n2(2);
    Node n7(7);
    Node n14(14);
    Node n20(20);

    Node n5(nullptr, &n7, 5);
    Node n12(nullptr, &n14, 12);
    Node n16(nullptr, &n20, 16);

    Node n4(&n2, &n5, 4);
    Node n15(&n12, &n16, 15);

    Node n10(&n4, &n15, 10);

    vector<vector<int>> a = { { 10 }, { 4, 15 }, { 2, 5, 12, 16 }, { 7, 14, 20 } };
	vector<vector<int>> b = levelOrder(&n10);
	EXPECT_EQ(a, b);
}

TEST(LevelOrder, SimpleAgain) {
    //leaf nodes
    //2 7 12 15
    Node n2(2);
    Node n7(7);
    Node n12(12);
    Node n15(15);
    Node n20(20);

    //4 14
    Node n4(&n2, nullptr, 4);
    Node n14(&n12, &n15, 14);

    //10
    Node n10(&n7, &n14, 10);

    //16
    Node n16(&n10, &n20, 16);

    //5
    Node n5(&n4, &n16, 5);

    vector<vector<int>> a =  { { 5 }, { 4, 16 }, { 2, 10, 20 }, { 7, 14 }, { 12, 15 } };
	vector<vector<int>> b = levelOrder(&n5);
	EXPECT_EQ(a, b);
}

TEST(LevelOrder, Wacky) {

    Node n16(16);
    Node n45(45);
    Node n43(nullptr, &n45, 43);
    Node n34(nullptr, &n43, 34);
    Node n49(&n34, nullptr, 49);
    Node n23(&n16, &n49, 23);

    Node n12(nullptr, &n23, 12);

 	vector<vector<int>> a =  { { 12 }, { 23 }, { 16, 49 }, { 34 }, { 43 }, { 45 } };
	vector<vector<int>> b = levelOrder(&n12);
	EXPECT_EQ(a, b);
}
