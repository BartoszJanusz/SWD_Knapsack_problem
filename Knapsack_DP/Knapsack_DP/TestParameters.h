#pragma once
#include "Solver.h"
#include "Data.h"

class TestParameters
{
public:
	TestParameters();
	~TestParameters();

	std::vector<Solver*> solvers;
	Range costRange;
	Range valueRange;
	Range sizeRange;
	uint itemsToGenerate;
	uint repeats;

	std::string additionalInfo;
};

