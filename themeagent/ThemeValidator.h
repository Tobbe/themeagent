#ifndef THEME_VALIDATOR_H_
#define THEME_VALIDATOR_H_

#include "Theme.h"
#include "ModuleList.h"

class ThemeValidator
{
private:
	ModuleList installedModules;

	bool checkOTSVersion(const Theme &theme) const;
	bool checkModuleDependencies(const Theme &theme) const;
public:
	ThemeValidator(ModuleList installedModules);
	bool validateTheme(const Theme &theme);
};

#endif