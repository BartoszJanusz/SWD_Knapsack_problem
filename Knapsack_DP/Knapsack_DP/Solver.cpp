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

