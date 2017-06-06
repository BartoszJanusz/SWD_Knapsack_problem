#include "SolverFactory.h"



Solver * SolverFactory::constructSolver(SolverType type)
{
	switch (type)
	{
		case GREEDY:
			return new GreedyAlgorithmSolver();
		case DYNAMIC:
			return new DynamicProgrammingSolver();
		case DYNAMIC_HASHMAP:
			return new DynamicProgrammingHashMapSolver();
		default:
			return nullptr;
	}
}

Solver * SolverFactory::constructSolver(SolverType type, const Data & data)
{
	switch (type)
	{
		case GREEDY:
			return new GreedyAlgorithmSolver(data);
		case DYNAMIC:
			return new DynamicProgrammingSolver(data);
		case DYNAMIC_HASHMAP:
			return new DynamicProgrammingHashMapSolver(data);
		default:
			return nullptr;
	}
}

