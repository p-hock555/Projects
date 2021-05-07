/*

Rearrange a singly-linked list so that all the odd-numbered nodes come before all the even-numbered nodes.
When we say odd and even, we're referring to the index of the node, not the value.

Do this in place (i.e. without creating a new list and just copying the values over).
This should run in linear time.

Return the head of the new list.

Example 1:
Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL

Example 2:
Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL

The relative ordering among the even/odd groups should remain the same, as shown in the examples.
The first node is odd, the second node is even and so on ...

*/

struct Node {
	int val;
	Node* next;
	Node(int x) : val(x), next(nullptr) {}
	Node(int x, Node* nextNode) : val(x), next(nextNode) {}
};


Node* oddEvenList(Node* head);