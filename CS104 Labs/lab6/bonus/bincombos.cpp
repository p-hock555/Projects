#include "bincombos.h"

using namespace std;

void generateHelper(vector<string>& combos, string prefix, int length) {
	//base case: prefix is full length, push it to vector

	//recursive case: add 0 or 1 to the prefix and continue
	
}


vector<string> BinaryCombos::generate(int length) {
	//completed function, write the helper function

	vector<string> combos;

	generateHelper(combos, "", length);

	return combos;
}
