#pragma once
#include <vector>
#include <algorithm>
#include "Solver.h"

class DynamicProgrammingSolver : public Solver
{
public:
	DynamicProgrammingSolver();
	DynamicProgrammingSolver(const Data& data);
	~DynamicProgrammingSolver() = default;

	unsigned getRecursiveCalls();

	virtual std::pair<int, std::vector<int>> solve() override;
private:
	std::pair<int, std::vector<int>> calculateValue(int kSize);
	
	unsigned recursiveCallsCounter;

};

