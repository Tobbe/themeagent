#include "ThemeInstaller.h"
#include <UnitTest++.h>
#include <windows.h>

using namespace std;

SUITE(ThemeInstaller)
{
	TEST(InstallTheme)
	{
		ThemeInstaller ti("TestFiles\\Themes");
		CHECK(ti.installTheme("TestFiles\\Themes\\ArchivedTheme.lsz") == true);
		CHECK(GetFileAttributes("TestFiles\\Themes\\ArchivedTheme\\theme.rc") != INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Themes\\ArchivedTheme\\theme.rc");
		RemoveDirectory("TestFiles\\Themes\\ArchivedTheme");

		CHECK(ti.installTheme("TestFiles\\Themes\\Rock.Steady.lsz") == true);
		CHECK(GetFileAttributes("TestFiles\\Themes\\Rock.Steady\\theme.rc") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Themes\\Rock.Steady\\config\\xpopup.rc") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Themes\\Rock.Steady\\config\\CommandBox.rc") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Themes\\Rock.Steady\\images") == FILE_ATTRIBUTE_DIRECTORY);

		DeleteFile("TestFiles\\Themes\\Rock.Steady\\theme.rc");
		DeleteFile("TestFiles\\Themes\\Rock.Steady\\config\\CommandBox.rc");
		DeleteFile("TestFiles\\Themes\\Rock.Steady\\config\\desktop.rc");
		DeleteFile("TestFiles\\Themes\\Rock.Steady\\config\\themevars.rc");
		DeleteFile("TestFiles\\Themes\\Rock.Steady\\config\\xLabel_TaskBar.rc");
		DeleteFile("TestFiles\\Themes\\Rock.Steady\\config\\xpopup.rc");
		DeleteFile("TestFiles\\Themes\\Rock.Steady\\config\\xTaskbar.rc");
		DeleteFile("TestFiles\\Themes\\Rock.Steady\\config\\xtray.rc");
		RemoveDirectory("TestFiles\\Themes\\Rock.Steady\\config");
		RemoveDirectory("TestFiles\\Themes\\Rock.Steady\\images");
		RemoveDirectory("TestFiles\\Themes\\Rock.Steady");
	}
}