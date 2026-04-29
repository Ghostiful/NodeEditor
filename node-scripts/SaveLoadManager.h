#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include "NodeManager.h"

const std::string DEFAULT_FILEPATH = "graph-save.txt";

class SaveLoadManager
{
public:
	// Constructors
	SaveLoadManager();

	~SaveLoadManager();

	void SaveToFile(std::string filePath, NodeSaveData data);

	void LoadFromFile(std::string filePath);
};

