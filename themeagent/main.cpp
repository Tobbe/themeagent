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
