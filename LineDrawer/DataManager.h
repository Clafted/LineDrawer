#pragma once

#define MAX_LINES 100
#define MAX_STREAM_SIZE 4000

#include <list>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>

#include "Data.h"
#include "Action.h"

class DataManager
{
	std::string file;
	
	void parseIntsToLines(int ints[], int size, std::list<Line>& dest);
	void loadData(const char* file, std::list<Line>& dest);

public:

	std::list<Line> loadFile(const char* file);

	bool saveData(std::list<Line> lines);
};

