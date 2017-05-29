#include "DynamicProgrammingSolver.h"



DynamicProgrammingSolver::DynamicProgrammingSolver()
{
	recursiveCallsCounter = 0;
}

DynamicProgrammingSolver::DynamicProgrammingSolver(Data& data)
{
	this->knapsackSize = data.knapsack_size;
	this->items = data.items;
	//this->items_count.resize(items.size());

	//std::fill(items_count.begin(), items_count.end(), 0);
}

std::pair<int, std::vector<int>> DynamicProgrammingSolver::calculateValue(int kSize)
{
	recursiveCallsCounter++;
	std::vector<int> items_count;
	int max_value = -1;
	int max_index = -1;

	if (kSize == 0)
		return std::pair<int, std::vector<int>>(0, std::vector<int>(items.size(), 0));
	else
	{
		for (int i = 0; i < items.size(); ++i)
		{
			if (items[i].first <= kSize)
			{
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