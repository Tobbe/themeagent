#ifndef THEME_INSTALLER_H_
#define THEME_INSTALLER_H_

#include <string>
#include <vector>
#include "Observer.h"
#include "Observable.h"
#include "ThemeList.h"
#include "ModuleManager.h"
#include "ThemeUsabilityAnalizer.h"

class ThemeInstaller : public Observable, public Observer
{
private:
	std::string themesDir;
	ModuleManager moduleManager;
	ThemeList themeList;
	ThemeUsabilityAnalizer themeUsabilityAnalizer;
public:
	ThemeInstaller(std::string pathToThemesDir, std::string modulesDir,
		std::string nlmIniPath, ThemeList themeList,
		std::vector<std::string> moduleDownloadSites);
	bool installTheme(std::string pathToThemeArchive);
	virtual void update(const Observable *o);
};

#endif