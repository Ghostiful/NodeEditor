#include "SaveLoadManager.h"

SaveLoadManager::SaveLoadManager()
{
}

SaveLoadManager::~SaveLoadManager()
{
}

void SaveLoadManager::SaveToFile(std::string filePath, NodeSaveData data)
{
	std::ofstream f;
	f.open(filePath);
	for (int i = 0; i < data.size(); i++)
	{
		f << data[i] << '\n';
	}
	f.close();
}

NodeSaveData SaveLoadManager::LoadFromFile(std::string filePath)
{
	NodeSaveData data;
	std::ifstream f;
	f.open(filePath);
	if (!f.is_open())
		return data;

	std::string temp;
	do 
	{
		std::getline(f, temp);
		if (temp == "")
			break;
		data.push_back(temp);
	} while (!f.eof());

	f.close();
	return data;
}
