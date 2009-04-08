#ifndef C_INTERFACE_HELPER_H_
#define C_INTERFACE_HELPER_H_

#include "Observer.h"

class ThemeInstaller;
class ThemeList;
class ThemeSwitcher;

class CInterfaceHelper
{
private:
	ThemeInstaller *ti;
	ThemeList *tl;
	ThemeSwitcher *ts;
	int actThemeIndex;
	void (__stdcall *tlCallback)(const char *name, int index);
	void (__stdcall *atCallback)(int index);
public:
	CInterfaceHelper();
	~CInterfaceHelper();
	void updateThemeList();
	void setThemeListCallback(void (__stdcall *func)(const char *name, int index));
	void forceThemeListUpdate();
	void setActiveTheme(int index);
	void setActiveThemeCallback(void (__stdcall *func)(int index));
	void getActiveThemeDetails(char *name, char *author, char *version, 
		char *preview);
	void switchTheme();
	void switchTheme(int index);
};

#endif