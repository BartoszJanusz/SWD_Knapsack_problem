#include "GreedyAlgorithmSolver.h"
#include <iostream>

GreedyAlgorithmSolver::GreedyAlgorithmSolver() : Solver()
{

}

GreedyAlgorithmSolver::GreedyAlgorithmSolver(const Data &data) : Solver(data)
{

}

std::pair<int, std::vector<int>> GreedyAlgorithmSolver::solve()
{
	decltype(solve()) retVal(0, std::vector<int>(items.size(), 0));

	// Sorting items by value to weight ratio
	std::sort(items.begin(),
			  items.end(),
			  [](std::pair<int, int> lhs, std::pair<int, int> rhs)
	{
		return (static_cast<double>(lhs.second) / static_cast<double>(lhs.first)) > (static_cast<double>(rhs.second) / static_cast<double>(rhs.first));
	});

	auto freeSpace = knapsackSize;
	auto itemChosen = false;

	do
	{
		itemChosen = false;
		for (size_t i = 0; i < items.size(); i++)
		{
			if (freeSpace - items[i].first >= 0)
			{
				// Decrease free space
				freeSpace -= items[i].first;
				// Add item value to knapsack value
				retVal.first += items[i].second;
				// Increment chosen item count 
				retVal.second[i]++;
				itemChosen = true;
				break;
			}
		}
	} while (itemChosen);

	return retVal;
}

std::string GreedyAlgorithmSolver::getName() const
{
	return QUOTE(GreedyAlgorithmSolver);
}
