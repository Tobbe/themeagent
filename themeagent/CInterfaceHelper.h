#ifndef C_INTERFACE_HELPER_H_
#define C_INTERFACE_HELPER_H_

#include "Observer.h"

class ThemeInstaller;
class ThemeInstallerObserver;
class ThemeList;
class ThemeListObserver;
class ThemeSwitcher;

class CInterfaceHelper
{
private:
	ThemeInstaller *ti;
	ThemeList *tl;
	ThemeSwitcher *ts;
	ThemeListObserver *tlo;
	ThemeInstallerObserver *tio;
	int actThemeIndex;
	void (__stdcall *tlCallback)(const char *name, int index);
	void (__stdcall *atCallback)(int index);
	void (__stdcall *tiCallback)(int progress, const char *filename,
		bool installationDone, unsigned int numModulesToInstall,
		unsigned int curInstallingModule);

public:
	CInterfaceHelper();
	~CInterfaceHelper();
	void updateThemeList();
	void updateThemeInstaller();
	void setThemeListCallback(void (__stdcall *func)(const char *name, int index));
	void forceThemeListUpdate();
	void setActiveTheme(int index);
	void setActiveThemeCallback(void (__stdcall *func)(int index));
	void getActiveThemeDetails(char *name, char *author, char *version, 
		char *preview);
	void switchTheme();
	void switchTheme(int index);
	void installTheme(const char *pathToArchive);
	void setThemeInstallerCallback(void (__stdcall *func)(int progress,
		const char *filename, bool installationDone,
		unsigned int numModulesToInstall, unsigned int curInstallingModule));
};

#endif
