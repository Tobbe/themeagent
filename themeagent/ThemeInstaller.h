#ifndef THEME_INSTALLER_H_
#define THEME_INSTALLER_H_

#include <string>

class ThemeInstaller
{
private:
	std::string themesDir;
public:
	ThemeInstaller(std::string pathToThemesDir);
	bool installTheme(std::string pathToThemeArchive);
};

#endif