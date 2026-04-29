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

void SaveLoadManager::LoadFromFile(std::string filePath)
{

}
