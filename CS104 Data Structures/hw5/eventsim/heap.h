#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>


template <typename T, typename PComparator = std::greater<T> >
class Heap
{
public:
    /// Constructs an m-ary heap for any m >= 2
    Heap(int m, PComparator c = PComparator());

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

private:
    /// Add whatever helper functions and data members you need below
    int m; //m-ary heap number
    PComparator comp; //keeping track of the input comparator from constructor
    std::vector<T> elements; //keep track of all of the elements of the heap
    void trickleUp(int idx);

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
  this->m = m;
  comp = c;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{ }

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  elements.push_back(item);
  int child = elements.size()-1;
  int parent = (child-1)/m;
  while (comp(elements[child], elements[parent]))
  {
    T temp = elements[child];
    elements[child] = elements[parent];
    elements[parent] = temp;

    child = parent;
    parent = (child-1) / m;
  }
}

// We will start top() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()) {
    throw std::logic_error("can't top an empty heap");
  }
   // If we get here we know the heap has at least 1 item
   // Add code to return the top element
   return elements[0];

}

// We will start pop() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("empty");
  }
  elements[0] = elements[elements.size()-1];
  elements.pop_back();

  int parent = 0;
  int swapIndex = 0;
  //making sure all of the elements in the heap are sorted correctly
  while(swapIndex != -1)
  {
    swapIndex = -1;
    for(int i = 1; i<m; i++)
    {
      if(parent * m + i <= (int)elements.size()-1)
      {
        if(comp(elements[parent * m +i], elements[parent]))
        {
          if(swapIndex == -1)
          {
            swapIndex = parent * m + i;
          }
          else if(comp(elements[parent * m + i], elements[swapIndex]))
          {
            if(elements[parent * m +i] != elements[swapIndex])
            {
              swapIndex = parent * m + i;
            }
          }
        }
      }
    }
    if(swapIndex != -1)
    {
      T temp = elements[swapIndex];
      elements[swapIndex] = elements[parent];
      elements[parent] = temp;

      parent = swapIndex;
    }
  }

}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return elements.empty();
}


#endif
