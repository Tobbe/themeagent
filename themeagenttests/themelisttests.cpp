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
}
