#include "DataManager.h"

void DataManager::setupSoftware()
{
	if (std::filesystem::create_directory(exportPath))
		std::cout << "Generated directory: " << exportPath << std::endl;
}

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

	format = format.substr(format.find_last_of('.') + 1, format.length());
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


bool DataManager::loadFile(const char* file)
{
	lines.clear();
	std::ifstream iS(file);
	this->file = std::filesystem::path(file).filename().string().c_str();

	if (iS.is_open())
	{
		std::cout << "Found file " << file << ". loading data..." << std::endl;	
		loadData(file, lines);
	}
	else
	{
		std::cout << "No file " << file << " exists. Operating on new data" << std::endl;
		return false;
	}
	iS.close();

	return true;
}

bool DataManager::loadNewFile()
{
	std::string newName = "file.csv";

	// Get non-existing number for file name
	if (std::filesystem::directory_entry(exportPath + "/file.csv").exists())
	{
		int number = 1;
		while (std::filesystem::directory_entry(exportPath + "/lineFile(" + std::to_string(number) + ").csv").exists())
			number++;

		newName = "lineFile(" + std::to_string(number) + ").csv";
	}

	lines.clear();
	file = newName;

	return true;
}

void DataManager::listLineFiles()
{
	if (!std::filesystem::exists(std::filesystem::path(exportPath)))
	{
		std::cout << "No directory " << exportPath << " for exported files" << std::endl;
		return;
	}

	std::filesystem::directory_iterator exportDir(exportPath);
	std::cout << "Listing files:\n" << std::endl;
	
	std::string path;
	for (auto file : exportDir)
	{
		path = file.path().string();
		// Skip non-csv files
		if (path.find(".csv") == std::string::npos) continue;
		std::cout << path << std::endl;
	}
}

bool DataManager::saveData()
{
	std::string data;
	std::string finalPath = exportPath + "/" + file;
	std::ofstream oS;
	oS.open(finalPath);

	if (!oS.is_open())
	{
		std::cout << "Failed to open save file!" << std::endl;
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
	std::cout << "Saved data to " << finalPath << std::endl;

	return true;
}

std::vector<std::filesystem::directory_entry> DataManager::getLineFiles()
{
	if (!std::filesystem::exists(exportPath)) return {};

	std::vector<std::filesystem::directory_entry> paths;
	
	for (auto path : std::filesystem::directory_iterator(exportPath))
		paths.push_back(path);

	return paths;
}