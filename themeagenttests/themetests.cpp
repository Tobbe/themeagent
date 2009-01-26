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
	TEST_FIXTURE(SetupFixtureTheme, GetName)
	{
		RCFile rc("TestFiles\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\ThemeTestOne", rc);

		CHECK(t.getName() == "ThemeTestOne");

		RCFile rc2(testFilesPath + "\\Turtle Soup II\\theme.rc");
		Theme t2(testFilesPath + "\\Turtle Soup II", rc2);

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

	TEST(GetPath)
	{
		RCFile rc("");
		Theme t("Q:\\This\\is\\a\\test\\", rc);

		CHECK(t.getPath() == "Q:\\This\\is\\a\\test");

		Theme t2("Q:\\This\\..\\a\\..\\", rc);

		CHECK(t2.getPath() == "Q:");

		Theme t3("test\\", rc);
		TCHAR buffer[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, buffer);

		CHECK(t3.getPath() == string(buffer) + "\\test");
	}

	TEST(GetOTSVersion)
	{
		RCFile rc("TestFiles\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\ThemeTestOne", rc);

		CHECK(t.getOTSVersion() == "2.0");

		RCFile rc2("TestFiles\\Turtle Soup II\\theme.rc");
		Theme t2("TestFiles\\Turtle Soup II", rc2);

		CHECK(t2.getOTSVersion() == "");

		RCFile rc3("testfiles\\themetesttwo\\theme.rc");
		Theme t3("testfiles\\themetesttwo", rc3);

		CHECK(t3.getOTSVersion() == "2");
	}

	TEST(GetNeededModules)
	{
		RCFile rc("TestFiles\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\ThemeTestOne", rc);

		ModuleList neededModules = t.getNeededModules();

		CHECK(neededModules.size() == 6);
		CHECK(neededModules.contains(Module("jdesk-0.711")));
		CHECK(neededModules.contains(Module("xtaskbar-1.1.5")));
		CHECK(neededModules.contains(Module("vtray-1.10")));
		CHECK(neededModules.contains(Module("popup2-2.1.7")));
		CHECK(neededModules.contains(Module("lsxcommand-1.9.3")));
		CHECK(neededModules.contains(Module("icondesk-0.68")));
	}
}