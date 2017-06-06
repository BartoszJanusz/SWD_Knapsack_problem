#pragma once
#include "Solver.h"
#include "GreedyAlgorithmSolver.h"
#include "DynamicProgrammingSolver.h"
#include "DynamicProgrammingHashMapSolver.h"
#include "Data.h"

enum SolverType
{
	GREEDY,
	DYNAMIC,
	DYNAMIC_HASHMAP
};


class SolverFactory
{
public:
	static Solver* constructSolver(SolverType type);
	static Solver* constructSolver(SolverType type, const Data& data);
private:
	SolverFactory() = delete;
	~SolverFactory() = delete;
};

