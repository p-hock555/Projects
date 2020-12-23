//
// You must provide your implementation of maxGroceryBox() and all
// helper functions in this file.
//

#include "grocery.h"

// You may prototype helper functions here and implement them below


std::vector<GItem> maxGroceryBox(const std::vector<GItem>& inventory, int weight_limit)
{
    // TODO implement!
		std::vector<std::vector<GItem>> res;
		std::vector<GItem> curr;
		for(size_t i = 0; i<inventory.size(); i++)
		{
			curr.push_back(inventory[i]);
			helper(inventory, weight_limit-(inventory[i].weight), i+1, res, curr);
			curr.pop_back();
		}
		return count(res);
}

void helper(const std::vector<GItem>& inventory, int lim, int idx, std::vector<std::vector<GItem>>& res, std::vector<GItem>& curr)
{
	if(idx == (int)inventory.size())
	{
		return;
	}
	if (lim>=0 && idx < (int)inventory.size()){
    res.push_back(curr);
    return;
	}
	else if(lim < 0)
	{
		return;
	}
	for (int i = idx; i<(int)inventory.size(); i++){
    if((inventory[i].weight)<=lim){
        curr.push_back(inventory[i]);
        helper(inventory, lim-(inventory[i].weight), i+1, res, curr);
        curr.pop_back();
			}
    }
}

std::vector<GItem> count(std::vector<std::vector<GItem>>& res)
{
	std::vector<int> count;
	int num = 0;
	for(int i = 0; i< (int)res.size(); i++)
	{
		num = 0;
		for(int j = 0; j<(int)res[i].size(); j++)
		{
			num += res[i][j].value;
		}
		count.push_back(num);
	}
	int max = 0;
	for(int i = 1; i<(int)count.size(); i++)
	{
		if(count[max]<count[i])
		{
			max = i;
		}
	}
	return res[max];
}
