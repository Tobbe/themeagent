#include "RCFile.h"
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>

using namespace std;

RCFile::RCFile(const string &path)
{
	readFile(path);
	lastValue = rc.end();
}

RCFile::RCFile(const RCFile &rhs)
{
	rc = rhs.rc;
	lineCount = rhs.lineCount;
	if (rhs.lastValue == rhs.rc.end())
	{
		lastValue = rc.end();
	}
	else
	{
		multimap<string, string>::const_iterator tmpit = rc.lower_bound(rhs.lastValue->first);
		while (tmpit->second != rhs.lastValue->second)
		{
			++tmpit;
		}
		lastValue = tmpit;
	}
}

void RCFile::readFile(const string &path)
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
			if (line.length() > 0 && line[0] != ';')
			{
				++lineCount;
				readLine(line, path);
			}
		}
		fin.close();
	}
}

void RCFile::readLine(const string &line, const string &path)
{
	string setting = getSetting(line);
	string value = getValue(line);

	if (setting == "include")
	{
		if (GetFileAttributes(value.c_str()) != INVALID_FILE_ATTRIBUTES)
		{
			readFile(value);
		}
		else
		{
			string relPath = path;
			relPath = relPath.substr(0, relPath.find_last_of("\\/"));
			readFile(relPath + value);
		}
	}
	else if (!(setting == "if" || setting == "else" ||
		setting == "elseif" || setting == "endif"))
	{
		rc.insert(pair<string, string>(setting, value));
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
	string setting = line.substr(0, distance(line.begin(), find_if(line.begin(), line.end(), ::isspace)));
	transform(setting.begin(), setting.end(), setting.begin(), tolower);
	return setting;
}

string RCFile::getValue(const string &line) const
{
	string val = trim(line);
	string::iterator whitespace = find_if(val.begin(), val.end(), ::isspace);
	string::iterator valueBegin = find_if(whitespace, val.end(), not1(ptr_fun(&::isspace)));
	unsigned int indexEnd = string::npos;
	unsigned int indexBegin = distance(val.begin(), valueBegin);

	if (val[indexBegin] == '"' && indexBegin < val.length() - 1)
	{
		indexBegin++;
		indexEnd = val.find_first_of('"', indexBegin);
	}
	else if (val[indexBegin] == '\'' && indexBegin < val.length() - 1)
	{
		indexBegin++;
		indexEnd = val.find_first_of('\'', indexBegin);
	}
	else
	{
		indexEnd = distance(val.begin(), find_if(valueBegin, val.end(), ::isspace));
	}

	val = val.substr(indexBegin, indexEnd - indexBegin);

	if (val[0] == ';')
	{
		val = "";
	}

	val = parseForEvars(val);

	return val;
}

string RCFile::parseForEvars(string line) const
{
	ostringstream oss;
	ostringstream buffer;
	bool evar = false;

	for (size_t i = 0; i < line.length(); ++i)
	{
		if (!evar && line[i] != '$')
		{
			oss << line[i];
		}
		else if (line[i] != '$')
		{
			buffer << line[i];
		}
		else if (line[i] == '$')
		{
			if (evar)
			{
				// found end of evar
				oss << get(trim(buffer.str()));
				evar = false;
				buffer.clear();
				buffer.str("");
			}
			else
			{
				evar = true;
			}
		}
	}

	if (evar)
	{
		oss << buffer.str();
	}

	return oss.str();
}

int RCFile::lines() const
{
	return lineCount;
}

string RCFile::get(const string &key) const
{
	string k = key; //to get the right size for k so it can be used in the transform algorithm
	transform(key.begin(), key.end(), k.begin(), ::tolower);

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

bool RCFile::isTrue(const std::string &key) const
{
	if (!isSet(key))
	{
		return false;
	}

	string value = get(key);
	transform(value.begin(), value.end(), value.begin(), ::tolower);

	return value == "" || value == "true" || value == "on" || value == "yes";
}

RCFile &RCFile::operator=(const RCFile &rhs)
{
	rc = rhs.rc;
	lineCount = rhs.lineCount;
	if (rhs.lastValue == rhs.rc.end())
	{
		lastValue = rc.end();
	}
	else
	{
		multimap<string, string>::const_iterator tmpit = rc.lower_bound(rhs.lastValue->first);
		while (tmpit->second != rhs.lastValue->second)
		{
			++tmpit;
		}
		lastValue = tmpit;
	}

	return *this;
}