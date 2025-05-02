#pragma once

#define MAX_LINES 100

#include <list>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>

#include "Data.h"

class DataManager
{
	std::stack<std::list<Line>> fStack, bStack;
	std::list<Line> lines;

public:
	
	const std::list<Line>& getLines()
	{
		return lines;
	}

	void saveState()
	{
		fStack.push(lines);
	}

	void addLine(Line line)
	{
		if (lines.size() == MAX_LINES) return;
		lines.push_back(line);
		saveState();
	}

	void removeLine(Line line)
	{
		lines.remove(line);
		saveState();
	}

	void undo()
	{
		if (fStack.size() == 0) return;
		bStack.push(fStack.top());
		fStack.pop();

		if (fStack.size() > 0) lines = fStack.top();
		else lines = {};
	}

	void redo()
	{
		if (bStack.size() == 0) return;
		fStack.push(bStack.top());
		bStack.pop();

		if (fStack.size() > 0) lines = fStack.top();
		else lines = {};
	}

	bool saveData()
	{
		std::string data;
		std::ofstream oS;
		oS.open("./lines.csv");
		
		if (!oS.is_open())
		{
			std::cout << "Failed to save data!" << std::endl;
			return false;
		}

		for (Line& l : lines)
		{
			
			data = std::to_string((int)l.start.x) + "," + 
					std::to_string((int)l.start.y) + "," + 
					std::to_string((int)l.end.x) + "," + 
					std::to_string((int)l.end.y) + ",";
			// Delete extra ','
			if (l == lines.back()) data.erase(data.size() - 1);

			oS << data.c_str();
		}
		oS.close();
		std::cout << "Saved data to lines.csv" << std::endl;

		return true;
	}
};

