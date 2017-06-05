#include "DynamicProgrammingSolver.h"

DynamicProgrammingSolver::DynamicProgrammingSolver() : Solver()
{
	calculateValueCalls = 0;
}

DynamicProgrammingSolver::DynamicProgrammingSolver(const Data& data) : Solver(data)
{
	calculateValueCalls = 0;
}

std::pair<int, std::vector<int>> DynamicProgrammingSolver::calculateValue(int kSize)
{
	calculateValueCalls++;

	std::vector<int> items_count;
	int max_value = -1;
	int max_index = -1;

	// When passed kSize is 0, return vector filled with zeros
	if (kSize == 0)
	{
		auto retVal = std::pair<int, std::vector<int>>(0, std::vector<int>(items.size(), 0));
#ifdef _DEBUG
		Logger::getLogger().log("return kSize == 0", retVal);
#endif // DEBUG
		return retVal;
	}
	else
	{
		// For every item check if it is the best-fit item (max gained value)
		for (size_t i = 0; i < items.size(); ++i)
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
		{
			auto retVal = std::pair<int, std::vector<int>>(0, std::vector<int>(items.size(), 0));
#ifdef _DEBUG
			std::stringstream ss;
			ss << "return kSize == " << kSize;
			Logger::getLogger().log(ss.str(), retVal);
#endif // DEBUG
			return retVal;
		}

		items_count[max_index] += 1;

		auto retVal = std::pair<int, std::vector<int>>(max_value, std::move(items_count));
#ifdef _DEBUG
		std::stringstream ss;
		ss << "return kSize == " << kSize;
		Logger::getLogger().log(ss.str(), retVal);
#endif // DEBUG
		return retVal;
	}
}

std::pair<int, std::vector<int>> DynamicProgrammingSolver::solve()
{
	calculateValueCalls = 0;
	return calculateValue(knapsackSize);
}

unsigned DynamicProgrammingSolver::getCalculateValueCalls()
{
	return calculateValueCalls;
}

std::string DynamicProgrammingSolver::getName() const
{
	return QUOTE(DynamicProgrammingSolver);
}
