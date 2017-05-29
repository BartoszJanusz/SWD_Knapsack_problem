#pragma once
#include <vector>
#include <algorithm>
#include "Data.h"

class DynamicProgrammingSolver
{
private:
	int knapsackSize;
	std::vector<std::pair<int, int>> items;
	//std::vector<int> items_count;
	std::pair<int, std::vector<int>> calculateValue(int kSize);
	unsigned recursiveCallsCounter;
public:
	DynamicProgrammingSolver();
	DynamicProgrammingSolver(Data& data);
	
	std::pair<int, std::vector<int>> solve();
	unsigned getRecursiveCalls();
};

