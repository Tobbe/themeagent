#ifndef THEME_INSTALLER_OBSERVER_H_
#define THEME_INSTALLER_OBSERVER_H_

#include "observer.h"

class CInterfaceHelper;
class ThemeInstaller;
class Observable;

class ThemeInstallerObserver : public Observer
{
private:
	CInterfaceHelper *cih;
public:
	ThemeInstallerObserver(CInterfaceHelper *cih, ThemeInstaller *ti);
	virtual void update(const Observable *o);
};

#endif
