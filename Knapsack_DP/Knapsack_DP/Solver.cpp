#include "Solver.h"

using std::string;
using std::cout;
using std::endl;

Solver::Solver(const Data &data)
{
	this->knapsackSize = data.getKnapsackSize();
	this->items = data.getItems();
}

int Solver::getKnapsackSize() const
{
	return knapsackSize;
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

std::string Solver::getName() const
{
	auto& ti = typeid(Solver);
	return ti.name();
}

Data Solver::getData() const
{
	return Data(knapsackSize, items);
}

void Solver::setData(const Data & data)
{
	this->knapsackSize = data.getKnapsackSize();
	this->items = data.getItems();
}

bool Solver::compareResults(const std::pair<int, std::vector<int>> &lhs, const std::pair<int, std::vector<int>> &rhs)
{
	bool retVal = false;
	auto& lhsValue = lhs.first;
	auto& lhsKnapsack = lhs.second;
	auto& rhsValue = rhs.first;
	auto& rhsKnapsack = rhs.second;

	if (lhsValue == rhsValue)
	{
		if (lhsKnapsack == rhsKnapsack)
		{
			retVal = true;
		}
	}

	return retVal;
}

bool Solver::compareResults(const std::vector<std::pair<int, std::vector<int>>> &results)
{
	if (results.size() <= 1)
		return true;
	
	for (size_t i = 0; i < results.size() - 1; i++)
	{
		for (size_t j = i + 1; j < results.size(); j++)
		{
			auto retVal = compareResults(results[i], results[j]);
			if (!retVal)
				return false;
		}
	}

	return true;
}
