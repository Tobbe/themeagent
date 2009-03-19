#include "ThemeInstaller.h"
#include <windows.h>
#include "unzip.h"
#include <string>

using namespace std;

ThemeInstaller::ThemeInstaller(string pathToThemesDir) : themesDir(pathToThemesDir)
{
}

bool ThemeInstaller::installTheme(string pathToThemeArchive)
{
	ZIPENTRY ze;
	HZIP hz = OpenZip(pathToThemeArchive.c_str(), NULL);
	GetZipItem(hz, -1, &ze); // -1 gives overall information about the zipfile

	size_t numitems = ze.index;

	if (numitems == 0)
	{
		CloseZip(hz);

		return false;
	}

	SetUnzipBaseDir(hz, themesDir.c_str());

	for (size_t i = 0; i < numitems; ++i)
	{
		GetZipItem(hz, i, &ze); // fetch individual details e.g. the item's name.
		UnzipItem(hz, i, ze.name);
	}

	CloseZip(hz);

	return true;
}