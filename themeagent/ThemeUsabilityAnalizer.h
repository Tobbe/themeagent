#ifndef THEME_USABILITY_ANALIZER_H_
#define THEME_USABILITY_ANALIZER_H_

#include "Theme.h"
#include "ModuleManager.h"

class ThemeUsabilityAnalizer
{
private:
	const ModuleManager &moduleManager;

	bool checkOTSVersion(const Theme &theme) const;
	bool checkModuleDependencies(const Theme &theme) const;
public:
	ThemeUsabilityAnalizer(const ModuleManager &moduleManager);
	bool themeIsUsable(const Theme &theme);
};

#endif