#include <UnitTest++.h>
#include "Theme.h"
#include "RCFile.h"
#include <windows.h>
#include <cassert>
#include <string>

using namespace std;

SUITE(Theme)
{
	TEST(GetName)
	{
		RCFile rc("TestFiles\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\ThemeTestOne", rc);

		CHECK(t.getName() == "ThemeTestOne");
	}

	TEST(GetAuthor)
	{
		RCFile rc("TestFiles\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\ThemeTestOne", rc);

		CHECK(t.getAuthor() == "Test Author");
	}

	TEST(GetVersion)
	{
		RCFile rc("TestFiles\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\ThemeTestOne", rc);

		CHECK(t.getVersion() == "One.5");
	}
}