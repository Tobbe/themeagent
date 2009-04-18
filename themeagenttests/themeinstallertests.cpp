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
		ThemeList tl("TestFiles\\Themes");
		ThemeInstaller ti("TestFiles\\Themes", "TestFiles\\Modules", "", &tl,
			dlSites);

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

	TEST(UpdateThemeList)
	{
		vector<string> dlSites;
		dlSites.push_back("http://www.ls-themes.org/modules/download/");
		dlSites.push_back("http://shellfront.org/modules/");
		ThemeList tl("TestFiles\\Themes");
		ThemeInstaller ti("TestFiles\\Themes", "TestFiles\\Modules", "", &tl,
			dlSites);

		size_t size = tl.size();
		CHECK(ti.installTheme("TestFiles\\Themes\\ArchivedTheme.lsz") == true);
		CHECK(tl.size() == size + 1);

		int found = 0;
		for (size_t i = 0; i < tl.size(); ++i)
		{
			if (tl[i].getName() == "ArchivedTheme")
			{
				++found;
			}
		}

		CHECK(found == 1);

		DeleteFile("TestFiles\\Themes\\ArchivedTheme\\theme.rc");
		RemoveDirectory("TestFiles\\Themes\\ArchivedTheme");
	}

	TEST(ThemeInstallerNotify)
	{
		class TIObserver : public Observer
		{
		public:
			ThemeInstaller *ti;
			std::string stringToSearchFor;
			int modNumToSearchFor;
			bool foundString;
			bool foundModNum;
			bool gotDone;
			int oldProgress;
			bool progressIncreases;
			int totalNumberOfModulesToInstall;

			TIObserver(ThemeInstaller *ti)
			{
				this->ti = ti;
				foundString = false;
				foundModNum = false;
				gotDone = false;
				oldProgress = 0;
				progressIncreases = true;
				ti->addObserver(this);
			}

			void searchFor(std::string needle)
			{
				stringToSearchFor = needle;
			}

			void moduleNumToSearchFor(int needle)
			{
				modNumToSearchFor = needle;
			}

			void update(const Observable *o)
			{
				if (ti->getCurrentFile() == stringToSearchFor)
				{
					foundString = true;
				}
				
				if (ti->getInstallationDone())
				{
					gotDone = true;
				}

				if (ti->getProgress() < oldProgress)
				{
					progressIncreases = false;
				}

				oldProgress = ti->getProgress();

				if (ti->getCurInstallingModule() == modNumToSearchFor)
				{
					foundModNum = true;
				}

				if (ti->getNumModulesToInstall() != totalNumberOfModulesToInstall)
				{
					totalNumberOfModulesToInstall = ti->getNumModulesToInstall();
				}
			}
		};

		vector<string> dlSites;
		dlSites.push_back("http://www.ls-themes.org/modules/download/");
		dlSites.push_back("http://shellfront.org/modules/");
		ThemeList tl("TestFiles\\Themes");
		ThemeInstaller ti("TestFiles\\Themes", "TestFiles\\Modules", "", &tl,
			dlSites);

		TIObserver tio1(&ti);
		tio1.searchFor("Rock.Steady/theme.rc");
		tio1.moduleNumToSearchFor(1);

		TIObserver tio2(&ti);
		tio2.searchFor("Rock.Steady/config/CommandBox.rc");
		tio2.moduleNumToSearchFor(2);

		TIObserver tio3(&ti);
		tio3.searchFor("Rock.Steady/config/desktop.rc");
		tio3.moduleNumToSearchFor(3);

		TIObserver tio4(&ti);
		tio4.searchFor("Rock.Steady/config/themevars.rc");
		tio4.moduleNumToSearchFor(4);

		TIObserver tio5(&ti);
		tio5.searchFor("Rock.Steady/config/xLabel_TaskBar.rc");
		tio5.moduleNumToSearchFor(8);

		TIObserver tio6(&ti);
		tio6.searchFor("Rock.Steady/config/xpopup.rc");
		tio6.moduleNumToSearchFor(9);

		CHECK(ti.installTheme("TestFiles\\Themes\\Rock.Steady.lsz") == true);

		CHECK(tio1.foundString == true);
		CHECK(tio2.foundString == true);
		CHECK(tio3.foundString == true);
		CHECK(tio4.foundString == true);
		CHECK(tio5.foundString == true);
		CHECK(tio6.foundString == true);

		CHECK(tio1.gotDone == true);
		CHECK(tio2.gotDone == true);
		CHECK(tio3.gotDone == true);
		CHECK(tio4.gotDone == true);
		CHECK(tio5.gotDone == true);
		CHECK(tio6.gotDone == true);

		CHECK(tio1.progressIncreases == true);
		CHECK(tio2.progressIncreases == true);
		CHECK(tio3.progressIncreases == true);
		CHECK(tio4.progressIncreases == true);
		CHECK(tio5.progressIncreases == true);
		CHECK(tio6.progressIncreases == true);

		CHECK(tio1.foundModNum == true);
		CHECK(tio2.foundModNum == true);
		CHECK(tio3.foundModNum == true);
		CHECK(tio4.foundModNum == true);
		CHECK(tio5.foundModNum == true);
		CHECK(tio6.foundModNum == true);

		CHECK(tio1.totalNumberOfModulesToInstall == 9);
		CHECK(tio2.totalNumberOfModulesToInstall == 9);
		CHECK(tio3.totalNumberOfModulesToInstall == 9);
		CHECK(tio4.totalNumberOfModulesToInstall == 9);
		CHECK(tio5.totalNumberOfModulesToInstall == 9);
		CHECK(tio6.totalNumberOfModulesToInstall == 9);

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
	}
}
