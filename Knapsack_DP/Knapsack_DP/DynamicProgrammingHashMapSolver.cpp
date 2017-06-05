#include "DynamicProgrammingHashMapSolver.h"

DynamicProgrammingHashMapSolver::DynamicProgrammingHashMapSolver() : DynamicProgrammingSolver()
{
}

DynamicProgrammingHashMapSolver::DynamicProgrammingHashMapSolver(const Data& data) : DynamicProgrammingSolver(data)
{
}

std::string DynamicProgrammingHashMapSolver::getName() const
{
	auto& ti = typeid(DynamicProgrammingSolver);
	return ti.name();
}

std::pair<int, std::vector<int>> DynamicProgrammingHashMapSolver::calculateValue(int kSize)
{
	calculateValueCalls++;

	auto element = previousValuesMap.find(kSize);
	if (element != previousValuesMap.end())
		return element->second;

	std::vector<int> items_count;
	int max_value = -1;
	int max_index = -1;

	// When passed kSize is 0, return vector filled with zeros
	if (kSize == 0)
	{
		auto retVal = std::pair<int, std::vector<int>>(0, std::vector<int>(items.size(), 0));
		previousValuesMap.insert(std::make_pair(kSize, retVal));
#ifdef _DEBUG
		Logger::getLogger().log("return kSize == 0", retVal);
#endif // DEBUG
		return retVal;
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
		{
			auto retVal = std::pair<int, std::vector<int>>(0, std::vector<int>(items.size(), 0));
			previousValuesMap.insert(std::make_pair(kSize, retVal));
#ifdef _DEBUG
			std::stringstream ss;
			ss << "return kSize == " << kSize;
			Logger::getLogger().log(ss.str(), retVal);
#endif // DEBUG
			return retVal;
		}

		items_count[max_index] += 1;

		auto retVal = std::pair<int, std::vector<int>>(max_value, std::move(items_count));
		previousValuesMap.insert(std::make_pair(kSize, retVal));
#ifdef _DEBUG
		std::stringstream ss;
		ss << "return kSize == " << kSize;
		Logger::getLogger().log(ss.str(), retVal);
#endif // DEBUG
		return retVal;
	}
}