#include "ThemeUsabilityAnalizer.h"
#include "Module.h"
#include <string>

using namespace std;

ThemeUsabilityAnalizer::ThemeUsabilityAnalizer(const ModuleManager &moduleManager) : moduleManager(moduleManager)
{
}

bool ThemeUsabilityAnalizer::themeIsUsable(const Theme &theme)
{
	return checkOTSVersion(theme) && checkModuleDependencies(theme);
}

bool ThemeUsabilityAnalizer::checkOTSVersion(const Theme &theme) const
{
	string otsMajorVersion = theme.getOTSVersion().substr(0, 1);
	return otsMajorVersion == "2";
}

bool ThemeUsabilityAnalizer::checkModuleDependencies(const Theme &theme) const
{
	ModuleList needed = theme.getNeededModules();
	ModuleList existing = moduleManager.getModuleList();

	for (ModuleList::const_iterator itr = needed.begin(); itr != needed.end(); ++itr)
	{
		if (!existing.contains(*itr))
		{
			return false;
		}
	}

	return true;
}