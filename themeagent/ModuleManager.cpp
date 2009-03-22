#include "ModuleManager.h"
#include <shlwapi.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "unzip.h"

using namespace std;

ModuleManager::ModuleManager(const string &modulesDir, const string &nlmIni,
	const vector<string> &downloadSites)
{
	this->modulesDir = modulesDir;
	this->nlmIni = nlmIni;
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

bool ModuleManager::installModule(const Module &module)
{
	return installModule(module.getName());
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

	if (!updateNLMList(moduleName))
	{
		return false;
	}

	modules.add(Module(moduleName));

	return true;
}

bool ModuleManager::downloadModule(const string &moduleName)
{
	string path = modulesDir + "\\archive\\" + moduleName + ".zip";

	if (fileExists(path))
	{
		return true;
	}

	if (downloadSites.size() < 1)
	{
		return false;
	}

	string url = downloadSites[0] + moduleName + ".zip";

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

	vector<pair<int, string>> dllFiles;
	vector<pair<int, string>> docsFiles;

	fillUnzipVectors(moduleName, path, dllFiles, docsFiles);
	
	if (!extractDlls(moduleName, path, dllFiles))
	{
		return false;
	}

	extractDocs(moduleName, path, docsFiles);

	return true;
}

void ModuleManager::fillUnzipVectors(const string &moduleName,
	const string &path, vector<pair<int, string>> &dllFiles,
	vector<pair<int, string>> &docsFiles) const
{
	// find_last_of returns string::npos if nothing is found, so this works
	// even if the module doesn't have a version
	string moduleBaseName = moduleName.substr(0, moduleName.find_last_of("-"));

	string moduleTxt = moduleBaseName + ".txt";
	string moduleChm = moduleBaseName + ".chm";

	ZIPENTRY ze;
	HZIP hz = OpenZip(path.c_str(), NULL);
	GetZipItem(hz, -1, &ze); // -1 gives overall information about the zipfile

	int numitems = ze.index;
	string fileName;

	for (int zi = 0; zi < numitems; zi++)
	{
		// Fetch individual details e.g. the item's name
		GetZipItem(hz, zi, &ze);
		fileName = ze.name;
		transform(fileName.begin(), fileName.end(), fileName.begin(), tolower);

		string ext = PathFindExtension(fileName.c_str());

		if (ext == ".dll")
		{
			dllFiles.push_back(make_pair(zi, string(ze.name)));
		}
		else if (strlen(ze.name) >= 6 && (fileName.substr(0, 5) == "docs/"))
		{
			docsFiles.push_back(make_pair(zi, string(ze.name).substr(5)));
		}
		else if (ext == ".png" ||
			ext == ".jpg" ||
			ext == ".gif" ||
			ext == ".htm" ||
			ext == ".html" ||
			ext == ".css" ||
			ext == ".rc" ||
			ext == ".chm" ||
			fileName.find("readme") != string::npos ||
			fileName.find("history") != string::npos ||
			fileName.find("changelog") != string::npos ||
			_stricmp(ze.name, moduleTxt.c_str()) == 0 ||
			_stricmp(ze.name, moduleChm.c_str()) == 0)
		{
			docsFiles.push_back(make_pair(zi, ze.name));
		}
	}

	CloseZip(hz);
}

bool ModuleManager::extractDlls(const string &moduleName, const string &path,
	const vector<pair<int, string>> &dllFiles) const
{
	ZIPENTRY ze;
	HZIP hz = OpenZip(path.c_str(), NULL);
	GetZipItem(hz, -1, &ze); // -1 gives overall information about the zipfile

	int numitems = ze.index;

	if (dllFiles.size() == 0)
	{
		CloseZip(hz);

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
			CloseZip(hz);

			return false;
		}

		SetUnzipBaseDir(hz, path.c_str());

		for (size_t i = 0; i < dllFiles.size(); ++i)
		{
			UnzipItem(hz, dllFiles[i].first, dllFiles[i].second.c_str());
		}
	}

	CloseZip(hz);

	return true;
}

void ModuleManager::extractDocs(const string &moduleName, const string &path,
	const vector<pair<int, string>> &docsFiles) const
{
	string docsDir = modulesDir + "\\docs";

	ZIPENTRY ze;
	HZIP hz = OpenZip(path.c_str(), NULL);
	GetZipItem(hz, -1, &ze); // -1 gives overall information about the zipfile

	int numitems = ze.index;

	if (docsFiles.size() == 1)
	{
		string helpFileName = moduleName + PathFindExtension(docsFiles[0].second.c_str());
		SetUnzipBaseDir(hz, docsDir.c_str());
		UnzipItem(hz, docsFiles[0].first, helpFileName.c_str());
	}
	else if (docsFiles.size() > 1)
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

	CloseZip(hz);
}

bool ModuleManager::updateNLMList(const string &moduleName) const
{
	string moduleDir = modulesDir + "\\" + moduleName;

	if (GetFileAttributes(moduleDir.c_str()) == INVALID_FILE_ATTRIBUTES)
	{
		// No separate directory exists for this module, so no special
		// handling is needed for NLM to be able to load the module
		return true;
	}

	ofstream ofs(nlmIni.c_str(), ios_base::out | ios_base::app);

	if (!ofs)
	{
		return false;
	}

	// find_last_of returns string::npos if nothing is found, so this works
	// even if the module doesn't have a version
	string moduleBaseName = moduleName.substr(0, moduleName.find_last_of("-"));

	ofs << moduleName << "=$litestepdir$modules\\" << moduleName << "\\" <<
		moduleBaseName << ".dll" << endl;

	ofs.close();

	return true;
}