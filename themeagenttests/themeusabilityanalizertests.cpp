#include "ThemeUsabilityAnalizer.h"
#include <UnitTest++.h>
#include "ModuleManager.h"
#include "Theme.h"
#include <vector>

using namespace std;

SUITE(ThemeUsabilityAnalizer)
{
	TEST(ThemeIsUsable)
	{
		ModuleManager mm("TestFiles\\Modules", "", vector<string>());
		ThemeUsabilityAnalizer tv(mm.getModuleList());

		RCFile rc("TestFiles\\Themes\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\Themes\\ThemeTestOne", rc);

		CHECK(tv.themeIsUsable(t) == false); // Missing modules

		RCFile rc2("TestFiles\\Themes\\ThemeMissingModule\\theme.rc");
		Theme t2("TestFiles\\Themes\\ThemeMissingModule", rc2);

		CHECK(tv.themeIsUsable(t2) == false); // Missing module (wrong version)

		RCFile rc3("TestFiles\\Themes\\Turtle Soup II\\theme.rc");
		Theme t3("TestFiles\\Themes\\Turtle Soup II", rc3);

		CHECK(tv.themeIsUsable(t3) == false); // Wrong (no) OTS version and missing modules

		RCFile rc4("TestFiles\\Themes\\ThemeValidate\\theme.rc");
		Theme t4("TestFiles\\Themes\\ThemeValidate", rc4);

		CHECK(tv.themeIsUsable(t4) == true);
	}
}