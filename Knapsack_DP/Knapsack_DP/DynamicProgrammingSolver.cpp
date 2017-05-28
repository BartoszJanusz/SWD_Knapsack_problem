#include "DynamicProgrammingSolver.h"



DynamicProgrammingSolver::DynamicProgrammingSolver()
{
}

DynamicProgrammingSolver::DynamicProgrammingSolver(Data& data)
{
	this->knapsackSize = data.knapsack_size;
	this->items = data.items;
	this->items_count.resize(items.size());

	std::fill(items_count.begin(), items_count.end(), 0);
}


DynamicProgrammingSolver::~DynamicProgrammingSolver()
{
}
