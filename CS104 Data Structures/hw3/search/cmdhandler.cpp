#include "cmdhandler.h"
#include "util.h"
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";
}

Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

PrintHandler::PrintHandler()
{

}

PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";
}

Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

IncomingHandler::IncomingHandler()
{

}

IncomingHandler::IncomingHandler(Handler* next)
  : Handler(next)
{


}

bool IncomingHandler::canHandle(const std::string& cmd) const
{
  return cmd == "INCOMING";

}

Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
  string page;
  WebPage* wp;


  if(!(instr >> page))
  {
    return HANDLER_ERROR;
  }
  try{
    //get the webpage
    wp = eng->retrieve_page(page);
    //get the incoming links
    WebPageSet p = wp->incoming_links();
    //print the incoming_links which are stored at a set of webpage pointers
    display_hits(p, ostr);
  }
  catch(std::exception& e){
    return HANDLER_ERROR;
  }
  return HANDLER_OK;


}
OutgoingHandler::OutgoingHandler()
{

}

OutgoingHandler::OutgoingHandler(Handler* next)
  : Handler(next)
{


}

bool OutgoingHandler::canHandle(const std::string& cmd) const
{
  return cmd == "OUTGOING";
}

Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
  string page;
  WebPage* wp;

  if(!(instr >> page))
  {
    return HANDLER_ERROR;
  }
  try{
    //search for the webpage
    wp = eng->retrieve_page(page);
    //call outgoing links on the WebPage
    WebPageSet p = wp->outgoing_links();
    //displays the number of outgoing links
    display_hits(p, ostr);
  }
  catch(std::exception& e){
    return HANDLER_ERROR;
  }
  return HANDLER_OK;

}

AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
  : Handler(next)
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
  return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
  string word;
  std::vector<std::string> terms;
  AndWebPageSetCombiner AndCombiner;
  WebPageSet wp_set;
  //no words are provided so use an empty set
  try{
    //read in terms from istream to a list while(instr >> word)
    while(instr >> word)
    {
      terms.push_back(word);
    }
    //use the search(vector<string> terms, WebPageSetCombiner combiner) to look for hits
    wp_set = eng->search(terms, &AndCombiner);
    //call display_hits(Webpageset hits, ostr) to output file names
    display_hits(wp_set, ostr);
  }
  catch(std::exception& e){
    return HANDLER_ERROR;
  }
  return HANDLER_OK;
}

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{


}

bool OrHandler::canHandle(const std::string& cmd) const
{
  return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
  string word;
  std::vector<std::string> terms;
  OrWebPageSetCombiner OrCombiner;
  WebPageSet wp_set;
  //no words are provided so use an empty set
    //read in terms from istream to a list while(instr >> word)
    while(instr >> word)
    {
      terms.push_back(word);
    }
    //use the search(vector<string> terms, WebPageSetCombiner combiner) to look for hits
    wp_set = eng->search(terms, &OrCombiner);
    display_hits(wp_set, ostr);
    return HANDLER_OK;

}

DiffHandler::DiffHandler()
{

}

DiffHandler::DiffHandler(Handler* next)
  : Handler(next)
{

}

bool DiffHandler::canHandle(const std::string& cmd) const
{
  return cmd == "DIFF";
}

Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
  string word;
  std::vector<std::string> terms;
  DiffWebPageSetCombiner DiffCombiner;
  WebPageSet wp_set;
  //no words are provided so use an empty set
    //read in terms from istream to a list while(instr >> word)
    while(instr >> word)
    {
      terms.push_back(word);
    }
    //use the search(vector<string> terms, WebPageSetCombiner combiner) to look for hits
    wp_set = eng->search(terms, &DiffCombiner);
    display_hits(wp_set, ostr);
    return HANDLER_OK;

}
