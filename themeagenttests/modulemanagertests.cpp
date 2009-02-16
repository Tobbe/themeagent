#include "ModuleManager.h"
#include <UnitTest++.h>
#include <vector>
#include <string>

using namespace std;

SUITE(ModuleManager)
{
	TEST(Constructor)
	{
		vector<string> dlSites;
		ModuleManager mm("TestFiles\\Modules", dlSites);
		ModuleList ml = mm.getModuleList();
		CHECK(ml.size() == 5);
		CHECK(ml.contains(Module("dynamp-0.51.dll")));
		CHECK(ml.contains(Module("lsres.dll")));
		CHECK(ml.contains(Module("lslua-0.7")));
	}
}