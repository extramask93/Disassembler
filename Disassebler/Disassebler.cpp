// Disassebler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "FileLoader.h"
#include "Disassembler.h"
#include "avr.h"
int main(int argc, char* argv[])
{
	//FileLoader::Load("a.txt");
	std::vector<uint8_t> bytes_;
	bytes_.push_back(0x1C);
	bytes_.push_back(0x56);
	bytes_.push_back(0x0C);
	bytes_.push_back(0x78);
	Disassembler dis{&avr::DecodeInstructions};
	dis.Decode(bytes_);
	system("PAUSE");
    return 0;
}

