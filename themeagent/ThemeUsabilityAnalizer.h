#ifndef THEME_USABILITY_ANALIZER_H_
#define THEME_USABILITY_ANALIZER_H_

#include "Theme.h"
#include "ModuleList.h"

class ThemeUsabilityAnalizer
{
private:
	ModuleList installedModules;

	bool checkOTSVersion(const Theme &theme) const;
	bool checkModuleDependencies(const Theme &theme) const;
public:
	ThemeUsabilityAnalizer(ModuleList installedModules);
	bool validateTheme(const Theme &theme);
};

#endif