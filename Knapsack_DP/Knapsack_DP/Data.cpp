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

void Data::generateItems(uint costMin, uint costMax, uint valueMin, uint valueMax, uint itemsToGenerate)
{
	generateItems(std::make_pair(costMin, costMax), std::make_pair(valueMin, valueMax), itemsToGenerate);
}

void Data::generateKnapsackSize(uint sizeMin, uint sizeMax)
{
	generateKnapsackSize(std::make_pair(sizeMin, sizeMax));
}

void Data::generateItems(Range costRange, Range valueRange, uint itemsToGenerate)
{
	if (costRange.first > costRange.second)
		std::swap(costRange.first, costRange.second);

	if (valueRange.first > valueRange.second)
		std::swap(valueRange.first, valueRange.second);

	std::vector<std::pair<int, int>> generatedItems;
	auto possibleToGenerate = (costRange.second - costRange.first) * (valueRange.second - valueRange.first);
	generatedItems.reserve(possibleToGenerate);

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

void Data::generateKnapsackSize(Range sizeRange)
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

bool Data::writeToFile(std::string path)
{
	std::fstream file;
	file.open(path, std::ios::out);
	if (file.good() == true)
	{
		std::cout << "Success in access to file." << std::endl;
		file << knapsackSize << "\n";

		for (auto &item : items)
		{
			file << item.first << " " << item.second << "\n";
		}

		file.flush();
		return true;
	}
	else
	{
		std::cout << "Error in access to file!" << std::endl;
		return true;
	}
}
