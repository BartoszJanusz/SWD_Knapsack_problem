#pragma once
#include "Solver.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include "TestParameters.h"

class Tester
{

public:
	Tester() = delete;
	~Tester() = default;
	static void test(const TestParameters& tp, bool parallel = true);
	static void testCorrectness(const TestParameters& tp);

private:
	static void performNTests(SolverType solverType, const std::vector<Data> &data, uint repeats, const std::string additionalInfo);
	static void performCorectnessTest(const std::set<SolverType> &solverTypes, const std::vector<Data>& data, const std::string additionalInfo = "");
	static std::string constructFileName(const Solver& solver, const std::string additionalInfo);
};

