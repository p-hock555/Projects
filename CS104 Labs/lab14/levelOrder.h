#include <vector>

/*

Given a binary tree, return the level order traversal of its nodes' values. (i.e. from left to right, level by level).


If you're given this binary tree as input:

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

*/

struct Node {
	int val;
	Node* left;
	Node* right;

	Node(int x) : val(x), left(nullptr), right(nullptr) {}
	Node(Node* leftNode, Node* rightNode, int x) : val(x), left(leftNode), right(rightNode) {}
};

std::vector<std::vector<int>> levelOrder(Node* root);