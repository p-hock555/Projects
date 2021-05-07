#include "LinkedList.h"

LinkedList::LinkedList() {
    this->head = nullptr;
}

LinkedList::~LinkedList() {
    while(head != nullptr) {
        Node* temp = head->next;
        delete head;
        head = temp;
    }
}

void LinkedList::add(int value) {
    Node* node = new Node();
    node->value = value;
    node->next = this->head;
    this->head = node;
}

// return sum of all items in linked list
// return 0 if list is empty
int sum(Node* head) {
    //TODO
}
