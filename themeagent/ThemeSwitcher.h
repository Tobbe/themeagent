#ifndef THEME_SETTER_H_
#define THEME_SETTER_H_

#include "Theme.h"
#include <string>

class ThemeSwitcher
{
private:
	std::string themesDir;
public:
	ThemeSwitcher(std::string themesDir);
	bool switchTheme(const Theme &theme) const;
};

#endif
