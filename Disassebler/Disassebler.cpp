// Disassebler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "FileLoader.h"
int main(int argc, char* argv[])
{
	FileLoader::Load("a.txt");
	system("PAUSE");
    return 0;
}

