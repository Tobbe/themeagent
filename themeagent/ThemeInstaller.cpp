#include "ThemeInstaller.h"
#include "ThemeList.h"
#include "Theme.h"
#include "RCFile.h"
#include "ModuleList.h"
#include <windows.h>
#include "unzip.h"
#include <string>
#include <sstream>

using namespace std;

ThemeInstaller::ThemeInstaller(string pathToThemesDir, string modulesDir,
	string nlmIniPath, ThemeList *themeList,
	vector<string> moduleDownloadSites) :
	themesDir(pathToThemesDir), themeList(themeList),
	moduleManager(modulesDir, nlmIniPath, moduleDownloadSites),
	themeUsabilityAnalizer(moduleManager)
{
}

bool ThemeInstaller::installTheme(string pathToThemeArchive)
{
	string themeDir = unzipTheme(pathToThemeArchive);
	if (themeDir == "")
	{
		return false;
	}

	RCFile rc(themesDir + "\\" + themeDir + "\\theme.rc");
	Theme theme(themesDir + "\\" + themeDir, rc);

	bool instMods = installModules(theme);

	themeList->addTheme(theme);

	if (!instMods)
	{
		return false;
	}

	return themeUsabilityAnalizer.themeIsUsable(theme);
}

bool ThemeInstaller::installModules(const Theme &theme)
{
	ModuleList needed = theme.getNeededModules();
	ModuleList existing = moduleManager.getModuleList();
	bool instModOK = true;

	for (ModuleList::const_iterator itr = needed.begin(); itr != needed.end(); ++itr)
	{
		if (!existing.contains(*itr))
		{
			if (!moduleManager.installModule(*itr))
			{
				instModOK = false;
			}
		}
	}

	return instModOK;
}

string ThemeInstaller::unzipTheme(const string &pathToThemeArchive) const
{
	ZIPENTRY ze;
	HZIP hz = OpenZip(pathToThemeArchive.c_str(), NULL);
	GetZipItem(hz, -1, &ze); // -1 gives overall information about the zipfile

	size_t numitems = ze.index;

	if (numitems == 0)
	{
		CloseZip(hz);

		return "";
	}

	string unzipDir = getUnzipDirectory(pathToThemeArchive);
	SetUnzipBaseDir(hz, unzipDir.c_str());

	for (size_t i = 0; i < numitems; ++i)
	{
		GetZipItem(hz, i, &ze);
		UnzipItem(hz, i, ze.name);
	}

	CloseZip(hz);

	return getThemeDir(pathToThemeArchive, unzipDir);
}

string ThemeInstaller::getThemeDir(const string &pathToThemeArchive,
	const string &unzipDirectory) const
{
	ZIPENTRY ze;
	HZIP hz = OpenZip(pathToThemeArchive.c_str(), NULL);

	GetZipItem(hz, 0, &ze); // fetch individual details e.g. the item's name.
	string firstItemName = ze.name;
	string path = themesDir + "\\" + firstItemName + "\\theme.rc";

	if (GetFileAttributes(path.c_str()) != INVALID_FILE_ATTRIBUTES)
	{
		return firstItemName.substr(0, firstItemName.length() - 1);
	}

	path = unzipDirectory + "\\theme.rc";

	if (GetFileAttributes(path.c_str()) != INVALID_FILE_ATTRIBUTES)
	{
		size_t slashIndex = unzipDirectory.find_last_of("\\/");
		return unzipDirectory.substr(slashIndex + 1, unzipDirectory.length() - slashIndex);
	}

	return "";
}

string ThemeInstaller::getUnzipDirectory(const string &pathToThemeArchive) const
{
	ZIPENTRY ze;
	HZIP hz = OpenZip(pathToThemeArchive.c_str(), NULL);
	bool singleDir = true;
	string unzipDirectory;

	GetZipItem(hz, 0, &ze); // fetch individual details e.g. the item's name.
	string firstItemName = ze.name;

	if (firstItemName.find_last_of("\\/") != firstItemName.length() - 1)
	{
		singleDir = false;
	}

	GetZipItem(hz, -1, &ze); // -1 gives overall information about the zipfile
	size_t numitems = ze.index;

	string currentItemName;
	size_t i = 1;
	while (singleDir && i < numitems)
	{
		GetZipItem(hz, i, &ze);
		currentItemName = ze.name;

		if (firstItemName != currentItemName.substr(0, firstItemName.length()))
		{
			singleDir = false;
		}

		++i;
	}

	CloseZip(hz);

	if (singleDir)
	{
		unzipDirectory = themesDir;
	}
	else
	{
		size_t slashIndex = pathToThemeArchive.find_last_of("\\/");
		string zipName = pathToThemeArchive.substr(slashIndex + 1, pathToThemeArchive.length() - slashIndex);
		zipName = zipName.substr(0, zipName.find_last_of("."));

		unzipDirectory = findAvailableDir(themesDir + "\\" + zipName);
	}

	return unzipDirectory;
}

string ThemeInstaller::findAvailableDir(const string &basePath) const
{
	ostringstream ostr;
	int index = 1;
	ostr << basePath;
	string tmp;

	while (!CreateDirectory(ostr.str().c_str(), NULL))
	{
		ostr.clear();
		ostr.str(string());
		index++;
		ostr << basePath << " (" << index << ")";
	}

	return ostr.str();
}

void ThemeInstaller::update(const Observable *o)
{
	notifyObservers(this);
}
