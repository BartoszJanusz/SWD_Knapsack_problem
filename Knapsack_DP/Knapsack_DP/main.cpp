#include <iterator>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Data.h"


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
		data.knapsack_size = *file_iterator++;
		while (file_iterator != std::istream_iterator<int>())
		{
			data.items.push_back(std::pair<int, int>(*file_iterator++, *file_iterator++));
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


	system("pause");
}