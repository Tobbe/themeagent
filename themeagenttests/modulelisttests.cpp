#include <UnitTest++.h>
#include "Module.h"
#include "ModuleList.h"
#include <windows.h>
#include <cassert>
#include <string>

using namespace std;

class SetupFixtureModule {
public:
	string programPath;

	SetupFixtureModule()
	{
		char buffer[MAX_PATH];

		if (GetModuleFileName(NULL, buffer, MAX_PATH) == 0)
		{
			assert(false);
		}

		programPath = buffer;
		int index = programPath.find_last_of('\\');

		if (index == string::npos)
		{
			assert(false);
		}

		programPath = programPath.substr(0, index);
	}
};

SUITE(ModuleList)
{
	TEST_FIXTURE(SetupFixtureModule, TestAddSize)
	{
		string fileName1 = "testModule-0.1.dll";
		string fileName2 = "testModule-0.2.dll";
		ModuleList ml;

		Module m1(programPath + "\\" + fileName1);	

		ml.add(m1);
		CHECK(ml.size() == 1);

		ml.add(m1);
		CHECK(ml.size() == 1);

		Module m2(programPath + "\\" + fileName2);
		ml.add(m2);
		CHECK(ml.size() == 2);

		Module m3(fileName2);
		ml.add(m3);
		CHECK(ml.size() == 2);
	}

	TEST_FIXTURE(SetupFixtureModule, TestContains)
	{
		string fileName1 = "testModule-0.1.dll";
		string fileName2 = "testModule-0.2.dll";
		ModuleList ml;

		Module m1(programPath + "\\" + fileName1);	
		Module m2(programPath + "\\" + fileName2);	
		ml.add(m1);
		ml.add(m2);

		CHECK(ml.contains(m1));
		CHECK(ml.contains(m2));
		CHECK(ml.contains(Module(fileName1)));
	}
}