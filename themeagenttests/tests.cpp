#include "Module.cpp"
#include "ModuleList.cpp"
#include "RCFile.cpp"
#include "Theme.cpp"
#include "ThemeList.cpp"
#include "NullTheme.cpp"
#include "Observable.cpp"
#include "FileDownloader.cpp"
#include "URLDownloadCallback.cpp"
#include "ModuleManager.cpp"
#define _CRT_SECURE_NO_WARNINGS 1
#include "unzip.cpp"
#undef _CRT_SECURE_NO_WARNINGS
#include <UnitTest++.h>

int main()
{
	return UnitTest::RunAllTests();
}