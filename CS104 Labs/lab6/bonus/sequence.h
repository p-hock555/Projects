#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <vector>

/*
An arithmetic sequence is a sequence of numbers such that 
there is a constant difference between consecutive numbers.

For example:
a. {2, 4, 6} is an arithmetic sequence with a constant difference of 2.

b. {2, 4, 7} is NOT an arithmetic sequence.

Given a SORTED array, determine whether or not it is an arithmetic sequence.
If it is, return the constant difference (e.g. return 2 for example a).
If it is not, return -1. If the array has a size of 0 or 1, return 0.

BONUS: Think about how you could solve this if the array wasn't sorted
(and you weren't able to sort it)
*/

int isArithmeticSequence(int arr[], int size);

#endif