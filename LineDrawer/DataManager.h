#pragma once

#define MAX_LINES 100

#include <list>
#include <string>
#include <iostream>
#include <fstream>

struct Vec2
{
	float x, y;

	bool operator==(const Vec2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
};

struct Line
{
	Vec2 start, end;

	inline bool operator==(const Line& rhs) const
	{
		return start == rhs.start && end == rhs.end;
	}
};


class DataManager
{
	std::list<Line> lines;

public:
	
	const std::list<Line>& getLines()
	{
		return lines;
	}

	void addLine(Line line)
	{
		if (lines.size() < MAX_LINES)
			lines.push_back(line);
	}

	void removeLine(Line line)
	{
		lines.remove(line);
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

		return true;
	}
};

