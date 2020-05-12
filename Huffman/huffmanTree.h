#pragma once
#include <map>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Node.h"
#include "Structs.h"
#include "WorkWithFiles.h"

using namespace std;

class huffmanTree
{
	Node* root;
	vector<bool> code;
	Data data;

	struct Compare
	{
		bool operator()(Node* left, Node* right) const
		{
			return left->getFrequency() < right->getFrequency();
		}
	};
	Arguments ArgumentsReading(int argc, char* argv[]);

public:
	huffmanTree(int argc, char* argv[]);
	Node* getRoot();
	void buildTable(Node* root);
	void print(Node* root, unsigned k = 0);
	void printTable();
};

