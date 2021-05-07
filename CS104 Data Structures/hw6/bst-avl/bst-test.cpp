
#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
  BinarySearchTree<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.remove(1);


  // Binary Search Tree tests
  // BinarySearchTree<char,int> bt;
  //
  // cout << "TESTING INSERTION" << endl;
  // bt.insert(std::make_pair('b',2));
  // bt.insert(std::make_pair('a',1));
  // bt.insert(std::make_pair('x',3));
  // bt.insert(std::make_pair('c',3));
  // bt.insert(std::make_pair('d',3));
  // cout << "Binary Search Tree contents:" << endl;
  // for(AVLTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
  //     cout << it->first << " " << it->second << endl;
  // }
  // bt.clear();
  //
  // bt.insert(std::make_pair('z',2));
  // bt.insert(std::make_pair('y',1));
  // bt.insert(std::make_pair('x',3));
  // bt.insert(std::make_pair('n',3));
  // bt.insert(std::make_pair('a',3));
  // cout << "Binary Search Tree contents:" << endl;
  // for(AVLTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
  //     cout << it->first << " " << it->second << endl;
  // }
  //
  // bt.remove('z');
  // cout << "Binary Search Tree contents:" << endl;
  // for(AVLTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
  //     cout << it->first << " " << it->second << endl;
  // }
  // bt.clear();
  //
  // cout << "\nTESTING REMOVAL" << endl;
  // bt.insert(std::make_pair('m',2));
  // bt.insert(std::make_pair('k',1));
  // bt.insert(std::make_pair('i',3));
  // bt.insert(std::make_pair('z',3));
  // bt.insert(std::make_pair('w',3));
  // bt.insert(std::make_pair('q',2));
  // bt.insert(std::make_pair('l',1));
  // bt.insert(std::make_pair('o',3));
  // bt.insert(std::make_pair('p',3));
  // bt.insert(std::make_pair('w',4));
  // for(AVLTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
  //     cout << it->first << " " << it->second << endl;
  // }
  //
  // if(bt.find('m') != bt.end()) {
  //     cout << "Found m " << endl;
  // }
  // else {
  //     cout << "Did not find m " << endl;
  // }
  // cout << "Erasing w" << endl;
  // bt.remove('m');
  // for(AVLTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
  //     cout << it->first << " " << it->second << endl;
  // }
  // bt.clear();

  // // AVL Tree Tests
  // AVLTree<int,int> at;
  // at.insert(std::make_pair(10,1));
  // at.insert(std::make_pair(20,2));
  // at.insert(std::make_pair(30,2));
  // at.insert(std::make_pair(25,2));
  // at.insert(std::make_pair(23,2));
  // at.insert(std::make_pair(5,2));
  // at.remove(25);
  // at.remove(20);
  //
  // cout << "AVLTree contents :" << endl;
  // for(AVLTree<int,int>::iterator it = at.begin(); it != at.end(); ++it) {
  //     cout << it->first << " " << it->second << endl;
  // }
  // at.clear();

  return 0;
}
