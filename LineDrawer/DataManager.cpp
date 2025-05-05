#include "DataManager.h"

void DataManager::parseIntsToLines(int ints[], int size, std::list<Line>& dest)
{
	dest.clear();

	Line l;
	for (int i = 0; i + 3 < size; i += 4)
	{
		l.start.x = ints[i];
		l.start.y = ints[i + 1];
		l.end.x = ints[i + 2];
		l.end.y = ints[i + 3];

		dest.push_back(l);
	}
}

void DataManager::loadData(const char* file, std::list<Line>& dest)
{
	std::ifstream iS(file);
	std::string format = file;
	std::vector<int> loadedInts;

	if (!iS.is_open())
	{
		std::cout << "Failed to load data from file " << file << std::endl;
		return;
	}

	format = format.substr(format.find('.') + 1, format.length());
	std::cout << "Format: " << format << std::endl;

	if (format == "csv")
	{
		std::string val = "";
		char data[MAX_STREAM_SIZE];

		iS.getline(data, MAX_STREAM_SIZE);

		for (int i = 0; i < MAX_STREAM_SIZE; i++)
		{
			if (data[i] == ',' || data[i] == '\0')
			{
				loadedInts.push_back(std::stoi(val));
				val = "";
				if (data[i] == '\0') break;
			}
			else val += data[i];
		}
	}

	parseIntsToLines(loadedInts.data(), loadedInts.size(), dest);
}


std::list<Line> DataManager::loadFile(const char* file)
{
	std::ifstream iS(file);
	std::list<Line> lines;
	this->file = file;

	if (iS.is_open())
	{
		std::cout << "Found file " << file << ". loading data..." << std::endl;
		loadData(file, lines);
	}
	else
	{
		std::cout << "No file " << file << " exists. Operating on new data" << std::endl;
	}

	return lines;
}

bool DataManager::saveData(std::list<Line> lines)
{
	std::string data;
	std::ofstream oS;
	oS.open(file);

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
		if (l == lines.back()) data.erase(data.end() - 1); // Delete extra ','
		oS << data.c_str();
	}
	oS.close();
	std::cout << "Saved data to lines.csv" << std::endl;

	return true;
}