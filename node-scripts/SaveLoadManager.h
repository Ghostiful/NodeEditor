#pragma once

#include <stdio.h>
#include <string>
#include <fstream>

class SaveLoadManager
{
public:
	// Constructors
	SaveLoadManager();

	~SaveLoadManager();

	void SaveToFile(std::string filePath);

	void LoadFromFile(std::string filePath);
};

