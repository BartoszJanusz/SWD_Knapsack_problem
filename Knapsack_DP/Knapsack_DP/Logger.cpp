#include "Logger.h"

Logger Logger::logger;

const Logger & Logger::getLogger()
{
	if (!logger.logFile.is_open())
	{
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y_%I.%M.%S.log", &timeinfo);
		std::string str(buffer);
		logger.logFile.open(str, std::ofstream::out);
	}

	return logger;
}

void Logger::log(const std::string &text, std::pair<int, std::vector<int>> retVal) const
{
	std::stringstream ss;
	ss << text << ": kValue: " << retVal.first << " [";
	size_t i = 0;
	for (; i < retVal.second.size() - 1; i++)
		ss << retVal.second[i] << ", ";
	ss << retVal.second[i] << "]";
	this->log(ss);
}

void Logger::log(const std::string &text) const
{
	logFile << text << std::endl;
}

void Logger::log(const std::stringstream &ss) const
{
	this->log(ss.str());
}
