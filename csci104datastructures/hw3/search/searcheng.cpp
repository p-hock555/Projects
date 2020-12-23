#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;

std::string extract_extension(const std::string& filename);


SearchEng::SearchEng(PageParser* noExtensionParser)
{
    if (NULL == noExtensionParser)
    {
        throw std::invalid_argument("default parser cannot be NULL");
    }
    this->noExtensionParser_ = noExtensionParser;

    // Add additional code if necessary


}

SearchEng::~SearchEng()
{
  std::map<std::string, PageParser*>::iterator a;
  for(a = parsers_.begin(); a != parsers_.end(); a++)
  {
    delete a->second;
  }
  parsers_.clear();

  std::map<std::string, WebPage*>::iterator b;
  for(b =  webpage_file_map.begin(); b != webpage_file_map.end(); b++)
  {
    delete b->second;
  }
  webpage_file_map.clear();

  std::map<std::string, WebPageSet>::iterator c;
  for(c = webpage_term_map.begin(); c != webpage_term_map.end(); b++)
  {
    (c->second).clear();
  }
  webpage_term_map.clear();
  delete noExtensionParser_;

}

void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
  parsers_.insert(make_pair(extension, parser));
}

void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

void SearchEng::read_page(const std::string& filename)
{
  //1. parse the file
  //2. create a new webpage object
  //3. use the webpage member functions webpage file map and term map
  //finds the type of extension the file is
  PageParser* parser;
  WebPage* wpptr;
  std::map<std::string, WebPage*>::iterator it = webpage_file_map.find(filename);
  std::set<std::string> allSearchableTerms;
  std::set<std::string> allOutgoingLinks;
  std::string extension = extract_extension(filename);
  std::map<std::string, PageParser*>::iterator i = parsers_.find(extension);
  if(i != parsers_.end())
  {
    parser = i->second;
  }
  else{
    parser = noExtensionParser_;
  }

  //if the file doesnt exist in the map allocate a new WebPage
  if(it == webpage_file_map.end())
  {
    wpptr = new WebPage(filename);
    webpage_file_map.insert(make_pair(filename, wpptr));
  }
  //if it exists create a pointer to the existing one so we can update it
  else{
    wpptr = it->second;
  }

  parser->parse(filename, allSearchableTerms, allOutgoingLinks);
  //add terms to page
  wpptr->all_terms(allSearchableTerms);
  std::set<std::string>::iterator q;
  for(q = allOutgoingLinks.begin(); q != allOutgoingLinks.end(); q++)
  {
    std::map<std::string, WebPage*>::iterator ph = webpage_file_map.find(*q);
    //if we dont find the file make a new one and push back
    //also add to its incoming links
    if(ph == webpage_file_map.end())
    {
      WebPage* newpg = new WebPage(*q);
      newpg->add_incoming_link(wpptr);
      webpage_file_map.insert(make_pair(*q, newpg));
      wpptr->add_outgoing_link(newpg);
    }
    //add the webpage in the file map to the webpage
    else{
      wpptr->add_outgoing_link(ph->second);
    }

  }

  //add the terms to the webpage_term_map
  std::set<std::string>::iterator a;
   std::map<std::string, WebPageSet>::iterator temp;
  for(a = allSearchableTerms.begin(); a != allSearchableTerms.end(); a++)
  {
    temp = webpage_term_map.find(*a);
    if(temp == webpage_term_map.end())
    {
      //the term doesnt exist so add it to the webpage set
      WebPageSet newset;
      newset.insert(wpptr);
      webpage_term_map.insert(make_pair(*a, newset));
    }
    else{
      //the term already exists in the map so add the webpage to this set
      (temp->second).insert(wpptr);
    }
  }

  //add incoming links to other pages
  for(a = allOutgoingLinks.begin(); a != allOutgoingLinks.end(); a++)
  {
    std::map<std::string, WebPage*>::iterator i = webpage_file_map.find(*a);
    if(i != webpage_file_map.end())
    {
      //then the webpage exists
      (i->second)->add_incoming_link(wpptr);
    }
    else{
      //the webpage doesnt exist so allocate it.
      WebPage* newptr = new WebPage(*a);
      newptr->add_incoming_link(wpptr);
      webpage_file_map.insert(make_pair(*a, newptr));
    }
  }

}

WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
  std::map<std::string, WebPage*>::const_iterator it =  webpage_file_map.find(page_name);
  if(it != webpage_file_map.end())
  {
    //if the page exists in our map return a pointer to it
    return it->second;
  }
  else{
    //we didnt find it so return NULL
    return NULL;
  }
}

void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
  std::map<std::string, WebPage*>::const_iterator it = webpage_file_map.find(page_name);
  if(it == webpage_file_map.end())
  {
    //we didnt find it so throe an invalid argument
    throw std::invalid_argument("Invalid argument");
  }
  std::string extension = extract_extension(page_name);
  PageParser* parser;
  std::map<std::string, PageParser*>::const_iterator i = parsers_.find(extension);
  if(i != parsers_.end())
  {
    parser = i->second;
  }
  else{
    parser = noExtensionParser_;
  }
  std::string s = parser->display_text(page_name);
  cout << s << endl;
}

WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
  WebPageSet output;
  WebPageSet setA;
  WebPageSet setB;
  std::vector<std::string>::const_iterator it = terms.begin();
  std::map<std::string, WebPageSet>::const_iterator i = webpage_term_map.find(*it);

  if(i != webpage_term_map.end())
  {
    //first term exists in the map so save it to setA
     setA = i->second;
  }
  //now search through the rest of the list
  it++;
  while(it != terms.end())
  {
    i = webpage_term_map.find(*it);
    //we found the next term, so we combine the sets
    if(i != webpage_term_map.end())
    {
      setB = i->second;
      output = combiner->combine(setA, setB);
    }
    //if it doesn't exist then continue until we do
    it++;
  }
  output = combiner->combine(setA, setB);
  return output;
}

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}
