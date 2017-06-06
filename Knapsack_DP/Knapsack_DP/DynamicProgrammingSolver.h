#pragma once
#include <vector>
#include <algorithm>
#include "Solver.h"
#include "Logger.h"
#include <unordered_map>

//#define USE_MAP_OPTIMALIZATION

class DynamicProgrammingSolver : public Solver
{
public:
	// Constructors and destructors
	DynamicProgrammingSolver();
	DynamicProgrammingSolver(const Data& data);
	virtual ~DynamicProgrammingSolver() = default;

	// Getters
	unsigned getCalculateValueCalls();
	virtual std::string getName() const override;

	virtual std::pair<int, std::vector<int>> solve() override;

	virtual void clearHelperStructures() override;
protected:
	virtual std::pair<int, std::vector<int>> calculateValue(int kSize);

	unsigned calculateValueCalls;
};

