 #include "expr-reader.h"
#include "expr-ops.h"
#include <iostream>
#include <sstream>

using namespace std;
/*-----------------------------------------------------------------------------
 *  Implement the following functions below.
 *  Processing of each (sub)expression must be recursive (i.e. loops
 *    may only be used to iterate through the child vector of the given node).
 *  You may define recursive helper functions to adapt the function signatures.
 *    However, only exprPrinter likely needs a helper function.
 ----------------------------------------------------------------------------*/

void exprPrinter(std::ostream& ostr, Node* n)
{
  // Should never be called on NULL expression
  if(n == NULL){
    throw std::logic_error("Can't solve a NULL expression");
  }

  exprPrinterHelper(ostr, n);
}

void exprPrinterHelper(std::ostream& ostr, Node* n)
{
  //we have reached a leaf node
  if(n->children.empty())
  {
    stringstream ss(n->val);
    int num;
    ss>>num;
    if(ss.fail())
    {
      throw std::logic_error("need to have an integer as a leaf");
    }
    ostr << num << " ";
  }

  for(int i = 0; i<(int)n->children.size(); i++) {
    if((n->val == "+" || n->val == "-" || n->val == "*" || n->val == "/"))
    {
      if(i == 0)
      {
        ostr << "( ";
      }
      exprPrinterHelper(ostr, n->children[i]);
      if(i != (int)n->children.size()-1)
      {
        ostr << n->val << " ";
      }
      if(i == (int)n->children.size()-1)
      {
        ostr << ") ";
      }
    }
    else{
      throw std::logic_error("invalid formatting");
    }
  }
}

int exprSolver(Node* n)
{

    /* Should never be called on NULL expression -- Do Not Modify */
    if(n == NULL ) {
        throw std::logic_error("Can't solve a NULL expression");
    }
    int retval;
    if(n->children.empty())
    {
      int num;
      stringstream ss(n->val);
      ss>>num;
      if(ss.fail())
      {
        throw std::logic_error("need to have an integer as a leaf");
      }
      retval = num;
      return retval;
    }

    if(n->val == "+"){
      int sum = 0;
      for(int i = 0; i < (int)n->children.size(); i++){
        sum += exprSolver(n->children[i]);
      }
      return sum;
    }
    else if(n->val == "-"){
      int sub = exprSolver(n->children[0]);
      for(int i = 1; i < (int)n->children.size(); i++){
        sub -= exprSolver(n->children[i]);
      }
      return sub;
    }
    else if(n->val == "*"){
      int mult = exprSolver(n->children[0]);
      for(int i = 1; i<(int)n->children.size(); i++){
        mult *= exprSolver(n->children[i]);
      }
      return mult;
    }
    else if(n->val == "/"){
      int div = exprSolver(n->children[0]);
      for(int i = 1; i<(int)n->children.size(); i++){
        div /= exprSolver(n->children[i]);
      }
      return div;
    }
    else{
      throw std::logic_error("invalid operation");
    }

}

bool exprIsValid(Node* n)
{
  bool value;
  //leaf node check
  if(n->children.empty())
  {
    int num;
    stringstream ss(n->val);
    ss >> num;
    //check if the leaf node is an int
    if(ss.fail())
    {
      value = false;
    }
  }
  else{
    for(int i = 0; i<(int)n->children.size(); i++)
    {
      value = exprIsValid(n->children[i]);
    }
  }
  return value;

}
