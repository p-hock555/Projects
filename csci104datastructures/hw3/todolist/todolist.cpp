#include <stdexcept>
#include <iostream>
#include "todolist.h"
using namespace std;


DailyTodoList::DailyTodoList()
{
    data_ = new Item * [5];
    cap_ = 5;
    priorityHead_ = NULL;
    // [TO BE COMPLETED]
    //===========================
    // Add any addition code here
    numPriorityItems_ = 0;
}
DailyTodoList::~DailyTodoList()
{
  delete [] data_;
}

void DailyTodoList::push_back(size_t dayIndex, const std::string& val, bool highPriority)
{
    if (dayIndex < cap_)
    {
        this->insert(dayIndex, this->numItemsOnDay(dayIndex), val, highPriority);
    }
    else
    {
        this->insert(dayIndex, 0, val, highPriority);
    }

}

void DailyTodoList::insert(size_t dayIndex, size_t loc, const std::string& val, bool highPriority)
{
  try{
    //if the day index is invalid we resize the data_
    if(dayIndex >= cap_)
    {
      Item ** temp = new Item* [dayIndex*2];
      for(size_t i = 0; i<cap_; i++)
      {
        temp[i] = data_[i];
      }
      //temp points to the same elements. did not need to make more
      delete [] data_;

      data_ = temp;
      cap_ = dayIndex*2;
      //once we have resized and copied data into the new list
      //now we can insert a new item
    }
    Item * newitem = data_[dayIndex];
    Item * prev;
    size_t currloc = 0;
    Item * pri = priorityHead_;
    //check valid index
    if(loc > numItemsOnDay(dayIndex))
     {
       throw std::out_of_range("out of range");
     }
     //if location is 0
     if(currloc == loc)
     {
       if(empty(dayIndex))
       {
         data_[dayIndex] = new Item(val, NULL, NULL);
         newitem = data_[dayIndex];
       }
       else{
         Item * newi = new Item(val, data_[dayIndex], NULL);
         data_[dayIndex] = newi;
       }

     }
  //if there are multiple elements in a list
    else{
      //iterate until we get the location we want
      while(currloc != loc)
      {
        prev = newitem;
        newitem = newitem->nextItem;
        currloc++;
      }
      //insert the values
      prev->nextItem = new Item(val, newitem, NULL);
      newitem = prev->nextItem;
     }
     //check if highPriority item
    if(highPriority)
    {
      //if there are no priority items in the list yet
      if(priorityHead_ == NULL)
      {
        priorityHead_ = newitem;
      }
      //there are already priority items in the list
      else{
        while(pri->nextPriorityItem != NULL)
        {
          pri = pri->nextPriorityItem;
        }
        pri->nextPriorityItem = newitem;
      }
      numPriorityItems_++;
    }
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << endl;
  }
}

void DailyTodoList::remove(size_t dayIndex, size_t loc)
{
  try{
    //check if the day is valid
    if(dayIndex >= cap_)
    {
      throw std::out_of_range("out of range");
    }
    //check if the loc is valid
    if(numItemsOnDay(dayIndex) <= loc)
    {
      throw std::out_of_range("out of range");
    }

    Item * prev;
    Item * temp = data_[dayIndex];
    size_t currloc = 0;
    Item * pri = priorityHead_;
    //list is not empty so find the loc to remove
      //if there is only one item in the list
    if(loc == currloc)
    {
      //check if its a highPriority item
      while(pri != NULL && pri != temp)
      {
        prev = pri;
        pri = pri->nextPriorityItem;
      }
      if(pri == temp)
      {
        //priority item prev points to the next item in the priority list
        prev->nextPriorityItem = pri->nextPriorityItem;
        numPriorityItems_--;
      }
      temp->nextItem = NULL;
      temp->nextPriorityItem = NULL;
      delete temp;
    }
    else{
      //if there are multiple locations
       while(currloc != loc)
       {
         prev = temp;
         temp = temp->nextItem;
         currloc++;
      }
      prev->nextItem = temp->nextItem;
      //check if its a highPriority item
      while(pri != NULL && pri != temp)
      {
        prev = pri;
        pri = pri->nextPriorityItem;
      }
      if(pri == temp)
      {
        //priority item prev points to the next item in the priority list
        prev->nextPriorityItem = pri->nextPriorityItem;
        numPriorityItems_--;
      }
      temp->nextItem = NULL;
      temp->nextPriorityItem = NULL;
      delete temp;
    }
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << endl;
  }
}

size_t DailyTodoList::numDays() const
{
  return cap_;
}

size_t DailyTodoList::numItemsOnDay(size_t dayIndex) const
{
  try{
    if(dayIndex >= cap_)
    {
      throw std::out_of_range("out of range");
    }
    //traverse the list and count
    //stop when next is NULL
    Item * temp = data_[dayIndex];
    size_t count = 0;
    //base case: the day has no Items
    if(empty(dayIndex))
    {
      return count;
    }
    count++;
    while(temp->nextItem != NULL)
    {
      count++;
      temp = temp->nextItem;
    }
    return count;
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << endl;
  }
}

bool DailyTodoList::empty(size_t dayIndex) const
{
  try{
    if(dayIndex >= cap_)
    {
      throw std::out_of_range("out of range");
    }
    if(data_[dayIndex] == NULL)
    {
      return true;
    }
    else{
      return false;
    }
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << endl;
  }
}
const std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc) const
{
  try{
  //check for a valid day
    if(dayIndex >= cap_)
    {
      throw std::out_of_range("out of range");
    }
    //iterate until we reach location
    Item * temp = data_[dayIndex];
    size_t i = 0;
    while(i != loc)
    {
      temp = temp->nextItem;
      i++;
    }
    return temp->val;
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << endl;
  }
}
std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc)
{
  try{
    //check for a valid day
    if(dayIndex >= cap_)
    {
      throw std::out_of_range("out of range");
    }
    //iterate until we reach location
    Item * temp = data_[dayIndex];
    size_t i = 0;
    while(i != loc)
    {
      temp = temp->nextItem;
      i++;
    }
    return temp->val;
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << endl;
  }
}

size_t DailyTodoList::numPriorityItems() const
{
  return numPriorityItems_;
}

const std::string& DailyTodoList::getPriorityVal(size_t priorityLoc) const
{
  try{
    Item * temp = priorityHead_;
    size_t i = 0;
    while(i != priorityLoc && temp != NULL)
    {
      temp = temp->nextPriorityItem;
      i++;
    }
    if(temp == NULL)
    {
      throw std::out_of_range("out of range");
    }
    return temp->val;
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << endl;
  }
}
