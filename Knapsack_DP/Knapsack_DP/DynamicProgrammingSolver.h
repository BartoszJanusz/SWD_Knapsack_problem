#pragma once
#include <vector>
#include "Data.h"

class DynamicProgrammingSolver
{
private:
	int knapsackSize;
	std::vector<std::pair<int, int>> items;
	std::vector<int> items_count;
public:
	DynamicProgrammingSolver();
	DynamicProgrammingSolver(Data& data);
	~DynamicProgrammingSolver();
};

