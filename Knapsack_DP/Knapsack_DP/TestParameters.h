#pragma once
#include "Solver.h"
#include "Data.h"

class TestParameters
{
public:
	TestParameters();
	~TestParameters();

	std::vector<Solver*> solvers;
	std::vector<int> knapsackSizes;
	Range costRange;
	Range valueRange;
	uint itemsToGenerate;
	uint repeats;

	std::string additionalInfo;
};

