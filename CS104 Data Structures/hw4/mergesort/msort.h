#include <vector>

/**
 * Performs mergesort on the provided vector using
 * the Compare object, comp, to peform ALL comparisons
 *
 * Must run in O(n*log(n))
 */
template <class T, class Compare >
void mergeSort(std::vector<T>& list, Compare comp);


template <class T, class Compare >
void mergeSort(std::vector<T>& list, Compare comp)
{
	std::vector<T> lhs;
	std::vector<T> rhs;
	if(list.size() <= 1)
	{
		return;
	}

	size_t middle = (list.size()+1)/2;

	for(size_t i = 0; i<middle; i++)
	{
		lhs.push_back(list[i]);
	}
	for(size_t i = middle; i<list.size(); i++)
	{
		rhs.push_back(list[i]);
	}

	mergeSort(lhs, comp);
	mergeSort(rhs, comp);

	list = merge(lhs, rhs, comp);

}

template <class T, class Compare >
std::vector<T> merge(std::vector<T>& lhs, std::vector<T>& rhs, Compare comp)
{
	std::vector<T> retvec;
	while(lhs.size() > 0 || rhs.size() > 0)
	{
		if(lhs.size() > 0 && rhs.size() > 0)
		{
			if (comp(lhs.front(), rhs.front()))
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

template<class T>
 class LTEComparison {
 public:
 	bool operator()(const T& lhs, const T& rhs) const
 	{
 		return lhs <= rhs;
 	}
 };
