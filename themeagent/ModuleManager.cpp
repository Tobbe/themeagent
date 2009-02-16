#include "ModuleManager.h"
#include <shlwapi.h>

using namespace std;

ModuleManager::ModuleManager(string modulesDir, vector<std::string> downloadSites)
{
	this->modulesDir = modulesDir;
	this->downloadSites = downloadSites;

	findModulesInModulesDir();
}

void ModuleManager::findModulesInModulesDir()
{
	string searchDir = modulesDir + "\\*";
	string searchFile;

	WIN32_FIND_DATA wfd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	HANDLE hFindFile = INVALID_HANDLE_VALUE;

	hFind = FindFirstFile(searchDir.c_str(), &wfd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		//Loop through all the files and folders in modulesDir
		while (FindNextFile(hFind, &wfd) != 0)
		{
			if (isDll(wfd))
			{
				modules.add(Module(wfd.cFileName));
			}
			else if (isDir(wfd))
			{
				WIN32_FIND_DATA wfd2;
				string searchString = modulesDir + "\\" + wfd.cFileName;
				searchString += "\\*.dll";
				if (FindFirstFile(searchString.c_str(), &wfd2) != INVALID_HANDLE_VALUE)
				{
					modules.add(Module(wfd.cFileName));
				}
			}
		}
	}
}

bool ModuleManager::isDll(const WIN32_FIND_DATA &wfd) const
{
	return (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) && 
		_stricmp(PathFindExtension(wfd.cFileName), ".dll") == 0;
}

bool ModuleManager::isDir(const WIN32_FIND_DATA &wfd) const
{
	return wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
		strcmp(wfd.cFileName, ".") != 0 &&
		strcmp(wfd.cFileName, "..") != 0;
}

ModuleList ModuleManager::getModuleList() const
{
	return modules;
}