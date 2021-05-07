#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "md_parser.h"
#include "txt_parser.h"
#include "util.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "Must provide an index file and output file" << endl;
        return 1;
    }

    // ---------------------- [TO BE COMPLETED] -------------------------------
    set<string> processed;
    //add parsers to the map for crawl()
    map<string, PageParser*> parsers;
    PageParser* mdp = new MDParser;
    PageParser* txtp = new TXTParser;
    parsers.insert(std::make_pair("md", mdp));
    parsers.insert(std::make_pair("txt", txtp));

    ifstream inputFile;
    inputFile.open(argv[1]);
    if(!inputFile)
    {
      cout << "unable to open file" << endl;
    }
    ofstream output(argv[2]);
    string filename;

    while(inputFile >> filename)
    {
      string type = extract_extension(filename);
      map<std::string, PageParser*>::iterator it = parsers.find(type);
      //file opened did not contain a link
      if(it == parsers.end())
      {
        continue;
      }
      (it->second)->crawl(parsers, filename, processed, output);
    }
    inputFile.close();

    // You may add cleanup code here if necessary
    map<string, PageParser*>::iterator it;
    for(it = parsers.begin(); it != parsers.end(); it++)
    {
      delete it->second;
    }
    parsers.clear();

    return 0;
}
