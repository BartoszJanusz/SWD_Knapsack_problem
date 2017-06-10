#include "Tester.h"

void Tester::test(const TestParameters& tp, bool parallel)
{
	// Generating data for tests
	std::vector<Data> data(tp.repeats * tp.knapsackSizes.size());
	for (size_t i = 0; i < tp.repeats; i++)
	{
		Data d;
		d.generateItems(tp.costRange, tp.valueRange, tp.itemsToGenerate);
		for (size_t j = 0; j < tp.knapsackSizes.size(); j++)
		{
			data[j * tp.repeats + i].setKnapsackSize(tp.knapsackSizes[j]);
			data[j * tp.repeats + i].setItems(d.getItems());
		}
	}

	if (parallel)
	{
		std::vector<std::thread> threads;
		threads.reserve(tp.solvers.size());

		// Creating and starting testing threads
		size_t i = 0;
		for (auto it = tp.solvers.begin(); it != tp.solvers.end(); i++, it++)
		{
			std::stringstream ss;
			ss << i;
			threads.emplace_back(performNTests, *it, data, tp.repeats, ss.str());
		}

		// Waiting for threads
		for (auto& t : threads)
		{
			t.join();
		}
	}
	else
	{
		size_t i = 0;
		for (auto it = tp.solvers.begin(); it != tp.solvers.end(); i++, it++)
		{
			std::stringstream ss;
			ss << i;
			performNTests(*it, data, tp.repeats, ss.str());
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
	ss << "results_" << className << "_" << knapsackSize << "-" << itemCount;
	if (!additionalInfo.empty())
		ss << "_" << additionalInfo;
	ss << ".txt";
	return ss.str();
}

void Tester::performNTests(SolverType solverType, const std::vector<Data> &data, uint repeats, const std::string additionalInfo)
{
	std::cout << additionalInfo << ": start" << std::endl;
	for (size_t i = 0; i < data.size(); i++)
	{
		auto percent = (i * 100 / data.size());
		if ((percent % 10) == 0)
		{
			std::cout << additionalInfo << ": " << percent << std::endl;
		}
		
		auto slv = SolverFactory::constructSolver(solverType, data[i]);
		std::unique_ptr<Solver> up(slv);
		// Constructing file name
		auto fileName = constructFileName(*slv, additionalInfo);
		
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

		ofs << "# seconds | milliseconds | microseconds | nanoseconds\n";
		for (decltype(repeats) j = 0; j < repeats; j++)
		{
			auto solver = SolverFactory::constructSolver(solverType, data[i]);
			timer.start();
			solver->solve();
			timer.stop();
			delete solver;

			ofs << timer.getTime(SECONDS) << " "
				<< timer.getTime(MILLISECONDS) << " "
				<< timer.getTime(MICROSECONDS) << " "
				<< timer.getTime(NANOSECONDS) << "\n";
		}
		ofs.flush();
	}
	std::cout << additionalInfo << ": finish" << std::endl;
}

