#pragma once
#include <vector>
#include <fstream>
class FileLoader
{
public:
	FileLoader();
	static std::vector<uint8_t> Load(std::string fileName);
	~FileLoader();
};

