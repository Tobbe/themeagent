#include <UnitTest++.h>
#include "Module.h"
#include "Module.cpp"
#include <windows.h>
#include <cassert>
#include <string>

using std::string;

class SetupFixture {
public:
	string programPath;

	SetupFixture()
	{
		char buffer[MAX_PATH];

		if (GetModuleFileName(NULL, buffer, MAX_PATH) == 0)
		{
			assert(false);
		}

		string programPath = buffer;
		int index = programPath.find_last_of('\\');

		if (index == string::npos)
		{
			assert(false);
		}

		programPath = programPath.substr(0, index);
	}
};

TEST_FIXTURE(SetupFixture, TestModuleConstructorName)
{
	string fileName = "testModule-0.1.dll";

	Module m1(fileName);

	CHECK(m1.getName() == "testModule-0.1");

	Module m2(programPath + "\\" + fileName);

	CHECK(m1.getName() == "testModule-0.1");
}

TEST(TestEqual)
{
	string fileName = "testModule-0.1.dll";

	Module m1(fileName);
	Module m2(fileName);

	CHECK(m1 == m2);
}

int main()
{
	return UnitTest::RunAllTests();
}