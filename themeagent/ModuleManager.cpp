#include "ModuleManager.h"
#include <shlwapi.h>
#include <string>
#include <vector>
#include "unzip.h"

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

bool ModuleManager::installModule(const string &moduleName)
{
	if (modules.contains(moduleName))
	{
		return true;
	}

	if (!downloadModule(moduleName))
	{
		return false;
	}

	if (!unzipModule(moduleName))
	{
		return false;
	}

	return true;
}

bool ModuleManager::downloadModule(const string &moduleName)
{
	string path = modulesDir + "\\archive\\" + moduleName + ".zip";

	if (fileExists(path))
	{
		return true;
	}

	string url = downloadSites[0] + "\\" + moduleName + ".zip";

	fileDownloader.downloadFile(url, path);

	if (!fileExists(path))
	{
		return false;
	}

	return true;
}

bool ModuleManager::fileExists(const string &path) const
{
	return (GetFileAttributes(path.c_str()) != INVALID_FILE_ATTRIBUTES);
}

bool ModuleManager::unzipModule(const string &moduleName) const
{
	string path = modulesDir + "\\archive\\" + moduleName + ".zip";

	if (!fileExists(path))
	{
		return false;
	}

	// find_last_of returns string::npos if nothing is found, so this works
	// even if the module doesn't have a version
	string moduleBaseName = moduleName.substr(0, moduleName.find_last_of("-"));

	string docsDir = modulesDir + "\\docs";
	string moduleTxt = moduleBaseName + ".txt";
	string moduleChm = moduleBaseName + ".chm";

	vector<pair<int, string>> dllFiles;
	vector<pair<int, string>> imgFiles;
	vector<pair<int, string>> htmlFiles;
	vector<pair<int, string>> cssFiles;
	vector<pair<int, string>> rcFiles;
	vector<pair<int, string>> docsFiles;
	pair<int, string> helpFile;

	ZIPENTRY ze;
	HZIP hz = OpenZip(path.c_str(), NULL);
	GetZipItem(hz, -1, &ze); // -1 gives overall information about the zipfile

	int numitems = ze.index;

	for (int zi = 0; zi < numitems; zi++)
	{
		// Fetch individual details e.g. the item's name
		GetZipItem(hz, zi, &ze);

		if (_stricmp(PathFindExtension(ze.name), ".dll") == 0)
		{
			dllFiles.push_back(make_pair(zi, string(ze.name)));
		}
		else if (strlen(ze.name) >= 6 &&
			_stricmp(string(ze.name).substr(0, 5).c_str(), "docs/") == 0)
		{
			docsFiles.push_back(make_pair(zi, string(ze.name).substr(5)));
		}
		else if (_stricmp(PathFindExtension(ze.name), ".png") == 0 ||
			_stricmp(PathFindExtension(ze.name), ".jpg") == 0 ||
			_stricmp(PathFindExtension(ze.name), ".gif") == 0)
		{
			imgFiles.push_back(make_pair(zi, string(ze.name)));
		}
		else if (_stricmp(PathFindExtension(ze.name), ".htm") == 0 ||
			_stricmp(PathFindExtension(ze.name), ".html") == 0)
		{
			htmlFiles.push_back(make_pair(zi, string(ze.name)));
		}
		else if (_stricmp(PathFindExtension(ze.name), ".css") == 0)
		{
			cssFiles.push_back(make_pair(zi, string(ze.name)));
		}
		else if (_stricmp(PathFindExtension(ze.name), ".rc") == 0)
		{
			rcFiles.push_back(make_pair(zi, string(ze.name)));
		}
		else if (_stricmp(ze.name, "readme.txt") == 0 ||
			_stricmp(ze.name, "readme.chm") == 0 ||
			_stricmp(ze.name, moduleTxt.c_str()) == 0 ||
			_stricmp(ze.name, moduleChm.c_str()) == 0)
		{
			helpFile.first = zi;
			helpFile.second = ze.name;
		}
	}

	if (dllFiles.size() == 0)
	{
		return false;
	}
	else if (dllFiles.size() == 1)
	{
		SetUnzipBaseDir(hz, modulesDir.c_str());

		string moduleNameExt = moduleName + ".dll";
		UnzipItem(hz, dllFiles[0].first, moduleNameExt.c_str());
	}
	else
	{
		string path = modulesDir + "\\" + moduleName;
		if (CreateDirectory(path.c_str(), NULL) == FALSE)
		{
			return false;
		}

		SetUnzipBaseDir(hz, path.c_str());

		for (size_t i = 0; i < dllFiles.size(); ++i)
		{
			UnzipItem(hz, dllFiles[i].first, dllFiles[i].second.c_str());
		}
	}

	if (helpFile.second.size() > 0 && rcFiles.size() == 0)
	{
		string helpFileName = moduleName + PathFindExtension(helpFile.second.c_str());
		SetUnzipBaseDir(hz, docsDir.c_str());
		UnzipItem(hz, helpFile.first, helpFileName.c_str());
	}
	else if (docsFiles.size() > 0)
	{
		docsDir += "\\" + moduleName;
		if (CreateDirectory(docsDir.c_str(), NULL))
		{
			SetUnzipBaseDir(hz, docsDir.c_str());

			for (size_t i = 0; i < docsFiles.size(); ++i)
			{
				UnzipItem(hz, docsFiles[i].first, docsFiles[i].second.c_str());
			}
		}
	}
	else if (htmlFiles.size() == 1 && imgFiles.size() == 0 &&
		cssFiles.size() == 0 && rcFiles.size() == 0)
	{
		string helpFileName = moduleName + ".html";
		SetUnzipBaseDir(hz, docsDir.c_str());
		UnzipItem(hz, helpFile.first, helpFileName.c_str());
	}
	else if (htmlFiles.size() > 1)
	{
		docsDir += "\\" + moduleName;
		if (CreateDirectory(docsDir.c_str(), NULL))
		{
			SetUnzipBaseDir(hz, docsDir.c_str());

			for (size_t i = 0; i < htmlFiles.size(); ++i)
			{
				UnzipItem(hz, htmlFiles[i].first, htmlFiles[i].second.c_str());
			}

			for (size_t i = 0; i < imgFiles.size(); ++i)
			{
				UnzipItem(hz, imgFiles[i].first, imgFiles[i].second.c_str());
			}

			for (size_t i = 0; i < cssFiles.size(); ++i)
			{
				UnzipItem(hz, cssFiles[i].first, cssFiles[i].second.c_str());
			}

			for (size_t i = 0; i < rcFiles.size(); ++i)
			{
				UnzipItem(hz, rcFiles[i].first, rcFiles[i].second.c_str());
			}
		}
	}
	else
	{
		docsDir += "\\" + moduleName;
		if (CreateDirectory(docsDir.c_str(), NULL))
		{
			SetUnzipBaseDir(hz, docsDir.c_str());

			for (size_t i = 0; i < rcFiles.size(); ++i)
			{
				UnzipItem(hz, rcFiles[i].first, rcFiles[i].second.c_str());
			}

			for (size_t i = 0; i < imgFiles.size(); ++i)
			{
				UnzipItem(hz, imgFiles[i].first, imgFiles[i].second.c_str());
			}

			if (helpFile.second.size() > 0)
			{
				UnzipItem(hz, helpFile.first, helpFile.second.c_str());
			}
		}
	}

	CloseZip(hz);

	return true;
}