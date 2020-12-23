#ifndef SEARCH_H
#define SEARCH_H

/*

Searching for an element in a list is a critical aspect of software development.
Performing a search quickly is essential for a good user experience. One such
way to perform the search is by going through the array from start to finish. But, 
if your array is sorted, we can do this faster, with a method called Binary Search.

Here is a simulation for Binary Search vs Linear Search, to help you visualize: 
https://www.mathwarehouse.com/programming/gifs/binary-vs-linear-search.php

Binary Search can only be conducted on a sorted array, where you start in 
the middle of the array and compare the element with the one you are looking for. 

If they are equal, then you are done -- you found the element! If they are not equal, compare them.
If the middle element is greater than the element you're looking for, check the left half of the list.
If the middle element is less, check the right half of the list.

Keep doing this recursively until you find the element.
Because this is recursion, you need to think carefully about your base case!

Given a SORTED array, determine whether or not it contains num.
If it is, return true, if not return false.


arr 	- Array To Search
n 		- Number of Elements In Array
num 	- Number to look for
*/

bool contains (int arr[], int n, int num);

// think about what parameters a helper function should take in, and define one here!

#endif