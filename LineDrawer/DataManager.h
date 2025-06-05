#pragma once

#define MAX_LINES 100
#define MAX_STREAM_SIZE 4000

#include <list>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "Data.h"

class DataManager
{
	std::string file;
	std::string exportPath = "./exports";

	void loadData(const char* file, std::list<Line>& dest);
	void parseIntsToLines(int ints[], int size, std::list<Line>& dest);

public:

	std::list<Line> lines;

	std::vector<std::filesystem::directory_entry> getLineFiles();
	void listLineFiles();
	void setupSoftware();
	bool loadFile(const char* file);
	bool loadNewFile();
	bool saveData();
};

