#include "CInterfaceHelper.h"
#include <windows.h>

CInterfaceHelper cih;

extern "C" __declspec(dllexport) void setThemeListCallback(void (__stdcall *func)(const char *name, int index))
{
	cih.setThemeListCallback(func);
}

extern "C" __declspec(dllexport) void forceThemeListUpdate()
{
	cih.forceThemeListUpdate();
}

extern "C" __declspec(dllexport) void setActiveTheme(int index)
{
	cih.setActiveTheme(index);
}

extern "C" __declspec(dllexport) void setActiveThemeCallback(void (__stdcall *func)(int index))
{
	cih.setActiveThemeCallback(func);
}

extern "C" __declspec(dllexport) void getActiveThemeDetails(char *name, char *author, char *version, char *preview)
{
	cih.getActiveThemeDetails(name, author, version, preview);
}

extern "C" __declspec(dllexport) void switchThemeWithIndex(int index)
{
	cih.switchTheme(index);
}

extern "C" __declspec(dllexport) void switchTheme()
{
	cih.switchTheme();
}

extern "C" __declspec(dllexport) void installTheme(const char *pathToArchive)
{
	cih.installTheme(pathToArchive);
}

extern "C" __declspec(dllexport) void setThemeInstallerCallback(
	void (__stdcall *func)(int progress, const char *currentFile,
	bool installationDone, unsigned int numModulesToInstall,
	unsigned int curInstallingModule))
{
	cih.setThemeInstallerCallback(func);
}
