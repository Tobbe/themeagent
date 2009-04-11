#include "ThemeInstallerObserver.h"
#include "CInterfaceHelper.h"
#include "ThemeInstaller.h"
#include "Observable.h"

ThemeInstallerObserver::ThemeInstallerObserver(CInterfaceHelper *cih, ThemeInstaller *ti)
{
	ti->addObserver(this);
	this->cih = cih;
}

void ThemeInstallerObserver::update(const Observable *o)
{
	cih->updateThemeInstaller();
}
