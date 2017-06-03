#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <iostream>
#include <iterator>

typedef unsigned int uint;

class Data 
{
public:
	Data() = default;
	Data(int knapsackSize, const std::vector<std::pair<int, int>> &items);
	Data(int knapsackSize, std::vector<std::pair<int, int>> &&items = std::vector<std::pair<int, int>>());

	// Access methods for fields
	const std::vector<std::pair<int, int>>& getItems() const;
	std::vector<std::pair<int, int>>& getItems();
	void setItems(const std::vector<std::pair<int, int>>& items);

	int getKnapsackSize() const;
	void setKnapsackSize(int knapsackSize);

	// Random data generation
	void generateItems(std::pair<uint, uint> costRange, std::pair<uint, uint> valueRange, uint itemsToGenerate);
	void generateKnapsackSize(std::pair<uint, uint> sizeRange);

	bool readFromFile(std::string path);

private:
	int knapsackSize;
	std::vector<std::pair<int, int>> items;
};