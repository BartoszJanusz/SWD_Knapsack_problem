#pragma once
#include "DynamicProgrammingSolver.h"


class DynamicProgrammingHashMapSolver :
	public DynamicProgrammingSolver
{
public:
	DynamicProgrammingHashMapSolver();
	DynamicProgrammingHashMapSolver(const Data& data);
	virtual ~DynamicProgrammingHashMapSolver() = default;

	// Getters
	virtual std::string getName() const override;

	// Setters
	virtual void setData(const Data& data) override;
private:
	virtual std::pair<int, std::vector<int>> calculateValue(int kSize) override;

	std::unordered_map<int, std::pair<int, std::vector<int>>> previousValuesMap;
};

