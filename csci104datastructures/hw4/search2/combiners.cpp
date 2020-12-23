#include "combiners.h"
#include "searcheng.h"


// Place your function implementations for your derived
// WebPageSetCombiner classes here

WebPageSet ANDWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
  //WebPageSet = std::set<Webpage*>
  WebPageSet output;
  WebPageSet::iterator it;
  WebPageSet::iterator i;

  //if the two webpages exist in the same set then add to output
  if(setB.empty())
  {
    return setA;
  }
  for(it = setA.begin(); it != setA.end(); it ++)
  {
    i = setB.find(*it);
    if(i != setB.end())
    {
      output.insert(*it);
    }
  }
  return output;
}

WebPageSet ORWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
  WebPageSet output;
  WebPageSet::iterator it;
  WebPageSet::iterator i;

  //needs to run nlogn time
  //add both sets to output
  if(setB.empty())
  {
    return setA;
  }
  for(it = setA.begin(); it != setA.end(); it++)
  {
    //insert all webpages from setA
    output.insert(*it);
  }
  for(i = setB.begin(); i != setB.end(); i++)
  {
    it = output.find(*i);
    //if the webpage doesnt exist, then insert
    if(it == output.end())
    {
      output.insert(*i);
    }
  }
  return output;
}


WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
  WebPageSet output;
  WebPageSet::iterator it;
  WebPageSet::iterator i;

  if(setB.empty())
  {
    output = setA;
    return output;
  }

  for(it = setA.begin(); it != setA.end(); it++)
  {
    //insert the element in setA
    output.insert(*it);
    i = setB.find(*it);
    //if the element also exists in setB then erase it from the output
    if(i != setB.end())
    {
      output.erase(i);
    }
  }
  return output;
}
