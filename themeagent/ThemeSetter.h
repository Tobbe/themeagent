#ifndef THEME_SETTER_H_
#define THEME_SETTER_H_

#include "Theme.h"
#include <string>

class ThemeSetter
{
private:
	std::string themesDir;
public:
	ThemeSetter(std::string themesDir);
	bool setTheme(const Theme &theme) const;
};

#endif
