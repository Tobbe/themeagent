#include <UnitTest++.h>
#include "NullTheme.h"

SUITE(NullTheme)
{
	TEST(GetMethods)
	{
		NullTheme nt;
		CHECK(nt.getName() == "");
		CHECK(nt.getAuthor() == "");
		CHECK(nt.getVersion() == "");
		CHECK(nt.getPath() == "");
		CHECK(nt.getOTSVersion() == "");
		CHECK(nt.getPreview() == "");
		CHECK(nt.getNeededModules().size() == 0);
	}

	TEST(SetEnable)
	{
		NullTheme nt;
		CHECK(nt.getEnabled() == false);
		nt.setEnabled(true);
		CHECK(nt.getEnabled() == false);
	}
}
