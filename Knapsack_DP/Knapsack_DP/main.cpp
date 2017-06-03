#include <iterator>
#include <string>
#include <iostream>
#include <vector>
#include "Data.h"
#include "DynamicProgrammingSolver.h"
#include "GreedyAlgorithmSolver.h"
#include "Timer.h"


using std::string;
using std::cout;
using std::endl;


int main()
{
	Data data;
	//data.readFromFile("data.txt");
	data.generateKnapsackSize(std::make_pair(80, 150));
	data.generateItems(std::make_pair(15, 30), std::make_pair(30, 60), 30);
	cout << "Knapsack size: " << data.getKnapsackSize() << "\nItems:" << endl;

	// Dynamic programming
	cout << "========== DYNAMIC PROGRAMMING ==========" << endl;
	DynamicProgrammingSolver dynamicSolver(data);
	Timer timer;
	timer.start();
	auto dynamicResult = dynamicSolver.solve();
	timer.stop();

	for (auto item : dynamicSolver.getItems())
	{
		auto ratio = static_cast<double>(item.second) / static_cast<double>(item.first);
		printf("w: %3d v: %3d v/w: %3.2f\n", item.first, item.second, ratio);
	}

	cout << endl << "Items in knapsack value:  " << dynamicResult.first << endl;
	cout << "Items in knapsack weight:  " << dynamicSolver.getItemsWeight(dynamicResult) << endl;
	cout << endl << "Items count: " << endl;
	for (int i = 0; i < dynamicResult.second.size(); i++)
		cout << "Category: " << i << "  Count: " << dynamicResult.second[i] << endl;

	cout << endl << "Number of calls to calculateValue: " << dynamicSolver.getCalculateValueCalls() << endl;
	printf("Elapsed time: %3.3f s\n", timer.getTime(SECONDS));
	printf("Elapsed time: %3.3f ms\n", timer.getTime(MILISECONDS));
	printf("Elapsed time: %3.0f us\n", timer.getTime(MICROSECONDS));

	// Greedy algorithm
	cout << "\n========== GREEDY ALGORITHM ==========" << endl;
	GreedyAlgorithmSolver greedySolver(data);
	timer.start();
	auto greedyResult = greedySolver.solve();
	timer.stop();

	for (auto item : greedySolver.getItems())
	{
		auto ratio = static_cast<double>(item.second) / static_cast<double>(item.first);
		printf("w: %3d v: %3d v/w: %3.2f\n", item.first, item.second, ratio);
	}

	cout << endl << "Items in knapsack value:   " << greedyResult.first << endl;
	cout << "Items in knapsack weight:  " << greedySolver.getItemsWeight(greedyResult) << endl;
	cout << endl << "Items count: " << endl;
	for (int i = 0; i < greedyResult.second.size(); i++)
		cout << "Category: " << i << "  Count: " << greedyResult.second[i] << endl;

	printf("\nElapsed time: %3.3f s\n", timer.getTime(SECONDS));
	printf("Elapsed time: %3.3f ms\n", timer.getTime(MILISECONDS));
	printf("Elapsed time: %3.0f us\n", timer.getTime(MICROSECONDS));

	system("pause");
}