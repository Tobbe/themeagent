#ifndef THEME_LIST_OBSERVER_H_
#define THEME_LIST_OBSERVER_H_

#include "Observer.h"

class ThemeList;
class CInterfaceHelper;
class Observable;

class ThemeListObserver : public Observer
{
private:
	CInterfaceHelper *cih;
public:
	ThemeListObserver(CInterfaceHelper *cih, ThemeList *tl);
	void update(const Observable *o);
};

#endif
