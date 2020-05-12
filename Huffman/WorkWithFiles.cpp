#include "WorkWithFiles.h"

bool WorkWithFiles::ReadStandartFile(string filename, Data& data)
{
	ifstream file(filename);
	if (file.is_open())
	{
		string str;
		while (getline(file, str))
		{
			data.str += str + '\n';
			for (int i = 0; i < str.length(); i++)
				data.map[str[i]]++;
			data.map['\n']++;
		}
	}
	else
	{
		cout << "File opening error." << endl;
		return false;
	}

	file.close();
	return true;
}

bool WorkWithFiles::ReadBinaryFile(Arguments args, Data& data)
{
	ifstream in(args.inputFilename, ios::binary | ios::in);
	string prefix;

	if (!in.fail())
	{
		string str;
		map<vector<bool>, char> reverseTable;
		vector<bool> code;
		int numEl = 1;
		int sizeTable;
		int sizeText;
		int tempInt = 0;
		char c;

		while (!in.eof())
		{
			in.get(c);

			if (c != ' ' && numEl < 4)
				str += c;
			else
			{
				if (numEl == 1)
				{
					prefix = str;
					str.clear();
					numEl++;
					if (prefix != args.prefix)
					{
						cout << "The discrepancy between the prefixes" << endl;
						return false;
					}
				}
				else if (numEl == 2)
				{
					sizeTable = atoi(str.c_str());
					str.clear();
					numEl++;
				}
				else if (numEl == 3)
				{
					sizeText = atoi(str.c_str());
					str.clear();
					numEl++;
				}
				else if (numEl == 4)
				{
					int num = 0;
					char temp = c;
					string tem;
					while (num < sizeTable)
					{
						in.get(c);
						if (c == '1' || c == '0')
							tem += c;
						else
						{
							num++;
							vector<bool> code;
							for (int i = 0; i < tem.length(); i++)
								(tem[i] == '1') ? (code.push_back(1)) : (code.push_back(0));
							data.table.emplace(temp, code);
							temp = c;
							tem.clear();
						}
					}
					numEl++;
					for (map<char, vector<bool>>::iterator iter = data.table.begin(); iter != data.table.end(); iter++)
						reverseTable.emplace(iter->second, iter->first);
				}
				else
				{
					for (int num = 0; num <= 7; num++)
					{
						if (c & (1 << (7 - num)))
							code.push_back(1);
						else
							code.push_back(0);

						if (reverseTable.count(code) > 0 && tempInt < sizeText - 1)
						{
							tempInt++;
							str += reverseTable[code];
							code.clear();
						}
					}
				}
			}
		}
		StandartSaveInFile(args.outputFilename, str);
	}
	else cout << "File not found" << endl;
	in.close();
	return false;
}

bool WorkWithFiles::StandartSaveInFile(string filename, string strSave)
{
	ofstream out(filename);
	if (out.is_open())
	{
		out << strSave;
		out.close();
		return true;
	}
	return false;
}

bool WorkWithFiles::BinarySaveInFile(Arguments args, Data& data)
{
	ofstream out(args.outputFilename, ios::binary | ios::out);
	char space = ' ';

	out << args.prefix << space;

	out << data.table.size() << space;
	out << data.str.length() << space;

	for (map<char, vector<bool>>::iterator iter = data.table.begin(); iter != data.table.end(); iter++)
	{
		out << iter->first;
		for (int i = 0; i < iter->second.size(); i++)
			out << iter->second[i];
	}
	out << space;


	char buf = 0;
	int count = 0;
	for (int i = 0; i < data.str.length(); i++)
		for (int j = 0; j < data.table[data.str[i]].size(); j++)
		{
			buf = buf | data.table[data.str[i]][j] << (7 - count);
			count++;
			if (count == 8)
			{
				out << buf;
				count = buf = 0;
			}
		}
	out.close();
	return true;
}

bool WorkWithFiles::FileReading(Arguments args, Data& data)
{
	if (args.mode == args.compress)
		return ReadStandartFile(args.inputFilename, data);
	if (args.mode == args.decompress)
		return ReadBinaryFile(args, data);
}

bool WorkWithFiles::SaveInFile(Arguments args, Data& data)
{
	if (args.mode == args.compress)
		return BinarySaveInFile(args, data);
	else if (args.mode == args.decompress)
		return StandartSaveInFile(args.outputFilename, data.str);
}
