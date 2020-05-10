#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Arguments
{
	enum modes{compress = 1, decompress} mode;
	string inputFilename;
	string outputFilename;
	string prefix;
};

struct Data
{
	string str;
	map <char, vector<bool>> table;
	map <char, int> map;
};