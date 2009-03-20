#include "ThemeValidator.h"
#include "Module.h"
#include <string>

using namespace std;

ThemeValidator::ThemeValidator(ModuleList installedModules) : installedModules(installedModules)
{
}

bool ThemeValidator::validateTheme(const Theme &theme)
{
	return checkOTSVersion(theme) && checkModuleDependencies(theme);
}

bool ThemeValidator::checkOTSVersion(const Theme &theme) const
{
	string otsMajorVersion = theme.getOTSVersion().substr(0, 1);
	return otsMajorVersion == "2";
}

bool ThemeValidator::checkModuleDependencies(const Theme &theme) const
{
	ModuleList ml = theme.getNeededModules();

	for (ModuleList::const_iterator itr = ml.begin(); itr != ml.end(); ++itr)
	{
		if (!installedModules.contains(*itr))
		{
			return false;
		}
	}

	return true;
}