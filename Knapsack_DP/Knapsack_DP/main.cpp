#include <iterator>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Data.h"
#include "DynamicProgrammingSolver.h"
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
			line.first = *(file_iterator++);
			line.second = *(file_iterator++);
			data.items.push_back(line);
		}
	}
	else cout << "Error in access to file!" << endl;
}

int main() {

	Data data;

	readFromFile("data.txt", data);

	cout << data.knapsack_size << endl;
	
	for(auto item : data.items)
		cout << item.first<<" " <<item.second << endl;

	DynamicProgrammingSolver solver(data);

	Timer timer;
	timer.start();
	auto result = solver.solve();
	timer.stop(SECONDS);

	cout << endl << "Items in knapsack value:  " << result.first << endl;
	cout << "Items count: " << endl;
	for (int i = 0; i < result.second.size(); i++)
		cout << "Category: " << i << "  Count: " << result.second[i] << endl;
	
	cout << "Number of calls to calculateValue: " << solver.getRecursiveCalls() << endl;
	cout << "Elapsed time: " << timer.getTime(SECONDS) << " s" << endl;
	cout << "Elapsed time: " << timer.getTime(MILISECONDS)<< " ms" << endl;
	cout << "Elapsed time: " << timer.getTime(MICROSECONDS) << " us" << endl;


	system("pause");
}