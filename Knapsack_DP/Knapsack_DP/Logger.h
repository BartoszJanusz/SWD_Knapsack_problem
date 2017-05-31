#pragma once
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>

class Logger
{
public:
	static const Logger& getLogger();
	void log(const std::string &text) const;
	void log(const std::string &text, std::pair<int, std::vector<int>> retVal) const;
	void log(const std::stringstream &ss) const;
private:
	Logger() = default;
	~Logger() = default;

	static Logger logger;
	mutable std::ofstream logFile;
};

