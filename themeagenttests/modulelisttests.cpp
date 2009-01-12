#include <UnitTest++.h>
#include "Module.h"
#include "ModuleList.h"
#include <windows.h>
#include <cassert>
#include <string>

using namespace std;

class SetupFixtureModules {
public:
	string programPath;
	string fileName1;
	string fileName2;
	Module m1;
	Module m2;

	SetupFixtureModules() : fileName1("testModule-0.1.dll"), fileName2("testModule-0.2.dll"), m1(""), m2("")
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

		m1 = Module(programPath + "\\" + fileName1);
		m2 = Module(programPath + "\\" + fileName2);
	}
};

SUITE(ModuleList)
{
	TEST_FIXTURE(SetupFixtureModules, TestAddSize)
	{
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

	TEST_FIXTURE(SetupFixtureModules, TestContains)
	{
		ModuleList ml;

		ml.add(m1);
		ml.add(m2);

		CHECK(ml.contains(m1));
		CHECK(ml.contains(m2));
		CHECK(ml.contains(Module(fileName1)));
	}
}