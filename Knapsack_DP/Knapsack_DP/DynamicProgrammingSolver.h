#pragma once
#include <vector>
#include <algorithm>
#include "Solver.h"
#include "Logger.h"
#include <unordered_map>

#define USE_MAP_OPTIMALIZATION

class DynamicProgrammingSolver : public Solver
{
public:
	DynamicProgrammingSolver();
	DynamicProgrammingSolver(const Data& data);
	~DynamicProgrammingSolver() = default;

	unsigned getCalculateValueCalls();

	virtual std::pair<int, std::vector<int>> solve() override;
private:
	std::pair<int, std::vector<int>> calculateValue(int kSize);
	std::unordered_map<int, std::pair<int, std::vector<int>>> previousValuesMap;


	unsigned calculateValueCalls;
	unsigned kSizeZeroReturns;

};

