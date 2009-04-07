#include <UnitTest++.h>
#include "Theme.h"
#include "RCFile.h"
#include <windows.h>
#include <cassert>
#include <string>

using namespace std;

class SetupFixtureTheme {
public:
	string themesPath;

	SetupFixtureTheme()
	{
		char buffer[MAX_PATH];

		if (GetModuleFileName(NULL, buffer, MAX_PATH) == 0)
		{
			assert(false);
		}

		themesPath = buffer;
		int index = themesPath.find_last_of('\\');

		if (index == string::npos)
		{
			assert(false);
		}

		themesPath = themesPath.substr(0, index) + "\\..\\themeagenttests\\TestFiles\\Themes";
	}
};

SUITE(Theme)
{
	TEST_FIXTURE(SetupFixtureTheme, GetName)
	{
		RCFile rc("TestFiles\\Themes\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\Themes\\ThemeTestOne", rc);

		CHECK(t.getName() == "ThemeTestOne");

		RCFile rc2(themesPath + "\\Turtle Soup II\\theme.rc");
		Theme t2(themesPath + "\\Turtle Soup II", rc2);

		CHECK(t2.getName() == "Turtle Soup II");

		Theme t3("TestFiles\\Themes\\Turtle Soup II\\", rc2);

		CHECK(t3.getName() == "Turtle Soup II");

		RCFile rc3("testfiles\\themes\\themetesttwo\\theme.rc");
		Theme t4("testfiles\\themes\\themetesttwo", rc3);

		CHECK(t4.getName() == "Theme - TestTwo");
	}

	TEST(GetAuthor)
	{
		RCFile rc("TestFiles\\Themes\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\Themes\\ThemeTestOne", rc);

		CHECK(t.getAuthor() == "Test Author");

		RCFile rc2("TestFiles\\Themes\\Turtle Soup II\\theme.rc");
		Theme t2("TestFiles\\Themes\\Turtle Soup II", rc2);

		CHECK(t2.getAuthor() == "");

		RCFile rc3("testfiles\\themes\\themetesttwo\\theme.rc");
		Theme t3("testfiles\\themes\\themetesttwo", rc3);

		CHECK(t3.getAuthor() == "MrGnome");
	}

	TEST(GetVersion)
	{
		RCFile rc("TestFiles\\Themes\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\Themes\\ThemeTestOne", rc);

		CHECK(t.getVersion() == "One.5");

		RCFile rc2("TestFiles\\Themes\\Turtle Soup II\\theme.rc");
		Theme t2("TestFiles\\Themes\\Turtle Soup II", rc2);

		CHECK(t2.getVersion() == "");

		RCFile rc3("testfiles\\themes\\themetesttwo\\theme.rc");
		Theme t3("testfiles\\themes\\themetesttwo", rc3);

		CHECK(t3.getVersion() == "1.0");
	}

	TEST_FIXTURE(SetupFixtureTheme, GetPreview)
	{
		RCFile rc(themesPath + "\\ThemeTestOne\\theme.rc");
		Theme t(themesPath + "\\ThemeTestOne\\", rc);

		CHECK(t.getPreview() == "");

		RCFile rc2(themesPath + "\\ThemePreviewOne\\theme.rc");
		Theme t2(themesPath + "\\ThemePreviewOne", rc2);

		// Can't use the full path, because themesPath is a relative path, and
		// the path given by getPreview is not.
		string previewEnd = t2.getPreview().substr(t2.getPreview().length() - 28);

		CHECK(previewEnd == "\\ThemePreviewOne\\preview.bmp");

		RCFile rc3(themesPath + "\\ThemePreviewTwo\\theme.rc");
		Theme t3(themesPath + "\\ThemePreviewTwo", rc3);

		previewEnd = t3.getPreview().substr(t3.getPreview().length() - 28);

		CHECK(previewEnd == "\\ThemePreviewTwo\\preview.png");
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

	TEST(GetFolder)
	{
		Theme t("Q:\\This\\is\\a\\test\\", RCFile(""));

		CHECK(t.getFolder() == "test");

		Theme t2("test", RCFile(""));

		CHECK(t2.getFolder() == "test");

		Theme t3("TestFiles\\Themes\\Turtle Soup II", RCFile(""));

		CHECK(t3.getFolder() == "Turtle Soup II");
	}

	TEST(GetOTSVersion)
	{
		RCFile rc("TestFiles\\Themes\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\Themes\\ThemeTestOne", rc);

		CHECK(t.getOTSVersion() == "2.0");

		RCFile rc2("TestFiles\\Themes\\Turtle Soup II\\theme.rc");
		Theme t2("TestFiles\\Themes\\Turtle Soup II", rc2);

		CHECK(t2.getOTSVersion() == "");

		RCFile rc3("testfiles\\themes\\themetesttwo\\theme.rc");
		Theme t3("testfiles\\themes\\themetesttwo", rc3);

		CHECK(t3.getOTSVersion() == "2");
	}

	TEST(GetNeededModules)
	{
		RCFile rc("TestFiles\\Themes\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\Themes\\ThemeTestOne", rc);

		ModuleList neededModules = t.getNeededModules();

		CHECK(neededModules.size() == 6);
		CHECK(neededModules.contains(Module("jdesk-0.711")));
		CHECK(neededModules.contains(Module("xtaskbar-1.1.5")));
		CHECK(neededModules.contains(Module("vtray-1.10")));
		CHECK(neededModules.contains(Module("popup2-2.1.7")));
		CHECK(neededModules.contains(Module("lsxcommand-1.9.3")));
		CHECK(neededModules.contains(Module("icondesk-0.68")));
	}

	TEST(GetSetEnabled)
	{
		RCFile rc("TestFiles\\Themes\\ThemeTestOne\\theme.rc");
		Theme t("TestFiles\\Themes\\ThemeTestOne", rc);

		CHECK(t.getEnabled() == false);

		t.setEnabled(true);

		CHECK(t.getEnabled() == true);
	}
}