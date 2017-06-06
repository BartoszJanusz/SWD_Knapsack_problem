#pragma once
#include "SolverFactory.h"
#include <set>

class TestParameters
{
public:
	TestParameters() = default;
	~TestParameters() = default;

	std::set<SolverType> solvers;
	std::vector<int> knapsackSizes;
	Range costRange;
	Range valueRange;
	uint itemsToGenerate;
	uint repeats;

	std::string additionalInfo;
};

