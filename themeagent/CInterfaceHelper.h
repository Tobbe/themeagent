#ifndef C_INTERFACE_HELPER_H_
#define C_INTERFACE_HELPER_H_

#include "Observer.h"

class ThemeInstaller;
class ThemeList;

class CInterfaceHelper : public Observer
{
private:
	ThemeInstaller *ti;
	ThemeList *tl;
	void (__stdcall *tlCallback)(const char *name, int index);
public:
	CInterfaceHelper();
	~CInterfaceHelper();
	void update(const Observable *o);
	void setThemeListCallback(void (__stdcall *func)(const char *name, int index));
	void forceThemeListUpdate();
	void setTheme(int index);
	void getThemeDetails(int index, void (__stdcall *func)(char *themeName,
		char *themeAuthor, char *themeVersion, char *themePreview));
};

#endif