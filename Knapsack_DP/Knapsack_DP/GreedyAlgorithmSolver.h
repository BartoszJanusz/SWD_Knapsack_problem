#pragma once
#include "Solver.h"

class GreedyAlgorithmSolver : public Solver
{
public:
	GreedyAlgorithmSolver();
	GreedyAlgorithmSolver(const Data &data);
	virtual ~GreedyAlgorithmSolver() = default;

	virtual std::pair<int, std::vector<int>> solve() override;
	virtual std::string getName() const override;
};

