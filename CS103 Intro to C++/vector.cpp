#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	vector<string> string;
	vector<int> g1; 
    char c;

    for (int i = 1; i <= 5; i++){
        g1.push_back(i); 
    }
    
    for(int i = 0;i<g1.size();i++)
    {
        c = (char)g1[i] + 48;
        string.push_back(i);
    }

    for(int i = 0; i<string.size(); i++)
    {
    	cout << string[i];
    }

    cout << endl;
}