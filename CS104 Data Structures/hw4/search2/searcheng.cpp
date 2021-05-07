#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "util.h"

using namespace std;


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
  parsers_.clear();

  std::map<std::string, WebPage*>::iterator b;
  for(b =  webpage_file_map.begin(); b != webpage_file_map.end(); b++)
  {
    delete b->second;
  }
  webpage_file_map.clear();

  std::map<std::string, WebPageSet>::iterator c;
  for(c = webpage_term_map.begin(); c != webpage_term_map.end(); c++)
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

std::vector<std::pair<WebPage*, double> > SearchEng::pageRank(const WebPageSet& in_pages)
{
  double d = .85;
  std::vector<std::pair<WebPage*, double> > old_pr;
  std::vector<std::pair<WebPage*, double> > curr_pr;
  std::map<WebPage*, std::set<WebPage*>> out_links_to_idx;
  std::map<WebPage*, std::set<WebPage*>> inc_links_to_idx;
  std::set<WebPage*> canset;
  std::set<WebPage*>::iterator it = in_pages.begin();
  //insert the incoming links in the set of webpages;
  while(it != in_pages.end())
  {
    canset.insert(*it);
    std::set<WebPage*> inc_links = (*it)->incoming_links();
    std::set<WebPage*>::iterator i = inc_links.begin();
    while(i != inc_links.end())
    {
      if(canset.find(*i) == canset.end())
      {
        canset.insert(*i);
      }
      i++;
    }
    it++;
  }
  //insert the outgoig links in the set of webpages;
  it = in_pages.begin();
  while(it != in_pages.end())
  {
    std::set<WebPage*> out_links = (*it)->outgoing_links();
    std::set<WebPage*>::iterator i = out_links.begin();
    while(i != out_links.end())
    {
      if(canset.find(*i) == canset.end())
      {
        canset.insert(*i);
      }
      i++;
    }
    it++;
  }
  //get the out links and in links of every node.
  it = canset.begin();
  while(it != canset.end())
  {
    WebPageSet inl = (*it)->incoming_links();
    WebPageSet otl = (*it)->outgoing_links();
    otl.insert(*it); //this is for the self loop or link to itself
    inc_links_to_idx.insert(std::make_pair(*it, inl));
    out_links_to_idx.insert(std::make_pair(*it, otl));
    it++;
  }
  //normalization of all starting pageranks
  it = canset.begin();
  while(it != canset.end())
  {
    old_pr.push_back(std::make_pair(*it, 1/canset.size()));
    curr_pr.push_back(std::make_pair(*it, 0));
    it++;
  }

  //calculating pageRank
  for(int b = 0; b<20; b++)
  {
    std::set<WebPage*>::iterator a;
    for(size_t i = 0; i <= old_pr.size(); i++)
    {
      std::map<WebPage*, std::set<WebPage*>>::iterator q = inc_links_to_idx.find(old_pr[i].first);
      WebPageSet temp_il = q->second;
      std::set<WebPage*>::iterator x = temp_il.begin();
      while(x != temp_il.end())
      {
        std::map<WebPage*, std::set<WebPage*>>::iterator a = out_links_to_idx.find(old_pr[i].first);
        WebPageSet temp_ol = a->second;
        curr_pr[i].second += (old_pr[i].second/temp_ol.size());
        x++;
      }
      curr_pr[i].second = (1-d) + (d * curr_pr[i].second);
      old_pr[i].second = curr_pr[i].second;
    }
  }

  return old_pr;


}
