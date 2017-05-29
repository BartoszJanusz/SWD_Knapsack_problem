#include "DynamicProgrammingSolver.h"

DynamicProgrammingSolver::DynamicProgrammingSolver() : Solver()
{
	recursiveCallsCounter = 0;
}

DynamicProgrammingSolver::DynamicProgrammingSolver(const Data& data) : Solver(data)
{
	recursiveCallsCounter = 0;
}

std::pair<int, std::vector<int>> DynamicProgrammingSolver::calculateValue(int kSize)
{
	recursiveCallsCounter++;

	std::vector<int> items_count;
	int max_value = -1;
	int max_index = -1;

	// When passed kSize is 0, return vector filled with zeros
	if (kSize == 0)
	{
		return std::pair<int, std::vector<int>>(0, std::vector<int>(items.size(), 0));
	}
	else
	{
		// For every item check if it is the best-fit item (max gained value)
		for (int i = 0; i < items.size(); ++i)
		{
			// If item fits in current knapsack
			if (items[i].first <= kSize)
			{
				// Recursively check if it is best-fit
				auto res = calculateValue(kSize - items[i].first);
				int value = items[i].second + res.first;

				if (value > max_value)
				{
					max_value = value;
					max_index = i;
					items_count = std::move(res.second);
				}
			}
		}

		// When none of items fit in knapsack, return vector filled with zeros
		if (max_value == -1)
			return std::pair<int, std::vector<int>>(0, std::vector<int>(items.size(), 0));

		items_count[max_index] += 1;

		return std::pair<int, std::vector<int>>(max_value, std::move(items_count));
	}
}

std::pair<int, std::vector<int>> DynamicProgrammingSolver::solve()
{
	recursiveCallsCounter = 0;
	return calculateValue(knapsackSize);
}

unsigned DynamicProgrammingSolver::getRecursiveCalls()
{
	return recursiveCallsCounter;
}