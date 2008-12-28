#include <UnitTest++.h>
#include "Module.h"
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

SUITE(Module)
{
	TEST_FIXTURE(SetupFixtureModule, TestConstructorName)
	{
		string fileName = "testModule-0.1.dll";

		Module m1(fileName);

		CHECK(m1.getName() == "testModule-0.1");

		Module m2(programPath + "\\" + fileName);

		CHECK(m2.getName() == "testModule-0.1");
	}

	TEST_FIXTURE(SetupFixtureModule, TestEqual)
	{
		string fileName = "testModule-0.1.dll";

		Module m1(fileName);
		Module m2(fileName);

		CHECK(m1 == m2);

		Module m3(programPath + "\\" + fileName);
		Module m4(programPath + "\\" + fileName);

		CHECK(m3 == m4);
		CHECK(m1 == m4);
	}
}