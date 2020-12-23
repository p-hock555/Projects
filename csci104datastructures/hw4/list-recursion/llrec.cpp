#include "llrec.h"
#include <iostream>
using namespace std;
//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
	//base case
	if(head == NULL)
	{
		return;
	}

	//defined recursively as the first node in the list and the rest
		//of the list in every iteration
	Node* first = head;
	Node* rest = head->next;

	//checking for smaller values
	if(first->val <= pivot)
	{
		smaller = first;
		smaller->next = NULL;
		llpivot(rest, smaller->next, larger, pivot);
	}
	//checking for larger values
	else{
		larger = first;
		larger->next = NULL;
		llpivot(rest, smaller, larger->next, pivot);
	}

}
