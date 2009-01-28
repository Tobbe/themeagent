#include <UnitTest++.h>
#include "ThemeList.h"
#include "RCFile.h"
#include "Theme.h"
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

SUITE(ThemeList)
{
	TEST(Size)
	{
		ThemeList tl;
		CHECK(tl.size() == 0);

		RCFile rc("");

		tl.addTheme(Theme("", rc));
		tl.addTheme(Theme("", rc));
		tl.addTheme(Theme("", rc));
		CHECK(tl.size() == 3);
	}

	TEST(IndexingOperator)
	{
		ThemeList tl;
		RCFile rc("");
		tl.addTheme(Theme("Test1", rc));
		tl.addTheme(Theme("Test2", rc));
		tl.addTheme(Theme("Test3", rc));
		CHECK(tl[0].getName() == "Test1");
		CHECK(tl[2].getName() == "Test3");
		CHECK(tl[1].getName() == "Test2");

		CHECK(tl[10].getName() == "");
	}

	TEST(AddTheme)
	{
		ThemeList tl;
		RCFile rc("");
		size_t index;

		index = tl.addTheme(Theme("Test1", rc));
		CHECK(tl[index].getName() == "Test1");

		tl.addTheme(Theme("Test2", rc));
		tl.addTheme(Theme("Test3", rc));
		tl.addTheme(Theme("Test4", rc));

		index = tl.addTheme(Theme("Test5", rc));
		CHECK(tl[index].getName() == "Test5");

		index = tl.addTheme(Theme("Test6", rc));
		CHECK(tl[index].getName() == "Test6");
	}

	TEST(WriteToFile)
	{
		string line;
		ifstream infile;
		ThemeList tl;
		RCFile rc("");
		string filename = "TestFiles\\themelisttest.rc";

		infile.open(filename.c_str());
		CHECK(infile.is_open() == false);
		infile.close();
		infile.clear();

		tl.addTheme(Theme("Test1", rc));
		tl.addTheme(Theme("Test2", rc));
		tl.addTheme(Theme("Test3", rc));

		tl.writeToFile(filename);

		infile.open(filename.c_str());
		CHECK(infile.is_open() == true);
		getline(infile, line);
		CHECK(line == "");
		CHECK(infile.eof() == true);
		infile.clear();
		infile.close();

		tl[0].setEnabled(true);
		tl[1].setEnabled(true);
		tl[2].setEnabled(true);

		tl.writeToFile(filename);

		infile.open(filename.c_str());
		CHECK(infile.is_open() == true);

		getline(infile, line);
		CHECK(line == "*Popup \"Test1\" !execute [\"$LiteStepDir$utilities\\SLI-ThemeManager.exe\" /switch \"Test1\"]");

		getline(infile, line);
		CHECK(line == "*Popup \"Test2\" !execute [\"$LiteStepDir$utilities\\SLI-ThemeManager.exe\" /switch \"Test2\"]");

		getline(infile, line);
		CHECK(line == "*Popup \"Test3\" !execute [\"$LiteStepDir$utilities\\SLI-ThemeManager.exe\" /switch \"Test3\"]");

		getline(infile, line);
		CHECK(line == "");

		CHECK(infile.eof() == true);
		infile.close();

		DeleteFile(filename.c_str());
	}
}
