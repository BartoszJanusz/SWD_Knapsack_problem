#include "Tester.h"

void Tester::test(const TestParameters& tp, bool parallel)
{
	// Generating data for tests
	std::vector<Data> data;
	for (auto& d : data)
	{
		d.generateKnapsackSize(tp.sizeRange);
		d.generateItems(tp.costRange, tp.valueRange, tp.itemsToGenerate);
	}

	if (parallel)
	{
		std::vector<std::thread> threads;
		threads.reserve(tp.solvers.size());
		
		// Creating and starting testing threads
		for (size_t i = 0; i < tp.solvers.size(); i++)
		{
			threads.emplace_back(performNTests, tp.solvers[i], data, tp.repeats, tp.additionalInfo);
		}

		// Waiting for threads
		for (auto& t : threads)
		{
			t.join();
		}
	}
	else
	{
		for (auto& s : tp.solvers)
		{
			performNTests(s, data, tp.repeats, tp.additionalInfo);
		}
	}
}

std::string Tester::constructFileName(const Solver & solver, const std::string additionalInfo)
{
	// Building file name
	auto className = solver.getName();
	auto knapsackSize = solver.getKnapsackSize();
	auto itemCount = solver.getItems().size();
	std::stringstream ss;
	ss << className << "_" << knapsackSize << "-" << itemCount;
	if (!additionalInfo.empty())
		ss << "_" << additionalInfo;
	ss << ".txt";
	return ss.str();
}

void Tester::performNTests(Solver* solver, const std::vector<Data> &data, uint repeats, const std::string additionalInfo)
{
	for (auto& d : data)
	{
		// Setting new set of data
		solver->setData(d);

		// Constructing file name
		auto fileName = constructFileName(*solver, additionalInfo);

		// Opening file
		std::ofstream ofs(fileName, std::ios_base::out | std::ios_base::trunc);

		// Skipping loop iteration if error in opening occurs
		if (!ofs.good())
		{
			std::cerr << "Couldn't open file: " << fileName << std::endl;
			continue;
		}

		// Testing given number of times
		Timer timer;

		ofs << "# seconds | milliseconds | microseconds\n";
		for (decltype(repeats) i = 0; i < repeats; i++)
		{
			timer.start();
			solver->solve();
			timer.stop();

			ofs << timer.getTime(SECONDS) << " "
				<< timer.getTime(MILLISECONDS) << " "
				<< timer.getTime(MICROSECONDS) << "\n";
		}

		ofs.flush();
	}
	
}

