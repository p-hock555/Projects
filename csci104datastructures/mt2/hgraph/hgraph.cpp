#include <iostream>
#include <deque>
#include <limits>
#include "hgraph.h"
// You may add other necessary #includes other than <algorithm>


using namespace std;


HollywoodGraph::HollywoodGraph(int n, vector<string> names)
{
	for(int j = 0; j<n; j++)
	{
		vector<bool> v;
		for(int i = 0; i<n; i++)
		{
			v.push_back(0);
		}
		aMatrix.push_back(v);
	}

	for(int i = 0; i<n; i++)
	{
		nameToIdx.insert(std::make_pair(names[i], i));
	}
}

HollywoodGraph::~HollywoodGraph()
{

}

bool HollywoodGraph::addConnection(string person1, string person2)
{
	std::map<std::string, int>::iterator i = nameToIdx.find(person1);
	std::map<std::string, int>::iterator j = nameToIdx.find(person2);

	if(aMatrix[i->second][j->second] == false && aMatrix[j->second][i->second] == false)
	{
		aMatrix[i->second][j->second] = true;
		aMatrix[j->second][i->second] = true;
		return true;
	}
	return false;

}

int HollywoodGraph::countConnections(string person1)
{
	std::map<std::string, int>::iterator i = nameToIdx.find(person1);
	int count = 0;
	for(int j = 0; j<(int)aMatrix.size(); j++)
	{
		if(aMatrix[i->second][j] == true)
		{
			count++;
		}
	}
	return count;
}

bool HollywoodGraph::degreesOfSeparation(string person1, string person2, int k, int& calls)
{
	std::map<std::string, int>::iterator i = nameToIdx.find(person1);
	std::map<std::string, int>::iterator j = nameToIdx.find(person2);

	bool* visited = new bool[(int)aMatrix.size()];
	for(int x = 0; x<(int)aMatrix.size(); x++)
	{
		visited[x] = false;
	}

	deque<int> d;
	d.push_back(i->second);
	visited[i->second] = true;
	int index;

	while(!d.empty()){
		index = d.front();
		d.pop_front();

		for(int c = 0; c<(int)aMatrix.size();c++)
		{
			if(aMatrix[index][c] == true)
			{
				if(c == j->second && calls <= k)
				{
					return true;
				}
				else if(c == j->second && calls >= k)
				{
					return false;
				}
				if(!visited[c])
				{
					visited[c] = true;
					d.push_back(c);
					calls++;
				}
			}
		}
	}
	return false;
}
