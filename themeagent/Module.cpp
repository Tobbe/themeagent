#include "Module.h"
#include <windows.h>
#include <algorithm>
#include <cctype>

using namespace std;

Module::Module(const string path)
{
	WIN32_FIND_DATA findData;
	if (FindFirstFile(path.c_str(), &findData) != INVALID_HANDLE_VALUE)
	{
		name = findData.cFileName;
	}
	else
	{
		name = path;
	}

	string s = name;

	transform (s.begin(), s.end(), s.begin(), tolower);

	if (s.substr(s.length() - 4) == ".dll")
	{
		name = name.substr(0, name.length() - 4);
	}

	int index = name.find_last_of('\\');

	if (index != string::npos)
	{
		name = name.substr(index + 1);
	}
}

string Module::getName() const
{
	return name;
}

bool Module::operator==(const Module &rhs) const
{
	string s1 = name;
	string s2 = rhs.name;

	transform(s1.begin(), s1.end(), s1.begin(), tolower);
	transform(s2.begin(), s2.end(), s2.begin(), tolower);
	return s1 == s2;
}

bool Module::operator<(const Module &rhs) const
{
	string s1 = name;
	string s2 = rhs.name;

	transform(s1.begin(), s1.end(), s1.begin(), tolower);
	transform(s2.begin(), s2.end(), s2.begin(), tolower);
	return s1 < s2;
}
