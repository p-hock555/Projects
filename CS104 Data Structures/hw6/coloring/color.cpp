#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

void printSolution(std::map<char,int>& answer, std::ostream& ostr);
void readFile(std::istream& is, int& countries, int& row, int& col, vector<vector<char>>& grid,
   map<char,std::set<char>>& matrix, vector<std::vector<int>>& adjm, map<char,int>& charToIndex);
void solve(vector<std::vector<int>>& adjm, int index, const int& countries, std::vector<int>& colors);
bool isValid(vector<std::vector<int>>& adjm, std::vector<int>& colors, int index, int c);

int main(int argc, char* argv[])
{
    if(argc < 3) {
        cout << "Please supply a map input file and output filename" << endl;
        return 1;
    }
    // COMPLETE main()
    std::map<char,int> answer; //this has the output colors
    int row, col, countries;
    vector<vector<char>> grid; //stores the input grid
    map<char,std::set<char>> matrix;
    vector<std::vector<int>> adjm;
    map<char,int> charToIndex;
    ifstream inputFile;
    inputFile.open(argv[1]);
    readFile(inputFile, countries, row, col, grid, matrix, adjm, charToIndex); //reads the file, gets the grid from input file
    std::vector<int> colors;
    for(int x = 0; x<countries; x++)
    {
      colors.push_back(0);
    }
    solve(adjm, 0, countries, colors);
    int i = 0;
    for(map<char,int>::iterator it = charToIndex.begin(); it != charToIndex.end(); it++)
    {
      answer.insert(std::make_pair(it->first, colors[i]));
      i++;
    }
    ofstream output;
    output.open(argv[2]);
    // Call printSolution to output the answers to the output file
    printSolution(answer, output);
    output.close();
    return 0;
}

void solve(vector<std::vector<int>>& adjm, int index, const int& countries, std::vector<int>& colors)
{
  if(index == countries)
  {
    return;
  }
    for(int c = 1; c<=4; c++)
    {
      //check if this is a valid choice
      if(isValid(adjm, colors, index, c))
      {
        colors[index] = c;
        solve(adjm, index+1, countries, colors);
      }
    }
}

bool isValid(vector<std::vector<int>>& adjm, std::vector<int>& colors, int index, int c)
{
  std::vector<int> v = adjm[index];
  for(size_t i = 0; i<v.size(); i++)
  {
    if(colors[v[i]] == c)
    {
      return false;
    }
  }
  return true;
}

void readFile(std::istream& is, int& countries, int& row, int& col, vector<vector<char>>& grid,
   map<char,std::set<char>>& matrix, vector<std::vector<int>>& adjm, map<char,int>& charToIndex)
{
  is >> countries >> row >> col;
  char a;
  for(int i = 0; i<row; i++)
  {
    vector<char> v;
    for(int j = 0; j<col; j++)
    {
      is >> a;
      v.push_back(a);
    }
    grid.push_back(v);
  }

  //create an adjacency matrix for the graph
  for(int i = 0; i<row; i++)
  {
    for(int j = 0; j<col; j++)
    {
      std::set<char>::iterator x;
      map<char,std::set<char>>::iterator it = matrix.find(grid[i][j]);
      //insert the country if it doesnt already exist
      if(it == matrix.end())
      {
        std::set<char> s;
        matrix.insert(std::make_pair(grid[i][j], s));
        it = matrix.find(grid[i][j]);
      }
      if(i+1 < row)
      {
        a = grid[i+1][j];
        x = (it->second).find(a);
        if(a != grid[i][j] && x == (it->second).end())
        {
          it->second.insert(a);
        }
      }
      if(i-1 >= 0)
      {
        a = grid[i-1][j];
        x = (it->second).find(a);
        if(a != grid[i][j] && x == (it->second).end())
        {
          it->second.insert(a);
        }
      }
      if(j+1 < col)
      {
        a = grid[i][j+1];
        x = (it->second).find(a);
        if(a != grid[i][j] && x == (it->second).end())
        {
          it->second.insert(a);
        }
      }
      if(j-1 >= 0)
      {
        a = grid[i][j-1];
        x = (it->second).find(a);
        if(a != grid[i][j] && x == (it->second).end())
        {
          it->second.insert(a);
        }
      }
    }
  }
  size_t x = 0;
  for(map<char,std::set<char>>::iterator it = matrix.begin(); it!= matrix.end(); it++)
  {
    charToIndex.insert(std::make_pair(it->first, x));
    x++;
  }
  x = 0;
  for(map<char,std::set<char>>::iterator it = matrix.begin(); it!= matrix.end(); it++)
  {
    std::set<char> s = it->second;
    vector<int> v;
    for(std::set<char>::iterator n = s.begin(); n != s.end(); n++)
    {
      map<char,int>::iterator c = charToIndex.find(*n);
      v.push_back(c->second);
    }
    adjm.push_back(v);
    x++;
  }
}

void printSolution(std::map<char,int>& answer, std::ostream& os)
{
    for(std::map<char,int>::iterator it = answer.begin();
            it!= answer.end();
            ++it) {
        os << it->first << " " << it->second << endl;
    }
}
