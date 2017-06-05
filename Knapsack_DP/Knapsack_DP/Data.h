#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <iostream>
#include <iterator>

typedef unsigned int uint;
typedef std::pair<uint, uint> Range;

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

	void generateItems(uint costMin, uint costMax, uint valueMin, uint valueMax, uint itemsToGenerate);
	void generateKnapsackSize(uint sizeMin, uint sizeMax);

	void generateItems(Range costRange, Range valueRange, uint itemsToGenerate);
	void generateKnapsackSize(Range sizeRange);

	// File manipulation
	bool readFromFile(std::string path);
	bool writeToFile(std::string path);

private:
	int knapsackSize;
	std::vector<std::pair<int, int>> items;
};