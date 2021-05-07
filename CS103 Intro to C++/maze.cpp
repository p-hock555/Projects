#include <fstream>
#include <iostream>
using namespace std;

char** read_maze(char* filename, int *rows, int *cols)
{
	ifstream myfile(filename);

	if(myfile.fail())
	{
		cout << "The file could not open." << endl;
		return 1;
	}

	myfile >> rows >> cols;

	char** maze = new char*[rows];
	char c;

	for(int i = 0; i<rows; i++)
	{
		maze[i] = new char[cols];
	}

	for(int j = 0; j<cols; j++)
	{
		myfile >> c;
		maze[i][j] = c; 
	}

	return maze;
}

