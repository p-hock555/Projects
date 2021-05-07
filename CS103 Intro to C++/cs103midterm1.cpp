//----------------------------------------------------------
// Program to read in a sequence of integers from a file and
// then print a column chart using '*' for each unit.
//
// The filename will be specified as the first command line:
//
// ./colchart chart0.in
//
// The first integer in the input file specifies how many
// actual data points (integer) will follow and should be
// charted.
//
// Example: An input file containing:
// |- chart0.in ------------------------------|
// | 4                                        |
// | 5 2 1 3                                  |
// |------------------------------------------|
//
// Should result in the output (to cout):
// |------------------------------------------|
// |*                                         |
// |*                                         |
// |*     *                                   |
// |* *   *                                   |
// |* * * *                                   |
// |------------------------------------------|
//
// Note:  Leave a space after each column of output
// (i.e. between each column)
//
// Use appropriate allocation techniques and ensure no
// Valgrind errors exist.
//
// When attempting to read the input file you need only
// check for these errors:
//  1. No filename was provided on the command line
//  2. You are unable to open the filename specified
//     (e.g. it does not exist)
//  3. You are unable to read the first integer
//     (which specifies how many more integers will
//      follow) from the file.
//
//  If any of these errors occur, print "Error" on the first
//  line of output followed by 'endl' and quit the program
//  by returning 1 (not 0).
//
//  For reference, our solution took under 50 lines of code.
//   You may add #include's as necessary but may not use
//   vectors or other STL libraries.
//----------------------------------------------------------

#include <iostream>
#include <fstream>
using namespace std;

int find_max(int array[], int size);


int main(int argc, char *argv[])
{
	ifstream myfile(argv[1]);
	int counter;
	int max;

	if(myfile.fail())
	{
		cout << "File failed. " << endl;
		return 1;
	}

	myfile >> counter;

	if(myfile.fail())
	{
		cout << "Not an integer" << endl;
		return 1;
	}

    //dynamically allocate an integer array of size counter
	int *array = new int[counter];
	for(int i = 0; i<counter; i++)
	{
		myfile >> array[i];
	}
    
    max = array[0];
	for(int i = 1; i<counter; i++)
	{
		if(max<array[i])
		{
			max = array[i];
		}
	}
   
    for(int i = 0; i<max; i++)
    {
        for(int j = 0; j<counter; j++)
        {
            if(i+array[j] >= max)
            {
                cout << "* ";
            }
            else{
                cout << ' ';
            }
        }
        cout << endl;
    }
    
    delete[] array;
    return 0;


}