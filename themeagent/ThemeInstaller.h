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
	bool installModules(const Theme &theme);
	std::string unzipTheme(const std::string &pathToThemeArchive) const;
	std::string getThemeDir(const std::string &pathToThemeArchive, const std::string &unzipDirectory) const;
	std::string getUnzipDirectory(const std::string &pathToThemeArchive) const;
	std::string findAvailableDir(const std::string &basePath) const;
public:
	ThemeInstaller(std::string pathToThemesDir, std::string modulesDir,
		std::string nlmIniPath, ThemeList themeList,
		std::vector<std::string> moduleDownloadSites);
	bool installTheme(std::string pathToThemeArchive);
	virtual void update(const Observable *o);
};

#endif