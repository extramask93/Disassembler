#pragma once
#include <vector>
#include <fstream>
#define IND 16
using Elf32_Addr = uint32_t;
using Elf32_Half = uint16_t;
using Elf32_Off = uint32_t;
using Elf32_SWord = int32_t;
using Elf32_Word = uint32_t;

class FileLoader
{
	typedef struct {
		unsigned char e_ident[IND];
		Elf32_Half e_type;
		Elf32_Half e_machine;
		Elf32_Word e_version;
		Elf32_Addr e_entry;
		Elf32_Off e_phoff;
		Elf32_Off e_shoff;
		Elf32_Word e_flags;
		Elf32_Half e_ehsize;
		Elf32_Half e_phentsize;
		Elf32_Half e_phnum;
		Elf32_Half e_shentsize;
		Elf32_Half e_shnum;
		Elf32_Half e_shstrndx;
	} Elf32_Ehdr;
public:
	FileLoader();
	static std::vector<uint8_t> Load(std::string fileName);
	void ParseELF();
	void ParseELFHeader();
	~FileLoader();
private:
	std::vector<uint8_t> bytes;
	Elf32_Ehdr header;
};

