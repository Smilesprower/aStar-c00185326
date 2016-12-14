#pragma once
#include <iostream>
#include <string>
#include <ctime> 
#include <fstream>

using namespace std;

extern bool Logging;
class Logger
{

public:
	static Logger * Instance();
	static void createLog();
	static void createLogContent(int numEnemies, bool thread, int totalGameTicks, int runsComplete, int totalTasks);
	static string nameFile();
	bool m_logging;
private:
	static Logger *m_inst;
	Logger();
	~Logger();
};
