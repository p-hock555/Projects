#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}
/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n, char diff);
    AVLNode<Key, Value>* rotateRight(AVLNode<Key,Value>* r);
    AVLNode<Key, Value>* rotateLeft(AVLNode<Key,Value>* r);
    bool isLeftChild(AVLNode<Key,Value>* n);
    bool isRightChild(AVLNode<Key,Value>* n);
    void removeHelper(AVLNode<Key,Value>* current);
};

/*
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO
    if(BinarySearchTree<Key,Value>::empty())
    {
      this->root_ = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
      AVLNode<Key, Value>* n = (AVLNode<Key, Value>*)this->root_;
      n->setBalance(0);
      n->setRight(NULL);
      n->setLeft(NULL);
    }
    else{
      AVLNode<Key, Value>* n = (AVLNode<Key, Value>*)this->root_;
      AVLNode<Key, Value>* p = (AVLNode<Key, Value>*)this->root_;
      while(n != NULL)
      {
        //check if nodes are equal no insertion needed
        if(n->getKey() == new_item.first)
        {
          n->setValue(new_item.second);
          return;
        }
        //go down left side because less than
        else if(new_item.first < n->getKey())
        {
           p = n;
           n = n->getLeft();
        }
        else{
          p = n;
          n = n->getRight();
        }
      }
      //make sure to set the parent, right and left values
      AVLNode<Key, Value>* newn = new AVLNode<Key, Value>(new_item.first, new_item.second, p);
      newn->setBalance(0);
      if(p->getKey() < new_item.first)
      {
        p->setRight(newn);
      }
      else{
        p->setLeft(newn);
      }
      newn->setRight(NULL);
      newn->setLeft(NULL);
      char parentBalance = p->getBalance();
      //update the parent balance
      if(parentBalance == -1 || parentBalance == 1)
      {
        p->setBalance(0);
      }
      else if(parentBalance == 0)
      {
        //if the newly inserted is a left child our l balance is deeper (-1)
        if(isLeftChild(newn))
        {
          p->setBalance(-1);

        }
        else
        {
          p->setBalance(1);
        }
        //grandparent can now be unbalanced, call InsertFix on parent and child
        insertFix(p, newn);
      }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    char diff;
    AVLNode<Key, Value>* n = (AVLNode<Key, Value>*)this->root_;
    AVLNode<Key, Value>* parent;
    while(n != NULL && key != n->getKey())
    {
      if(key < n->getKey())
      {
        n = n->getLeft();
      }
      else{
        n = n->getRight();
      }
    }
    if(n == NULL)
    {
      return;
    }
    if(isLeftChild(n))
    {
      diff = 1;
    }
    else{
      diff = -1;
    }
    parent = n->getParent();
    removeHelper(n);
    removeFix(parent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeHelper(AVLNode<Key,Value>* current)
{
  //first check if leaf node
  if(current->getRight() == NULL && current->getLeft() == NULL)
  {
    //check for root node
    if(current->getParent() == NULL)
    {
      this->root_ = NULL;
    }
    else if(current->getParent()->getLeft() == current)
    {
      current->getParent()->setLeft(NULL);
    }
    else if(current->getParent()->getRight() == current)
    {
      current->getParent()->setRight(NULL);
    }
    delete current;
  }
  //the node has only one child
  else if((current->getRight() == NULL && current->getLeft() != NULL) ||
              (current->getLeft() == NULL && current->getRight() != NULL))
    {
      //promote the child then delete
      AVLNode<Key,Value>* pred;
      if(current->getRight() == NULL)
      {
        pred = current->getLeft();
        AVLTree<Key,Value>::nodeSwap(pred, current);
      }
      else if(current->getLeft() == NULL)
      {
        pred = current->getRight();
        AVLTree<Key,Value>::nodeSwap(pred, current);
      }
      //check if its a root node
      if(this->root_ == current)
      {
        this->root_ = pred;
      }
      //recurse until we can delete as a leaf node
      removeHelper(current);
    }
   //the node has two children
   else{
     AVLNode<Key,Value>* pred = (AVLNode<Key,Value>*) BinarySearchTree<Key,Value>::predecessor(current);
     AVLTree<Key,Value>::nodeSwap(pred, current);
     //recurse
     removeHelper(current);
   }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
  if(p == NULL)
  {
    return;
  }
  AVLNode<Key, Value>* g = p->getParent();
  if(g == NULL)
  {
    return;
  }
  //if p is left child
  if(isLeftChild(p))
  {
    g->updateBalance(-1);
    if(g->getBalance() == 0)
    {
      return;
    }
    else if(g->getBalance() == -1)
    {
      insertFix(g, p);
    }
    else if(g->getBalance() == -2)
    {
      //LEFT RIGHT CASE
      if(p->getRight() == n)
      {
        p = rotateLeft(p);
        g = rotateRight(g);
        if(n->getBalance() == -1)
        {
          p->setBalance(0);
          g->setBalance(1);
          n->setBalance(0);
        }
        else if(n->getBalance() == 0)
        {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        else if(n->getBalance() == 1)
        {
          p->setBalance(-1);
          g->setBalance(0);
          n->setBalance(0);
        }
      }
      //RIGHT CASE
      else{
        g = rotateRight(g);
        p->setBalance(0);
        g->setBalance(0);
      }
    }
  }
  //p is g's right child
  else{
    g->updateBalance(1);
    if(g->getBalance() == 0)
    {
      return;
    }
    else if(g->getBalance() == 1)
    {
      insertFix(g, p);
    }
    else if(g->getBalance() == 2)
    {
      //RIGHT LEFT CASE
      if(p->getLeft() == n)
      {
        p = rotateRight(p);
        g = rotateLeft(g);
        if(p->getRight() == n)
        {
          p = rotateLeft(p);
          g = rotateRight(g);
          if(n->getBalance() == -1)
          {
            p->setBalance(0);
            g->setBalance(1);
            n->setBalance(0);
          }
          else if(n->getBalance() == 0)
          {
            p->setBalance(0);
            g->setBalance(0);
            n->setBalance(0);
          }
          else if(n->getBalance() == 1)
          {
            p->setBalance(-1);
            g->setBalance(0);
            n->setBalance(0);
          }
        }
      }
      //LEFT CASE
      else{
        g = rotateLeft(g);
        p->setBalance(0);
        g->setBalance(0);
       }
      }
    }
 }

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, char diff)
{
  if(n == NULL)
  {
    return;
  }
  //parent node of n
  AVLNode<Key, Value>* p = n->getParent();
  //this ndiff will be recursed
  char ndiff = 0;
  if(p != NULL)
  {
    if(isLeftChild(n))
    {
      ndiff += 1;
    }
    else{
      ndiff -= 1;
    }
  }
  //c is the taller child
  //c = left node for -1 diff and right for +1
  char gbalance;
  AVLNode<Key, Value>* c;
  AVLNode<Key, Value>* g;
  if(diff == -1)
  {
    //unbalanced tree
    if(n->getBalance() + diff == -2)
    {
      c = n->getLeft();
      //currents left child unbalanced left
      if(c->getBalance() == -1)
      {
        //zig zig case
        n = rotateRight(n);
        c->setBalance(0);
        n->setBalance(0);
        removeFix(p, ndiff);
      }
      //currents left child balanced right
      else if(c->getBalance() == 0)
      {
        //zig zig case
        n = rotateRight(n);
        n->setBalance(-1);
        c->setBalance(1);
        //done, balanced now
      }
       //currents left child unbalanced right
      else if(c->getBalance() == 1)
      {
        g = c->getRight();
        gbalance = g->getBalance();
        c = rotateLeft(c);
        n = rotateRight(n);
        if(gbalance == 1)
        {
          n->setBalance(0);
          c->setBalance(-1);
          g->setBalance(0);
        }
        else if(gbalance == 0)
        {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if(gbalance == -1)
        {
          n->setBalance(1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    //done!!
    else if(n->getBalance() + diff == -1)
    {
      n->setBalance(-1);
    }
    //still need to recurse and check higher up
    else if(n->getBalance() + diff == 0)
    {
      n->setBalance(0);
      removeFix(n, ndiff);
    }
  }
  //mirror right
  else if(diff == 1)
  {
    //unbalanced tree
    if(n->getBalance() + diff == 2)
    {
      c = n->getRight();
      //currents left child unbalanced left
      if(c->getBalance() == 1)
      {
        //zig zig case
        n = rotateLeft(n);
        c->setBalance(0);
        n->setBalance(0);
        removeFix(p, ndiff);
      }
      //currents left child balanced right
      else if(c->getBalance() == 0)
      {
        //zig zig case
        n = rotateLeft(n);
        n->setBalance(1);
        c->setBalance(-1);
        //done, balanced now
      }
       //currents left child unbalanced right
      else if(c->getBalance() == -1)
      {
        g = c->getLeft();
        gbalance = g->getBalance();
        c = rotateRight(c);
        n = rotateLeft(n);
        if(gbalance == 1)
        {
          n->setBalance(0);
          c->setBalance(1);
          g->setBalance(0);
        }
        else if(gbalance == 0)
        {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if(gbalance == -1)
        {
          n->setBalance(-1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    //done!!
    else if(n->getBalance() + diff == 1)
    {
      n->setBalance(1);
    }
    //still need to recurse and check higher up
    else if(n->getBalance() + diff == 0)
    {
      n->setBalance(0);
      removeFix(n, ndiff);
    }
  }
}


template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* r)
{
  AVLNode<Key, Value>* p = r->getParent();
  AVLNode<Key, Value>* x = r->getLeft();
  AVLNode<Key, Value>* q = x->getRight();
  if(p == NULL)
  {
    this->root_ = x;
    x->setParent(NULL);
  }
  else if(isLeftChild(r))
  {
    p->setLeft(x);
    x->setParent(p);
  }
  else{
    p->setRight(x);
    x->setParent(p);
  }
  r->setParent(x);
  x->setRight(r);

  if(q != NULL)
  {
    q->setParent(r);
  }
  r->setLeft(q);
  return x;
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* r)
{
  AVLNode<Key, Value>* p = r->getParent();
  AVLNode<Key, Value>* x = r->getRight();
  AVLNode<Key, Value>* q = x->getLeft();
  if(p == NULL)
  {
    this->root_ = x;
    x->setParent(NULL);
  }
  else if(isLeftChild(r))
  {
    p->setRight(x);
    x->setParent(p);
  }
  else{
    p->setLeft(x);
    x->setParent(p);
  }
  r->setParent(x);
  x->setLeft(r);

  if(q != NULL)
  {
    q->setParent(r);
  }
  r->setRight(q);
  return x;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftChild(AVLNode<Key,Value>* n)
{
  AVLNode<Key,Value>* avlP = n->getParent();
  if(avlP->getLeft() == n)
  {
    return true;
  }
  return false;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isRightChild(AVLNode<Key,Value>* n)
{
  AVLNode<Key,Value>* avlP = n->getParent();
  if(avlP->getRight() == n)
  {
    return true;
  }
  return false;
}


#endif
