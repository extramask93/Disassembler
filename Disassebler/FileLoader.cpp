#include "FileLoader.h"
#include <assert.h>

FileLoader::FileLoader()
{
}

std::vector<uint8_t> FileLoader::Load(std::string fileName)
{
	std::ifstream file{};
	file.open(fileName, std::ifstream::binary);
	file.seekg(0, std::ios::end);
	auto fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<uint8_t> bytes(fileSize);
	file.read(reinterpret_cast<char*>(&bytes[0]), fileSize);
	return bytes;
}

void FileLoader::ParseELF()
{

}


void FileLoader::ParseELFHeader()
{
	assert(bytes.size() >= sizeof(Elf32_Ehdr));
	std::copy(bytes.begin(),bytes.end(),reinterpret_cast<uint8_t*>(&header));
}

FileLoader::~FileLoader()
{
}
