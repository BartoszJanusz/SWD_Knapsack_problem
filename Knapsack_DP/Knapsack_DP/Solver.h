#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "Data.h"

class Solver
{
public:
	Solver() = default;
	Solver(const Data &data);
	virtual ~Solver() = default;
	virtual std::pair<int, std::vector<int>> solve() = 0;
	const std::vector<std::pair<int, int>> getItems() const;
	
	unsigned getItemsWeight(std::pair<int, std::vector<int>> result) const;

protected:
	int knapsackSize;
	std::vector<std::pair<int, int>> items;
};

