#include "RCFile.h"
#include <fstream>
#include <algorithm>

using namespace std;

RCFile::RCFile(const std::string &path)
{
	ifstream fin(path.c_str());
	string line;

	lineCount = 0;

	if (fin.is_open())
	{
		while (!fin.eof() )
		{
			getline(fin, line);
			line = trim(line);
			if (line.length() > 0)
			{
				++lineCount;
				rc.insert(pair<string, string>(getSetting(line), getValue(line)));
			}
		}
		fin.close();
	}
}

string RCFile::trim(string str) const
{
	str.erase(str.begin(), find_if(str.begin(), str.end(), not1(ptr_fun(&::isspace))));
	str.erase(str.rbegin().base(), find_if(str.rbegin(), str.rend(), not1(ptr_fun(&::isspace))).base());

	return str;
}

string RCFile::getSetting(const string &line) const
{
	return line.substr(0, distance(line.begin(), find_if(line.begin(), line.end(), isspace)));
}

string RCFile::getValue(const string &line) const
{
	int index = distance(line.begin(), find_if(line.begin(), line.end(), ptr_fun(&isspace)));
	return trim(line.substr(index));
}

int RCFile::lines() const
{
	return lineCount;
}