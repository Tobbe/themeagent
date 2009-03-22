#include "ThemeInstaller.h"
#include "ThemeList.h"
#include <UnitTest++.h>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

SUITE(ThemeInstaller)
{
	TEST(InstallTheme)
	{
		ThemeInstaller ti("TestFiles\\Themes", "TestFiles\\Modules", "",
			ThemeList("TestFiles\\Themes"), vector<string>());

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

		CHECK(ti.installTheme("TestFiles\\Themes\\NoFolderTheme.lsz") == true);
		CHECK(GetFileAttributes("TestFiles\\Themes\\NoFolderTheme\\theme.rc") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Themes\\NoFolderTheme\\readme.txt") != INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Themes\\NoFolderTheme\\theme.rc");
		DeleteFile("TestFiles\\Themes\\NoFolderTheme\\readme.txt");
		RemoveDirectory("TestFiles\\Themes\\NoFolderTheme");

		CHECK(ti.installTheme("TestFiles\\Themes\\NoExtensionTheme") == true);
		CHECK(GetFileAttributes("TestFiles\\Themes\\NoExtensionTheme (2)\\theme.rc") != INVALID_FILE_ATTRIBUTES);
		CHECK(GetFileAttributes("TestFiles\\Themes\\NoExtensionTheme (2)\\docs\\readme_NoExtensionTheme.txt") != INVALID_FILE_ATTRIBUTES);

		DeleteFile("TestFiles\\Themes\\NoExtensionTheme (2)\\theme.rc");
		DeleteFile("TestFiles\\Themes\\NoExtensionTheme (2)\\docs\\readme_NoExtensionTheme.txt");
		RemoveDirectory("TestFiles\\Themes\\NoExtensionTheme (2)\\docs");
		RemoveDirectory("TestFiles\\Themes\\NoExtensionTheme (2)");
	}
}