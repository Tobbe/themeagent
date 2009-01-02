#include "RCFile.h"
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>

using namespace std;

RCFile::RCFile(const std::string &path)
{
	ifstream fin(path.c_str());
	string line;

	lineCount = 0;
	lastValue = rc.end();

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
	str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun(&::isspace))).base(), str.end());

	return str;
}

string RCFile::getSetting(const string &line) const
{
	string setting = line.substr(0, distance(line.begin(), find_if(line.begin(), line.end(), isspace)));
	transform(setting.begin(), setting.end(), setting.begin(), tolower);
	return setting;
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

string RCFile::get(const string &key) const
{
	string k = key; //to get the right size for k so it can be used in the transform algorithm
	transform(key.begin(), key.end(), k.begin(), tolower);

	multimap<string, string>::const_iterator it = rc.find(k);

	if (it == rc.end())
	{
		return "";
	}
	else
	{
		return it->second;
	}
}

bool RCFile::isSet(const string &key) const
{
	string k = key; //to get the right size for k so it can be used in the transform algorithm
	transform(key.begin(), key.end(), k.begin(), tolower);

	multimap<string, string>::const_iterator it = rc.find(k);

	return it != rc.end();
}

string RCFile::getMultiple(const string &key)
{
	string k = key; //to get the right size for k so it can be used in the transform algorithm
	transform(key.begin(), key.end(), k.begin(), ::tolower);

	multimap<string, string>::const_iterator it = rc.end();

	if (lastValue != rc.end() && lastValue->first == k)
	{
		lastValue++;
		it = lastValue;
	}
	else
	{
		it = lastValue = rc.lower_bound(k);
	}

	if (it != rc.end() && it->first == k)
	{
		return it->second;
	}
	else
	{
		lastValue = rc.end();
		return "";
	}
}