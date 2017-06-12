#include <iterator>
#include <string>
#include <iostream>
#include <vector>
#include "Data.h"
#include "GreedyAlgorithmSolver.h"
#include "DynamicProgrammingSolver.h"
#include "DynamicProgrammingHashMapSolver.h"
#include "Tester.h"

//#define TESTS

using std::string;
using std::cout;
using std::endl;

int main()
{
#ifdef TESTS
	GreedyAlgorithmSolver greedy;
	DynamicProgrammingSolver dynamic;
	DynamicProgrammingHashMapSolver dynamicHashMap;

	std::set<SolverType> solvers;

	solvers.emplace(GREEDY);
	//solvers.emplace(DYNAMIC);
	solvers.emplace(DYNAMIC_HASHMAP);

	TestParameters tp;
	tp.knapsackSizes = { 10000 };
	tp.costRange = std::make_pair(25, 30);
	tp.valueRange = std::make_pair(30, 60);
	tp.itemsToGenerate = 30;
	tp.repeats = 10;
	tp.solvers = std::move(solvers);

	Tester::test(tp, false);

#else
	Data data;
	//data.readFromFile("data.txt");
	data.generateKnapsackSize(std::make_pair(80, 100));
	data.generateItems(std::make_pair(30, 15), std::make_pair(30, 60), 30);
	cout << "Knapsack size: " 
		<< data.getKnapsackSize() 
		<< "\nItems:" << endl;

	for (auto item : data.getItems())
	{
		auto ratio = static_cast<double>(item.second) / static_cast<double>(item.first);
		printf("w: %3d v: %3d v/w: %3.2f\n", item.first, item.second, ratio);
	}

	// Dynamic programming
	cout << "\n========== DYNAMIC PROGRAMMING ==========" << endl;
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
	printf("Elapsed time: %3.3f ms\n", timer.getTime(MILLISECONDS));
	printf("Elapsed time: %3.0f us\n", timer.getTime(MICROSECONDS));

	// Dynamic programming optimized
	cout << "\n========== DYNAMIC PROGRAMMING OPTIMIZED ==========" << endl;
	DynamicProgrammingHashMapSolver dynamicHMSolver(data);
	timer.start();
	auto dynamicHMResult = dynamicHMSolver.solve();
	timer.stop();

	for (auto item : dynamicHMSolver.getItems())
	{
		auto ratio = static_cast<double>(item.second) / static_cast<double>(item.first);
		printf("w: %3d v: %3d v/w: %3.2f\n", item.first, item.second, ratio);
	}

	cout << endl << "Items in knapsack value:  " << dynamicHMResult.first << endl;
	cout << "Items in knapsack weight:  " << dynamicHMSolver.getItemsWeight(dynamicHMResult) << endl;
	cout << endl << "Items count: " << endl;
	for (int i = 0; i < dynamicHMResult.second.size(); i++)
		cout << "Category: " << i << "  Count: " << dynamicHMResult.second[i] << endl;

	cout << endl << "Number of calls to calculateValue: " << dynamicHMSolver.getCalculateValueCalls() << endl;
	printf("Elapsed time: %3.3f s\n", timer.getTime(SECONDS));
	printf("Elapsed time: %3.3f ms\n", timer.getTime(MILLISECONDS));
	printf("Elapsed time: %3.0f us\n", timer.getTime(MICROSECONDS));

	auto compareString = Solver::compareResults(dynamicHMResult, dynamicResult) ? "TRUE" : "FALSE";
	printf("Are results of dynamic programming algorithms exactly the same?: %s\n", 
		   compareString);

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
	printf("Elapsed time: %3.3f ms\n", timer.getTime(MILLISECONDS));
	printf("Elapsed time: %3.0f us\n", timer.getTime(MICROSECONDS));
#endif
	system("pause");
}