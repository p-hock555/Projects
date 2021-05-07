#include <iostream>
using namespace std;  // fine for this exam

// Item definition - do NOT change
template <typename T>
struct Item {
    T val;
    Item<T>* next;
    // Constructor for convenience of testing
    Item<T>(T v, Item<T>* n): val(v), next(n) {}
};


// Sample comparator for reference and testing
struct isEven {
    bool operator()(int v) {
        return v%2 == 0;
    }
};

// You may prototype helper functions here



// Removes items from a linked list and and places them in the returned list
//
// Compare object should take in a single T value and return true if
//  that item should be removed (e.g. if 'curr' is an Item<T>* then calling
//  comp(curr->val) should return true if the item should be removed, false otherwise).
//
// head should be updated to point at the head of the remaining items in the original list
//
// The return value should be a head pointer to the list of items removed. Order should
//  be preserved in both lists.  For example, if item1 came before item2 in the original list,
//  it should come before item2 in the returned list.
//
template <class T, class Compare>
Item<T>* removeCond(Item<T>* &head, Compare comp)
{
  if(head == NULL){
    return head;
  }
  Item<T>* removedHead;
  Item<T>* curr;
  Item<T>* prev;
  //if the first value needs to be removed
  if(comp(head->val)){
    removedHead = head;
    Item<T>* temp = head;
    //get the head of the correct list
    while(comp(temp->val)){
      temp = temp->next;
    }
    if(temp == NULL)
    {
      //all elements need to be removed
      head = NULL;
      return removedHead;
    }
    else{
      head = temp;
      prev = head;
    }
  }
  //the first value is okay, need to find the first element that needs to be removed iterate
  else{
    removedHead = head;
    while(removedHead != NULL){
      if(comp(removedHead->val)){
        break;
      }
      prev = removedHead;
      removedHead = removedHead->next;
    }
    //nothing needs to be removed
    if(removedHead == NULL)
    {
      return removedHead;
    }
  }
  Item<T>* p = removedHead;
  curr = removedHead->next;
  while(curr != NULL)
  {
    //if it is even remove
    if(comp(curr->val))
    {
      p->next = curr;
      p = p->next;
    }
    //odd and keep
    else{
      prev->next = curr;
      prev = prev->next;
    }
    curr = curr->next;
  }
  return removedHead;
}
