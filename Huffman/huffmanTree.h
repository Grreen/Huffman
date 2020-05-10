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
	//map<char, string> table;
	vector<bool> code;
	//map <char, int> _map;
	//string _string;
	Data data;

	struct Compare
	{
		bool operator()(Node* left, Node* right) const
		{
			return left->getFrequency() < right->getFrequency();
		}
	};

	Arguments ArgumentsReading(int argc, char* argv[])
	{
		Arguments args;
		for (int i = 0; i < argc; i++)
		{
			if (string(argv[i]).find("decompress") != string::npos)
				args.mode = args.decompress;
			else if (string(argv[i]).find("compress") != string::npos)
				args.mode = args.compress;			
			else if (string(argv[i]).find("input_filename") != string::npos ||
					 string(argv[i]).find("inputFilename") != string::npos)
			{
				if (string(argv[i]).find("=") != string::npos)
					args.inputFilename = string(argv[i]).substr(string(argv[i]).find('=') + 1, string(argv[i]).length() - 1);
				else if (i < argc)
					args.inputFilename = argv[++i];
			}
			else if (string(argv[i]).find("output_filename") != string::npos ||
					 string(argv[i]).find("outputFilename") != string::npos)
			{
				if (string(argv[i]).find("=") != string::npos)
					args.outputFilename = string(argv[i]).substr(string(argv[i]).find('=') + 1, string(argv[i]).length() - 1);
				if (i < argc)
					args.outputFilename = argv[++i];
			}
			else if (string(argv[i]).find("prefix_phrase") != string::npos ||
					 string(argv[i]).find("prefixPhrase") != string::npos)
			{
				if (string(argv[i]).find("=") != string::npos)
					args.prefix = string(argv[i]).substr(string(argv[i]).find('=') + 1, string(argv[i]).length() - 1);
				if (i < argc)
					args.prefix = argv[++i];
			}
		}
		return args;
	}

public:

	huffmanTree(int argc, char *argv[])
	{
		Arguments args = ArgumentsReading(argc, argv);
		
		if (WorkWithFiles::FileReading(args, data))
		{
			list<Node*> tree;

			map<char, int>::iterator iter;
			for (iter = data.map.begin(); iter != data.map.end(); ++iter)
			{
				Node* temp = new Node();
				temp->setValue(iter->second, iter->first);
				tree.push_back(temp);
			}

			if (tree.size() == 0)
				return;

			while (tree.size() != 1)
			{
				tree.sort(Compare());

				Node* sonLeft = tree.front();
				tree.pop_front();
				Node* sonRight = tree.front();
				tree.pop_front();

				Node* parent = new Node(sonLeft, sonRight);
				tree.push_front(parent);
			}

			root = tree.front();
			buildTable(root);
			WorkWithFiles::SaveInFile(args, data);
			//WorkWithFiles::FileReading(args, data);
		}
	}

	Node* getRoot()
	{
		return root;
	}

	void buildTable(Node *root)
	{
		if (root->getLeftChild() != NULL)
		{
			code.push_back(0);
			buildTable(root->getLeftChild());
		}
		if (root->getRightChild() != NULL)
		{
			code.push_back(1);
			buildTable(root->getRightChild());
		}
		if (root->getLetter())
			data.table[root->getLetter()] = code;

		if (code.size() != 0)
			code.pop_back();
	}

	void print(Node *root,unsigned k = 0)
	{
		if (root != NULL)
		{
			print(root->getLeftChild(), k + 3);

			for (unsigned i = 0; i < k; i++)
				cout << "  ";

			if (root->getLetter())
				if (root->getLetter() == '\n')
					cout << root->getFrequency() << "(\\n)" << endl;
				else
					cout << root->getFrequency() << "(" << root->getLetter() << ")" << endl;
			else
				cout << root->getFrequency() << endl;
			print(root->getRightChild(), k + 3);
		}
	}

	void printTable()
	{
		for (map<char, vector<bool>>::iterator iter = data.table.begin(); iter != data.table.end(); ++iter)
		{
			if (iter->first == '\n')
				cout << "\\n" << " : ";
			else
				cout << iter->first << " : ";
			for (int i = 0; i < iter->second.size(); i++)
				cout << iter->second[i] ;
			cout << " (" << data.map[iter->first] << ")" << endl;;
		}

		for (int i = 0; i < data.str.length(); i++)
			for (int j = 0; j < data.table[data.str[i]].size(); j++)
				cout << data.table[data.str[i]][j];
	}
};

