#include "CInterfaceHelper.h"
#include "ThemeList.h"
#include "ThemeInstaller.h"
#include "ThemeSwitcher.h"
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

CInterfaceHelper::CInterfaceHelper()
{
	tlCallback = NULL;
	string themesDir = "C:\\Tobbe\\DevProjects\\C++\\themeagent\\themeagenttests\\TestFiles\\Themes";
	string modulesDir = "C:\\Tobbe\\DevProjects\\C++\\themeagent\\themeagenttests\\TestFiles\\Modules";
	string nlmIniPath = "C:\\Tobbe\\DevProjects\\C++\\themeagent\\themeagenttests\\TestFiles\\NLM\\NetLoadModule.ini";
	vector<string> dlSites;
	dlSites.push_back("http://modules.shellfront.org");
	dlSites.push_back("http://www.ls-themes.org/modules/download/");
	tl = new ThemeList(themesDir);
	ti = new ThemeInstaller(themesDir, modulesDir, nlmIniPath, *tl, dlSites);
	ts = new ThemeSwitcher(themesDir);
	actThemeIndex = 0;
}

CInterfaceHelper::~CInterfaceHelper()
{
	delete tl;
	delete ti;
	delete ts;
}

void CInterfaceHelper::updateThemeList()
{
	if (tlCallback != NULL)
	{
		for (size_t i = 0; i < tl->size(); ++i)
		{
			tlCallback((*tl)[i].getName().c_str(), i);
		}
	}
}

void CInterfaceHelper::setThemeListCallback(void (__stdcall *func)(const char *, int))
{
	tlCallback = func;
	updateThemeList();
}

void CInterfaceHelper::forceThemeListUpdate()
{
	updateThemeList();
}

void CInterfaceHelper::getActiveThemeDetails(char *name, char *author, char *version, char *preview)
{
	Theme at = (*tl)[actThemeIndex];
	strncpy_s(name, MAX_PATH, at.getName().c_str(), _TRUNCATE);
	strncpy_s(author, MAX_PATH, at.getAuthor().c_str(), _TRUNCATE);
	strncpy_s(version, MAX_PATH, at.getVersion().c_str(), _TRUNCATE);
	strncpy_s(preview, MAX_PATH, at.getPreview().c_str(), _TRUNCATE);
}

void CInterfaceHelper::setActiveTheme(int index)
{
	if (index >= 0 && static_cast<unsigned int>(index) < tl->size())
	{
		actThemeIndex = index;
		atCallback(index);
	}
}

void CInterfaceHelper::setActiveThemeCallback(void (__stdcall *func)(int index))
{
	atCallback = func;
	atCallback(actThemeIndex);
}

void CInterfaceHelper::switchTheme()
{
	switchTheme(actThemeIndex);
}

void CInterfaceHelper::switchTheme(int index)
{
	ts->switchTheme((*tl)[index]);
}

void CInterfaceHelper::installTheme(const char *pathToArchive)
{
	ti->installTheme(pathToArchive);
}
