#include "CInterfaceHelper.h"
#include "ThemeList.h"
#include "ThemeInstaller.h"
#include <string>
#include <vector>

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
	tl->addObserver(this);
}

CInterfaceHelper::~CInterfaceHelper()
{
	delete tl;
	delete ti;
}

void CInterfaceHelper::update(const Observable *o)
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
}

void CInterfaceHelper::forceThemeListUpdate()
{
	update(NULL);
}

void CInterfaceHelper::getThemeDetails(int index, void (__stdcall *func)(char *, char *, char *, char *))
{
}

void CInterfaceHelper::setTheme(int index)
{
}
