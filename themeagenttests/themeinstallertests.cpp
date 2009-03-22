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
		vector<string> dlSites;
		dlSites.push_back("http://www.ls-themes.org/modules/download/");
		dlSites.push_back("http://shellfront.org/modules/");
		ThemeInstaller ti("TestFiles\\Themes", "TestFiles\\Modules", "",
			ThemeList("TestFiles\\Themes"), dlSites);

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

		DeleteFile("TestFiles\\Modules\\lsxcommand-2.0.2.dll");
		DeleteFile("TestFiles\\Modules\\xDesk-1.0.dll");
		DeleteFile("TestFiles\\Modules\\xLabel-4.0.9.dll");
		DeleteFile("TestFiles\\Modules\\xPaintClass-1.0.dll");
		DeleteFile("TestFiles\\Modules\\xPopup-2.0.1.dll");
		DeleteFile("TestFiles\\Modules\\xStatsClass-1.0.dll");
		DeleteFile("TestFiles\\Modules\\xTaskbar-2.2.dll");
		DeleteFile("TestFiles\\Modules\\xTray-2.0.1.dll");
		DeleteFile("TestFiles\\Modules\\clickonic-1.0.7.dll");

		DeleteFile("TestFiles\\Modules\\archive\\lsxcommand-2.0.2.zip");
		DeleteFile("TestFiles\\Modules\\archive\\xDesk-1.0.zip");
		DeleteFile("TestFiles\\Modules\\archive\\xLabel-4.0.9.zip");
		DeleteFile("TestFiles\\Modules\\archive\\xPaintClass-1.0.zip");
		DeleteFile("TestFiles\\Modules\\archive\\xPopup-2.0.1.zip");
		DeleteFile("TestFiles\\Modules\\archive\\xStatsClass-1.0.zip");
		DeleteFile("TestFiles\\Modules\\archive\\xTaskbar-2.2.zip");
		DeleteFile("TestFiles\\Modules\\archive\\xTray-2.0.1.zip");
		DeleteFile("TestFiles\\Modules\\archive\\clickonic-1.0.7.zip");

		DeleteFile("TestFiles\\Modules\\docs\\clickonic-1.0.7.chm");
		DeleteFile("TestFiles\\Modules\\docs\\lsxcommand-2.0.2.chm");
		DeleteFile("TestFiles\\Modules\\docs\\xDesk-1.0.txt");
		DeleteFile("TestFiles\\Modules\\docs\\xLabel-4.0.9.chm");
		DeleteFile("TestFiles\\Modules\\docs\\xPopup-2.0.1.chm");
		DeleteFile("TestFiles\\Modules\\docs\\xTaskbar-2.2.chm");
		DeleteFile("TestFiles\\Modules\\docs\\xTray-2.0.1.chm");
		DeleteFile("TestFiles\\Modules\\docs\\xPaintClass-1.0.txt");
		DeleteFile("TestFiles\\Modules\\docs\\xStatsClass-1.0\\xStatsClass.htm");
		DeleteFile("TestFiles\\Modules\\docs\\xStatsClass-1.0\\litestep_logo.png");
		RemoveDirectory("TestFiles\\Modules\\docs\\xStatsClass-1.0");

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