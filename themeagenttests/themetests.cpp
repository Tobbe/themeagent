#include <UnitTest++.h>
#include "Theme.h"
#include "RCFile.h"
#include <windows.h>
#include <cassert>
#include <string>

using namespace std;

class SetupFixtureTheme {
public:
	string testFilesPath;

	SetupFixtureTheme()
	{
		char buffer[MAX_PATH];

		if (GetModuleFileName(NULL, buffer, MAX_PATH) == 0)
		{
			assert(false);
		}

		testFilesPath = buffer;
		int index = testFilesPath.find_last_of('\\');

		if (index == string::npos)
		{
			assert(false);
		}

		testFilesPath = testFilesPath.substr(0, index) + "\\..\\themeagenttests\\TestFiles";
	}
};

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
		Theme t3("testfiles\\themetesttwo", rc3);

		CHECK(t3.getVersion() == "1.0");
	}

	TEST_FIXTURE(SetupFixtureTheme, GetPreview)
	{
		RCFile rc(testFilesPath + "\\ThemeTestOne\\theme.rc");
		Theme t(testFilesPath + "\\ThemeTestOne\\", rc);

		CHECK(t.getPreview() == "");

		RCFile rc2(testFilesPath + "\\ThemePreviewOne\\theme.rc");
		Theme t2(testFilesPath + "\\ThemePreviewOne", rc2);

		CHECK(t2.getPreview() == "preview.bmp");

		RCFile rc3(testFilesPath + "\\ThemePreviewTwo\\theme.rc");
		Theme t3(testFilesPath + "\\ThemePreviewTwo", rc3);

		CHECK(t3.getPreview() == "preview.png");
	}
}