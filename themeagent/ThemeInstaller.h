#ifndef THEME_INSTALLER_H_
#define THEME_INSTALLER_H_

#include <string>
#include "Observer.h"
#include "Observable.h"

class ThemeInstaller : public Observable, public Observer
{
private:
	std::string themesDir;
public:
	ThemeInstaller(std::string pathToThemesDir);
	bool installTheme(std::string pathToThemeArchive);
	virtual void update(const Observable *o);
};

#endif