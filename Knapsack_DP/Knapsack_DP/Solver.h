#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "Data.h"
#include <typeinfo>

#define QUOTE(x) #x

class Solver
{
public:
	Solver() = default;
	Solver(const Data &data);
	virtual ~Solver() = default;
	virtual std::pair<int, std::vector<int>> solve() = 0;
	
	// Getters
	int getKnapsackSize() const;
	const std::vector<std::pair<int, int>> getItems() const;
	unsigned getItemsWeight(std::pair<int, std::vector<int>> result) const;
	virtual std::string getName() const;
	Data getData() const;

	// Setters
	virtual void setData(const Data& data);

	virtual void clearHelperStructures() = 0;

	static bool compareResults(std::pair<int, std::vector<int>> lhs, std::pair<int, std::vector<int>> rhs);
protected:
	int knapsackSize;
	std::vector<std::pair<int, int>> items;
};

