#include <UnitTest++.h>
#include "ThemeList.h"
#include "RCFile.h"
#include "Theme.h"

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
}
