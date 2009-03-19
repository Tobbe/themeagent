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
#include "unzip.cpp"
#include "ThemeInstaller.cpp"
#include "ThemeValidator.cpp"
#include <UnitTest++.h>

int main()
{
	return UnitTest::RunAllTests();
}