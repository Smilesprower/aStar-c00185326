#include "stdafx.h"
#include "Logger.h"

static string currentLog;
Logger * Logger::m_inst = nullptr;
static Logger * Instance();

Logger::Logger() :
	m_logging(false)
{
}

Logger::~Logger()
{
}

Logger * Logger::Instance()
{
	if (!m_inst)
	{
		m_inst = new Logger();
	}
	return m_inst;
}

void Logger::createLogContent(int numEnemies, bool thread, int totalGameTicks, int runsComplete, int totalTasks)
{
	std:string temp;
	if (numEnemies == 500)
		temp = "Large";
	else if (numEnemies == 50)
		temp = "Medium";
	else
		temp = "Small";

	currentLog += " Map Size,Number of Enemies,Threads Enabled,Total Game Ticks,Total Runs Complete, Total A* Paths Calculated\n";
	currentLog += temp
			   + "," + to_string(numEnemies)
			   + "," + to_string(thread)
			   + "," + to_string(totalGameTicks) 
			   + "," + to_string(runsComplete) 
			   + "," + to_string(totalTasks) + "\n";
}

//If I is pressed again create the log with the log stream 
void Logger::createLog()
{
	std::ofstream myfile;
	myfile.open(nameFile());
	myfile << currentLog;
	myfile.close();
	currentLog = "";
}

string Logger::nameFile()
{
	string filestamp;
	struct tm localtime;
	__time64_t long_time;
	char timestamp[80];
	_time64(&long_time);
	_localtime64_s(&localtime, &long_time);
	asctime_s(timestamp, 80, &localtime);
	filestamp = timestamp;
	//remove ":" which isn't a vaild file name
	filestamp.replace(13, 1, ".");
	filestamp.replace(16, 1, ".");
	string fileName = "log-" + filestamp;
	fileName.pop_back(); //get rid of \n
	return fileName += ".csv";
}
