#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>

#include "Structs.h"

using namespace std;

static class WorkWithFiles
{
	static bool ReadStandartFile(string filename, Data& data);
	static bool ReadBinaryFile(Arguments args, Data& data);
	static bool StandartSaveInFile(string filename, string strSave);
	static bool BinarySaveInFile(Arguments args, Data& data);
public:
	static bool FileReading(Arguments args, Data& data);
	static bool SaveInFile(Arguments args, Data& data);
};

