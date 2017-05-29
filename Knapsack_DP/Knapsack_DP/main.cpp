#include <iterator>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Data.h"
#include "DynamicProgrammingSolver.h"
#include "GreedyAlgorithmSolver.h"
#include "Timer.h"


using std::string;
using std::cout;
using std::endl;


void readFromFile(string path, Data &data) {
	std::fstream file;
	file.open(path, std::ios::in);
	if (file.good() == true)
	{
		cout << "Success in access to file." << endl;
		auto file_iterator = std::istream_iterator<int>(file);
		data.knapsack_size = *(file_iterator++);
		while (file_iterator != std::istream_iterator<int>())
		{
			std::pair<int, int> line;
			// Read weight
			line.first = *(file_iterator++);
			// Read value
			line.second = *(file_iterator++);
			data.items.push_back(line);
		}
	}
	else
	{
		cout << "Error in access to file!" << endl;
	}
}

int main() {

	Data data;

	readFromFile("data.txt", data);

	cout << "Knapsack size: " << data.knapsack_size << "\nItems:" << endl;
	
	

	// Dynamic programming
	cout << "========== DYNAMIC PROGRAMMING ==========" << endl;
	DynamicProgrammingSolver dynamicSolver(data);
	Timer timer;
	timer.start();
	auto dynamicResult = dynamicSolver.solve();
	timer.stop();

	for (auto item : dynamicSolver.getItems())
		cout << "w: " << item.first << " v: " << item.second << endl;

	cout << endl << "Items in knapsack value:  " << dynamicResult.first << endl;
	cout << "Items count: " << endl;
	for (int i = 0; i < dynamicResult.second.size(); i++)
		cout << "Category: " << i << "  Count: " << dynamicResult.second[i] << endl;
	
	cout << "Number of calls to calculateValue: " << dynamicSolver.getRecursiveCalls() << endl;
	cout << "Elapsed time: " << timer.getTime(SECONDS) << " s" << endl;
	cout << "Elapsed time: " << timer.getTime(MILISECONDS)<< " ms" << endl;
	cout << "Elapsed time: " << timer.getTime(MICROSECONDS) << " us" << endl;

	// Greedy algorithm
	cout << "\n========== GREEDY ALGORITHM ==========" << endl;
	GreedyAlgorithmSolver greedySolver(data);
	timer.start();
	auto greedyResult = greedySolver.solve();
	timer.stop();

	for (auto item : dynamicSolver.getItems())
		cout << "w: " << item.first << " v: " << item.second << endl;

	cout << endl << "Items in knapsack value:  " << greedyResult.first << endl;
	cout << "Items count: " << endl;
	for (int i = 0; i < greedyResult.second.size(); i++)
		cout << "Category: " << i << "  Count: " << greedyResult.second[i] << endl;

	cout << "Elapsed time: " << timer.getTime(SECONDS) << " s" << endl;
	cout << "Elapsed time: " << timer.getTime(MILISECONDS) << " ms" << endl;
	cout << "Elapsed time: " << timer.getTime(MICROSECONDS) << " us" << endl;

	system("pause");
}