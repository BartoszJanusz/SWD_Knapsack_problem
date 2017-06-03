#include "Data.h"

Data::Data(int knapsackSize, const std::vector<std::pair<int, int>> &items)
{
	this->knapsackSize = knapsackSize;
	this->items = items;
}

Data::Data(int knapsackSize, std::vector<std::pair<int, int>> &&items)
{
	this->knapsackSize = knapsackSize;
	this->items = items;
}

const std::vector<std::pair<int, int>>& Data::getItems() const
{
	return items;
}

std::vector<std::pair<int, int>>& Data::getItems()
{
	return items;
}

void Data::setItems(const std::vector<std::pair<int, int>>& items)
{
	this->items = items;
}

int Data::getKnapsackSize() const
{
	return knapsackSize;
}

void Data::setKnapsackSize(int knapsackSize)
{
	this->knapsackSize = knapsackSize;
}

void Data::generateItems(std::pair<uint, uint> costRange, std::pair<uint, uint> valueRange, uint itemsToGenerate)
{
	if (costRange.first > costRange.second)
		std::swap(costRange.first, costRange.second);

	if (valueRange.first > valueRange.second)
		std::swap(valueRange.first, valueRange.second);

	std::vector<std::pair<int, int>> generatedItems;
	auto possibleToGenerate = (costRange.second - costRange.first) * (valueRange.second - valueRange.first);
	generatedItems.reserve(possibleToGenerate);

	printf("Items to generate: %u\nPossible items for given ranges: %u\n", itemsToGenerate, possibleToGenerate);

	for (auto i = costRange.first; i < costRange.second; i++)
	{
		for (auto j = valueRange.first; j < valueRange.second; j++)
		{
			generatedItems.emplace_back(std::make_pair(i, j));
		}
	}

	auto itemsTaken = std::min(itemsToGenerate, possibleToGenerate);
	std::random_shuffle(generatedItems.begin(), generatedItems.end());
	items = std::vector<std::pair<int, int>>(generatedItems.begin(), generatedItems.begin() + itemsTaken);
}

void Data::generateKnapsackSize(std::pair<uint, uint> sizeRange)
{
	if (sizeRange.first > sizeRange.second)
		std::swap(sizeRange.first, sizeRange.second);

	// Seed with a real random value, if available
	std::random_device randomDevice;

	// Choose a random mean between 1 and 6
	std::default_random_engine engine(randomDevice());
	std::uniform_int_distribution<int> uniform_dist(sizeRange.first, sizeRange.second);

	knapsackSize = uniform_dist(engine);
}

bool Data::readFromFile(std::string path)
{
	std::fstream file;
	file.open(path, std::ios::in);
	if (file.good() == true)
	{
		std::cout << "Success in access to file." << std::endl;
		auto file_iterator = std::istream_iterator<int>(file);
		knapsackSize = *(file_iterator++);
		while (file_iterator != std::istream_iterator<int>())
		{
			std::pair<int, int> line;
			// Read weight
			line.first = *(file_iterator++);
			// Read value
			line.second = *(file_iterator++);
			items.push_back(line);
		}
		return true;
	}
	else
	{
		std::cout << "Error in access to file!" << std::endl;
		return true;
	}
}