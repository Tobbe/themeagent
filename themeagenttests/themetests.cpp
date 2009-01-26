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

		RCFile rc2("TestFiles\\Turtle Soup II\\theme.rc");
		Theme t2("TestFiles\\Turtle Soup II", rc2);

		CHECK(t2.getName() == "Turtle Soup II");

		Theme t3("TestFiles\\Turtle Soup II\\", rc2);

		CHECK(t3.getName() == "Turtle Soup II");

		RCFile rc3("testfiles\\themetesttwo\\theme.rc");
		Theme t4("testfiles\\themetesttwo", rc3);

		CHECK(t4.getName() == "Theme - TestTwo");
	}

	TEST(GetAuthor)
	{
		RCFile rc("TestFiles\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\ThemeTestOne", rc);

		CHECK(t.getAuthor() == "Test Author");

		RCFile rc2("TestFiles\\Turtle Soup II\\theme.rc");
		Theme t2("TestFiles\\Turtle Soup II", rc2);

		CHECK(t2.getAuthor() == "");

		RCFile rc3("testfiles\\themetesttwo\\theme.rc");
		Theme t3("testfiles\\themetesttwo", rc3);

		CHECK(t3.getAuthor() == "MrGnome");
	}

	TEST(GetVersion)
	{
		RCFile rc("TestFiles\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\ThemeTestOne", rc);

		CHECK(t.getVersion() == "One.5");

		RCFile rc2("TestFiles\\Turtle Soup II\\theme.rc");
		Theme t2("TestFiles\\Turtle Soup II", rc2);

		CHECK(t2.getVersion() == "");

		RCFile rc3("testfiles\\themetesttwo\\theme.rc");
		Theme t4("testfiles\\themetesttwo", rc3);

		CHECK(t4.getVersion() == "1.0");
	}
}