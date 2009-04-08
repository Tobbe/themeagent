#include "ThemeSetter.h"
#include <string>
#include <fstream>

using namespace std;

ThemeSetter::ThemeSetter(string themesDir) : themesDir(themesDir)
{
}

bool ThemeSetter::setTheme(const Theme &theme) const
{
	if (theme.getFolder() == "")
	{
		return false;
	}

	string path = themesDir + "\\themeselect.rc";
	ofstream fout(path.c_str(), std::ios_base::trunc);

	if (!fout.is_open())
	{
		return false;
	}

	fout << ";------------------------------------------------------------------------------" << endl;
	fout << ";   edit this evar to switch themes" << std::endl;
	fout << ";------------------------------------------------------------------------------" << endl;
	fout << endl;
	fout << "ThemeDir \"$ThemesDir$" << theme.getFolder() << "\\\"" << endl;
	fout << endl;

	fout.close();

	return true;
}