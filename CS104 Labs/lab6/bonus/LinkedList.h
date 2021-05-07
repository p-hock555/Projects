#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node {
    Node* next;
    int value;
};

class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        void add(int value);
        
        Node* head;
};

// return sum of all items in linked list
// return 0 if list is empty
int sum(Node* head);

#endif