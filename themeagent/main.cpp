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
