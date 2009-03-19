#include "ThemeValidator.h"
#include <UnitTest++.h>
#include "ModuleManager.h"
#include "Theme.h"
#include <vector>

using namespace std;

SUITE(ThemeValidator)
{
	TEST(ValidateTheme)
	{
		ModuleManager mm("TestFiles\\Modules", "", vector<string>());
		ThemeValidator tv(mm.getModuleList());

		RCFile rc("TestFiles\\Themes\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\Themes\\ThemeTestOne", rc);

		CHECK(tv.validateTheme(t) == false); // Missing modules

		RCFile rc2("TestFiles\\Themes\\ThemeMissingModule\\theme.rc");
		Theme t2("TestFiles\\Themes\\ThemeMissingModule", rc2);

		CHECK(tv.validateTheme(t2) == false); // Missing module (wrong version)

		RCFile rc3("TestFiles\\Themes\\Turtle Soup II\\theme.rc");
		Theme t3("TestFiles\\Themes\\Turtle Soup II", rc3);

		CHECK(tv.validateTheme(t3) == false); // Wrong (no) OTS version and missing modules

		RCFile rc4("TestFiles\\Themes\\ThemeValidate\\theme.rc");
		Theme t4("TestFiles\\Themes\\ThemeValidate", rc4);

		CHECK(tv.validateTheme(t4) == true);
	}
}