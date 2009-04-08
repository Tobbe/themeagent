#include "ThemeListObserver.h"

#include "ThemeList.h"
#include "Observable.h"
#include "CInterfaceHelper.h"

ThemeListObserver::ThemeListObserver(CInterfaceHelper *cih, ThemeList *tl)
{
	this->cih = cih;
	tl->addObserver(this);
}

void ThemeListObserver::update(const Observable *o)
{
	cih->updateThemeList();
}
