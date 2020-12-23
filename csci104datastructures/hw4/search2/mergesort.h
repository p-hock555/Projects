#ifndef MERGESORT_H
#define MERGESORT_H
#include <vector>

template<class Compare>
std::vector<std::pair<WebPage*, double>> mergesort(std::vector<std::pair<WebPage*, double>>& inputset, Compare c);

template<class Compare>
std::vector<std::pair<WebPage*, double>> merge(std::vector<std::pair<WebPage*, double>>& lhs, std::vector<std::pair<WebPage*, double>>& rhs, Compare comp);


class compr
{
public:
  bool operator()(const std::vector<std::pair<WebPage*, double>>& lhs, const std::vector<std::pair<WebPage*, double>>& rhs) const
  {
    return lhs[0].second > rhs[0].second;
  }
};

class compn
{
public:
  bool operator()(const std::vector<std::pair<WebPage*, double>>& lhs, const std::vector<std::pair<WebPage*, double>>& rhs) const
  {
    std::string lhs_page_name = lhs[0].first->filename();
    std::string rhs_page_name = rhs[0].first->filename();

    lhs_page_name = conv_to_lower(lhs_page_name);
    rhs_page_name = conv_to_lower(rhs_page_name);

    char l = lhs_page_name[0];
    char r = rhs_page_name[0];

    return l < r;
  }
};


template <class Compare>
std::vector<std::pair<WebPage*, double>> mergesort(std::vector<std::pair<WebPage*, double>>& inputset, Compare comp)
{

  if(inputset.size() <= 1)
  {
    return inputset;
  }
  std::vector<std::pair<WebPage*, double>> lhs;
  std::vector<std::pair<WebPage*, double>> rhs;
  std::vector<std::pair<WebPage*, double>> retvec;
  size_t middle = (inputset.size()+1)/2;

  for(size_t i = 0; i<middle; i++)
  {
    lhs.push_back(inputset[i]);
  }
  for(size_t i = middle; i<inputset.size(); i++)
  {
    rhs.push_back(inputset[i]);
  }

  lhs = mergesort(lhs, comp);
  rhs = mergesort(rhs, comp);

  retvec = merge(lhs, rhs, comp);

  return retvec;
}

template <class Compare>
std::vector<std::pair<WebPage*, double>> merge(std::vector<std::pair<WebPage*, double>>& lhs, std::vector<std::pair<WebPage*, double>>& rhs, Compare comp)
{
  std::vector<std::pair<WebPage*, double>> retvec;
  while(lhs.size() > 0 || rhs.size() > 0)
  {
    if(lhs.size() > 0 && rhs.size() > 0)
    {
      if (comp(lhs, rhs))
      {
        retvec.push_back(lhs.front());
        lhs.erase(lhs.begin());
      }
      else{
        retvec.push_back(rhs.front());
        rhs.erase(rhs.begin());
      }
    }
    else if (lhs.size() > 0)
    {
      for (size_t i = 0; i < lhs.size(); i++)
      {
        retvec.push_back(lhs[i]);
      }
      break;
    }
    else if (rhs.size() > 0)
    {
      for (size_t i = 0; i < rhs.size(); i++)
      {
        retvec.push_back(rhs[i]);
      }
      break;
    }
   }
   return retvec;
}

#endif
