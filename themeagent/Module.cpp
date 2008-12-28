#include "Module.h"
#include <windows.h>
#include <algorithm>
#include <cctype>

Module::Module(const std::string path) {
	WIN32_FIND_DATA findData;
	if (FindFirstFile(path.c_str(), &findData) != INVALID_HANDLE_VALUE)
	{
		name = findData.cFileName;
	}
	else
	{
		name = path;
	}

	std::string s = name;

	transform (s.begin(), s.end(), s.begin(), tolower);

	if (s.substr(s.length() - 4) == ".dll")
	{
		name = name.substr(0, name.length() - 4);
	}
}

std::string Module::getName() const {
	return name;
}

bool Module::operator==(const Module &rhs) const {
	std::string s1 = name;
	std::string s2 = rhs.name;

	transform (s1.begin(), s1.end(), s1.begin(), tolower);
	transform (s2.begin(), s2.end(), s2.begin(), tolower);
	return s1 == s2;
}