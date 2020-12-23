//
// Students: write your trie implementation below.
//

#include "trie.h"

//----------------------------------------------
// DO NOT MODIFY THE CONSTRUCTOR OR DESTRUCTOR.
//----------------------------------------------

SparseTrie::SparseTrie()
{
    // DO NOT MODIFY.
    // The root node is always present and represents an
    // empty string. It should never be removed until
    // the destructor runs.
    root = new TNode('\0', false);
}

SparseTrie::~SparseTrie()
{
    // LEAVE BLANK. Don't worry about deallocation.
}

void SparseTrie::insert(std::string key)
{
  if(contains(key))
  {
    return;
  }
  if(key == "")
  {
    root->terminal = true;
  }
  TNode* r = getRoot();
  if(r->children == NULL)
  {
    getRoot()->children = new TNode(key[0], false);
    if((int)key.size() == 1)
    {
     getRoot()->children->terminal = true;
     return;
    }
  }
  r = r->children;
  int index = 0;
  while(index != (int)key.size())
  {
    //if node already exists
    if(r != NULL && key[index] == r->letter)
    {
      if(index == (int)key.size()-1)
      {
        r->terminal = true;
      }
      r = r->children;
      index++;
    }
    //if we fount an open spot
    else if(r == NULL)
    {
      if(index == (int)key.size()-1)
      {
        r = new TNode(key[index], true);
      }
      else{
        r = new TNode(key[index], false);
      }

      r = r->children;
      index++;
    }
    //next is not null
    else{
      r = r->next;
    }
  }
}

 bool SparseTrie::contains(std::string key)
 {
   int index = 0;
   TNode* r = getRoot();
   r = r->children;
   while(index != (int)key.size())
   {
     if(r == NULL)
     {
       return false;
     }
     else{
       if(key[index] != r->letter)
       {
         r = r->next;
       }
       else{
         if(index == (int)key.size()-1)
         {
           if(r->terminal){
             return true;
           }
           else{
             return false;
           }
         }
         else{
           r = r->children;
           index++;
         }
       }
     }
   }
   return false;
 }
