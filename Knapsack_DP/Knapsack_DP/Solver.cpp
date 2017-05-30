#include "Solver.h"

using std::string;
using std::cout;
using std::endl;

Solver::Solver(const Data &data)
{
	this->knapsackSize = data.knapsack_size;
	this->items = data.items;
}

const std::vector<std::pair<int, int>> Solver::getItems() const
{
	return items;
}

unsigned Solver::getItemsWeight(std::pair<int, std::vector<int>> result) const
{
	unsigned retVal = 0;
	for (unsigned i = 0; i < result.second.size(); i++)
	{
		retVal += result.second[i] * items[i].first;
	}

	return retVal;
}