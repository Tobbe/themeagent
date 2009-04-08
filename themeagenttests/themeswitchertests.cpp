#include "ThemeSwitcher.h"
#include "ThemeList.h"
#include <UnitTest++.h>
#include <fstream>
#include <windows.h>

using namespace std;

SUITE(ThemeSwitcher)
{
	TEST(SetTheme)
	{
		ThemeSwitcher ts("TestFiles\\Themes");

		RCFile rc("TestFiles\\Themes\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\Themes\\ThemeTestOne", rc);

		CHECK(ts.switchTheme(t) == true);

		ifstream fin("TestFiles\\Themes\\themeselect.rc");
		string line;

		CHECK(fin.is_open());

		getline(fin, line);
		CHECK(line == ";------------------------------------------------------------------------------");
		getline(fin, line);
		CHECK(line == ";   edit this evar to switch themes");
		getline(fin, line);
		CHECK(line == ";------------------------------------------------------------------------------");
		getline(fin, line);
		CHECK(line == "");
		getline(fin, line);
		CHECK(line == "ThemeDir \"$ThemesDir$ThemeTestOne\\\"");
		getline(fin, line);
		CHECK(line == "");
		getline(fin, line);
		CHECK(fin.eof());

		fin.clear();
		fin.close();

		RCFile rc2("TestFiles\\Themes\\Turtle Soup II\\theme.rc");
		Theme t2("TestFiles\\Themes\\Turtle Soup II", rc2);

		CHECK(ts.switchTheme(t2) == true);

		fin.open("TestFiles\\Themes\\themeselect.rc");

		CHECK(fin.is_open());

		getline(fin, line);
		CHECK(line == ";------------------------------------------------------------------------------");
		getline(fin, line);
		CHECK(line == ";   edit this evar to switch themes");
		getline(fin, line);
		CHECK(line == ";------------------------------------------------------------------------------");
		getline(fin, line);
		CHECK(line == "");
		getline(fin, line);
		CHECK(line == "ThemeDir \"$ThemesDir$Turtle Soup II\\\"");
		getline(fin, line);
		CHECK(line == "");
		getline(fin, line);
		CHECK(fin.eof());

		fin.close();

		DeleteFile("TestFiles\\Themes\\themeselect.rc");
	}

	TEST(SetNullTheme)
	{
		ThemeList tl("TestFiles\\Themes");
		ThemeSwitcher ts("TestFiles\\Themes");

		CHECK(ts.switchTheme(tl[99]) == false);
		CHECK(GetFileAttributes("TestFiles\\Themes\\themeselect.rc") == INVALID_FILE_ATTRIBUTES);
	}
}
