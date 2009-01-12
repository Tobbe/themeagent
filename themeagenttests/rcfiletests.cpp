#include "RCFile.h"
#include <UnitTest++.h>
#include <windows.h>
#include <cassert>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class SetupFixtureRCFile
{
public:
	string rc12;

	SetupFixtureRCFile()
	{
		ofstream rcfile;
		rc12 = "rc12.rc";
		rcfile.open(rc12.c_str(), ios::out | ios::trunc);

		if (!rcfile.is_open())
		{
			assert(false);
		}
		else
		{
			rcfile << "   \tsettingOne    uno" << endl;
			rcfile << "\t\t settingTwo    dos" << endl;
			rcfile << "     settingThree  tres" << endl;
			rcfile << endl;
			rcfile << "\t   settingFour   red green blue  \t  " << endl;
			rcfile << endl;
			rcfile << "*test MessageBox(NULL, \"message box text\", \"caption\", MB_OK);" << endl;
			rcfile << "*test cout << \"text to standard output\" << endl;" << endl;
			rcfile << "*test fstream(\"Twelve: %d, Three and three quaters: %f, Fifty six: %X\", 12, 15/4.0, 56)" << endl;
			rcfile << endl;
			rcfile << "*single this is the only \"*single\"" << endl;
			rcfile << endl;
			rcfile << "settingFive   cuatro" << endl;
			rcfile << "settingSix" << endl;
			rcfile << "settingTrue true" << endl;
			rcfile << "settingFalse no" << endl;

			rcfile.close();
		}
	}

	~SetupFixtureRCFile()
	{
		DeleteFile(rc12.c_str());
	}

};
			

SUITE(RCFile)
{
	TEST_FIXTURE(SetupFixtureRCFile, Constructor)
	{
		RCFile rc(rc12);
		CHECK(rc.lines() == 12);
	}

	TEST_FIXTURE(SetupFixtureRCFile, Get)
	{
		RCFile rc(rc12);

		CHECK(rc.get("settingone") == "uno");
		CHECK(rc.get("doesntexist") == "");
		CHECK(rc.get("settingFour") == "red green blue");
	}

	TEST_FIXTURE(SetupFixtureRCFile, IsSet)
	{
		RCFile rc(rc12);

		CHECK(rc.isSet("doesntexist") == false);
		CHECK(rc.isSet("settingone") == true);
		CHECK(rc.isSet("settingSix") == true);
	}

	TEST_FIXTURE(SetupFixtureRCFile, GetMultiple)
	{
		RCFile rc(rc12);

		CHECK(rc.getMultiple("settingOne") == "uno");

		// Should reset settingOne counter when we reach the end of the 
		// settings with that name
		CHECK(rc.getMultiple("settingOne") == ""); 
		CHECK(rc.getMultiple("settingOne") == "uno");

		// Should reset settingOne's counter as soon as we access some other
		// setting
		CHECK(rc.getMultiple("doesntexist") == ""); 
		CHECK(rc.getMultiple("settingOne") == "uno");
		CHECK(rc.getMultiple("settingOne") == ""); 

		CHECK(rc.getMultiple("*test") == "MessageBox(NULL, \"message box text\", \"caption\", MB_OK);");
		CHECK(rc.getMultiple("*test") == "cout << \"text to standard output\" << endl;");
		CHECK(rc.getMultiple("*test") == "fstream(\"Twelve: %d, Three and three quaters: %f, Fifty six: %X\", 12, 15/4.0, 56)");
		CHECK(rc.getMultiple("*test") == "");
		CHECK(rc.getMultiple("*test") == "MessageBox(NULL, \"message box text\", \"caption\", MB_OK);");
	}

	TEST_FIXTURE(SetupFixtureRCFile, isTrue)
	{
		RCFile rc(rc12);

		CHECK(rc.isTrue("settingSix"));
		CHECK(rc.isTrue("settingTrue"));
		CHECK(rc.isTrue("settingFalse") == false);
	}
}